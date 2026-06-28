#!/usr/bin/env bash
# check-sdk-parity.sh — validate SDK behavioral parity against the manifest.
#
# Reads sdks/conformance/parity-manifest.json and verifies:
#   1. The manifest is well-formed JSON with the expected top-level keys.
#   2. Every SDK listed in manifest.sdks has a conformance directory under
#      sdks/conformance/<lang>/.
#   3. Every behavior entry lists a sdk_status for each declared SDK.
#   4. Prints a human-readable matrix showing which behaviors are still TODO.
#
# This is a SCAFFOLD: it does not drive the 7 SDK runtimes. It proves the
# manifest is internally consistent and flags unimplemented behaviors so
# maintainers know exactly what remains. See sdks/README.md §Behavioral parity.
#
# Usage:
#   scripts/check-sdk-parity.sh          # normal run (exit non-zero on drift)
#   scripts/check-sdk-parity.sh --check  # same; alias for CI / dry-run mode
#
# Exit codes:
#   0 — manifest well-formed, all SDKs accounted for (TODO statuses ok)
#   1 — manifest malformed, missing conformance dir, or missing sdk_status entry
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

MANIFEST="sdks/conformance/parity-manifest.json"
CONFORMANCE_DIR="sdks/conformance"

fail=0

step() { echo; echo "==> $*"; }

# ---------------------------------------------------------------------------
step "1/4  Locate manifest"
# ---------------------------------------------------------------------------
if [ ! -f "$MANIFEST" ]; then
  echo "ERROR: manifest not found: $MANIFEST" >&2
  exit 1
fi
echo "  found: $MANIFEST"

# ---------------------------------------------------------------------------
step "2/4  Validate manifest JSON"
# ---------------------------------------------------------------------------
if ! python3 -m json.tool "$MANIFEST" > /dev/null 2>&1; then
  echo "ERROR: $MANIFEST is not valid JSON" >&2
  exit 1
fi
echo "  JSON valid"

# Check required top-level keys (version, sdks, behaviors) using python3 to
# avoid a jq dependency; jq is used opportunistically if available.
python3 - "$MANIFEST" <<'PYEOF'
import json, sys

data = json.load(open(sys.argv[1]))
required = {"version", "sdks", "behaviors"}
missing = required - data.keys()
if missing:
    print(f"ERROR: manifest missing keys: {missing}", file=sys.stderr)
    sys.exit(1)
if not isinstance(data["sdks"], list) or not data["sdks"]:
    print("ERROR: manifest 'sdks' must be a non-empty list", file=sys.stderr)
    sys.exit(1)
if not isinstance(data["behaviors"], list) or not data["behaviors"]:
    print("ERROR: manifest 'behaviors' must be a non-empty list", file=sys.stderr)
    sys.exit(1)
for b in data["behaviors"]:
    for key in ("id", "title", "description", "assertions", "sdk_status"):
        if key not in b:
            print(f"ERROR: behavior '{b.get('id','?')}' missing key '{key}'", file=sys.stderr)
            sys.exit(1)
print(f"  schema ok: version={data['version']}, {len(data['sdks'])} SDKs, {len(data['behaviors'])} behaviors")
PYEOF

# ---------------------------------------------------------------------------
step "3/4  Conformance directories present for every declared SDK"
# ---------------------------------------------------------------------------
declared_sdks="$(python3 -c "import json,sys; d=json.load(open('$MANIFEST')); print(' '.join(d['sdks']))")"
for sdk in $declared_sdks; do
  if [ -d "$CONFORMANCE_DIR/$sdk" ]; then
    echo "  [ok]  $CONFORMANCE_DIR/$sdk"
  else
    echo "  [MISSING]  $CONFORMANCE_DIR/$sdk  <-- add this directory" >&2
    fail=1
  fi
done

# ---------------------------------------------------------------------------
step "4/4  Every behavior has sdk_status for every declared SDK"
# ---------------------------------------------------------------------------
python3 - "$MANIFEST" "$CONFORMANCE_DIR" <<'PYEOF'
import json, os, sys

manifest_path = sys.argv[1]
conformance_dir = sys.argv[2]

data = json.load(open(manifest_path))
sdks = data["sdks"]
behaviors = data["behaviors"]

fail = 0
todo_count = 0
total = 0

print()
# Print header row
header = f"  {'BEHAVIOR':<36}" + "".join(f" {s:<12}" for s in sdks)
print(header)
print("  " + "-" * (36 + 13 * len(sdks)))

for b in behaviors:
    bid = b["id"]
    statuses = b.get("sdk_status", {})
    row = f"  {bid:<36}"
    for sdk in sdks:
        total += 1
        status = statuses.get(sdk, "MISSING")
        if status == "MISSING":
            fail = 1
            cell = "MISSING"
        elif status == "TODO":
            todo_count += 1
            cell = "TODO"
        else:
            cell = status[:12]
        row += f" {cell:<12}"
    print(row)

    # check for any SDK missing entirely from sdk_status
    for sdk in sdks:
        if sdk not in statuses:
            print(f"  ERROR: behavior '{bid}' has no sdk_status entry for '{sdk}'", file=sys.stderr)
            fail = 1

print()
if fail:
    print(f"ERROR: sdk_status entries are missing — fix the manifest.", file=sys.stderr)
    sys.exit(1)

implemented = total - todo_count
print(f"  behaviors x SDKs: {total} total, {implemented} implemented, {todo_count} TODO")
if todo_count > 0:
    print(f"  NOTE: {todo_count} TODO entries — add per-SDK test files and update sdk_status to 'implemented'.")
PYEOF
status_rc=$?
[ $status_rc -ne 0 ] && fail=1

# ---------------------------------------------------------------------------
echo
if [ "$fail" -ne 0 ]; then
  echo "SDK PARITY DRIFT — resolve the issues above and re-run." >&2
  exit 1
fi
echo "SDK parity manifest: well-formed and all SDKs accounted for."
echo "Run the per-language conformance test suites (sdks/conformance/<lang>/run.sh) to validate behavior."
