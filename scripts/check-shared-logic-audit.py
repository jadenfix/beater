#!/usr/bin/env python3
"""Guard the shared-logic audit against losing architecture-backed anchors."""

from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parent.parent
AUDIT = ROOT / "docs" / "engineering" / "shared-logic-audit.md"
ARCHITECTURE = ROOT / "ARCHITECTURE.md"

SECTIONS = [
    "Audit Method",
    "Shipped in this pass",
    "Keep Independent",
    "Audit Findings",
    "Next Shared-Logic Targets",
]

AUDIT_GROUPS = {
    "audit method": [
        "Scan first-party Rust, TypeScript, Python, Node ESM, and shell sources",
        "Keep black-box contract tests",
        "large files as a direction signal, not an automatic refactor target",
    ],
    "shipped shared contracts": [
        "scripts/gate2_proof_contract.py",
        "Gate 2 readiness, public handoff, proof generation, and proof validation",
        "web/dashboard/lib/gate2-confirmation-request.ts",
        "web/dashboard/tests/e2e/gate2-confirmation-code.mjs",
        "generated OpenAPI",
        "PageRunSummaryDoc",
        "beater_core::sha256_hex",
        "beater_core::sha256_json_hash",
        "beater_core::lower_hex",
        "beater-search::TraceIngestedSearchProcessor",
        "beater_store::query_runs_by_materializing_spans",
        "backend-aggregation boundary",
    ],
    "independent guardrails": [
        "independent expected outcomes",
        "guardrails against accidental coupling",
        "Runtime-specific Gate 2 confirmation implementations",
        "shared prefix and golden vector",
    ],
    "audit findings": [
        "SQLite schema ownership is the largest remaining duplication",
        "small SQLite support module",
        "without becoming an ORM",
        "OpenAPI doc schemas mirror real API and schema DTOs",
        "TraceStore::query_runs",
        "ClickHouse-scale implementation must aggregate",
        "rather than calling the fallback helper",
        "preserving all-in-one operational simplicity",
    ],
    "next targets": [
        "SQLite schema: choose the one-database versus per-store migration model",
        "Gate 2 proof schema: move required proof field names",
        "TraceStore scale contract: add a ClickHouse-oriented run query conformance suite",
        "Dashboard query model: replace repeated query field mappings",
        "Dashboard Gate 2 confirmation: keep the request/id contract shared",
        "Rust store result helpers",
        "OTLP test support",
    ],
}

ARCHITECTURE_TOKENS = [
    "Ship one Rust binary first",
    "Use standards at the edge",
    "generated SDK clients plus a native Rust SDK, an MCP server, and a CLI",
    "scripts/check-contract-sync.sh",
    "gate2-proof-contract",
    "The GENERATED OpenAPI client is the ONLY data contract",
]


def normalize(text: str) -> str:
    return " ".join(text.split())


def main() -> int:
    audit = AUDIT.read_text(encoding="utf-8")
    architecture = ARCHITECTURE.read_text(encoding="utf-8")
    normalized_audit = normalize(audit)
    normalized_architecture = normalize(architecture)
    failures: list[str] = []

    section_positions = []
    for section in SECTIONS:
        token = f"## {section}"
        position = audit.find(token)
        if position == -1:
            failures.append(f"missing section: {token}")
        section_positions.append(position)
    if section_positions != sorted(section_positions):
        failures.append("shared-logic audit sections are out of order")

    for group, tokens in AUDIT_GROUPS.items():
        for token in tokens:
            if normalize(token) not in normalized_audit:
                failures.append(f"{group}: missing {token!r}")

    for token in ARCHITECTURE_TOKENS:
        if normalize(token) not in normalized_architecture:
            failures.append(f"architecture backing: missing {token!r}")

    if failures:
        print("Shared logic audit drift:", file=sys.stderr)
        for failure in failures:
            print(f"  - {failure}", file=sys.stderr)
        return 1

    print("Shared logic audit keeps the expected architecture-backed anchors.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
