#!/usr/bin/env python3
"""Audit the OpenAPI spec for shape consistency across the API surface.

Enforces the conventions that keep the API/MCP/CLI/SDKs nice and in-sync:
  - every operation has a unique camelCase operationId
  - every operation has exactly one resource tag
  - every operation documents a uniform error body (ApiErrorBody) for failures
  - success responses reference a NAMED schema (no anonymous/inline objects)
  - list operations expose pagination (cursor/next_cursor)
Exit 1 on any violation.
"""

import json
import re
import sys

SPEC = sys.argv[1] if len(sys.argv) > 1 else "sdks/openapi/beater-api.json"
spec = json.load(open(SPEC))
paths = spec["paths"]

violations = []
op_ids = {}
CAMEL = re.compile(r"^[a-z][a-zA-Z0-9]*$")

ops = []
for path, methods in paths.items():
    for method, op in methods.items():
        if method in ("parameters",):
            continue
        ops.append((method.upper(), path, op))

for method, path, op in ops:
    where = f"{method} {path}"
    oid = op.get("operationId")
    tags = op.get("tags", [])

    if not oid:
        violations.append(f"{where}: missing operationId")
    else:
        if not CAMEL.match(oid):
            violations.append(f"{where}: operationId '{oid}' is not camelCase")
        op_ids.setdefault(oid, []).append(where)

    if len(tags) != 1:
        violations.append(f"{where}: expected exactly 1 tag, got {tags}")

    responses = op.get("responses", {})
    # Health is the only allowed exception to the error-body rule.
    # 422 is used for partial-success (drain-with-dead-letters) and carries a
    # domain payload, not the shared error body, so it's exempt from this rule.
    if oid != "health":
        err_codes = [c for c in responses if c.startswith(("4", "5")) and c != "422"]
        if not err_codes:
            violations.append(f"{where}: no documented 4xx/5xx error response")
        for code in err_codes:
            ref = (
                responses[code]
                .get("content", {})
                .get("application/json", {})
                .get("schema", {})
                .get("$ref", "")
            )
            if not ref.endswith("/ErrorResponse") and not ref.endswith("/ApiErrorBody"):
                violations.append(
                    f"{where}: error {code} body is not the shared error schema (got {ref or 'none'})"
                )

    # Success response must reference a named schema (no inline/anonymous object).
    for code, body in responses.items():
        if not code.startswith("2"):
            continue
        schema = body.get("content", {}).get("application/json", {}).get("schema", {})
        if not schema:
            continue  # empty 204-style ok
        if "$ref" not in schema and schema.get("type") == "object" and "properties" in schema:
            violations.append(f"{where}: success {code} uses an inline anonymous object (name it)")

# operationId uniqueness
for oid, wheres in op_ids.items():
    if len(wheres) > 1:
        violations.append(f"operationId '{oid}' is duplicated: {wheres}")

# list operations should paginate
for method, path, op in ops:
    oid = op.get("operationId", "")
    if oid.startswith("list") and oid not in ("listAuditEvents", "listJudgeLedger", "listProviderSecrets", "listReviewTasks"):
        params = {p.get("name") for p in op.get("parameters", [])}
        if "cursor" not in params and "limit" not in params:
            violations.append(f"{method} {path}: list op '{oid}' lacks pagination params")

print(f"audited {len(ops)} operations, {len(op_ids)} unique operationIds, "
      f"{len(spec['components']['schemas'])} schemas")
if violations:
    print(f"\n{len(violations)} CONSISTENCY VIOLATIONS:")
    for v in violations:
        print(f"  - {v}")
    sys.exit(1)
print("PASS: API shapes are consistent")
