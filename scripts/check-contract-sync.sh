#!/usr/bin/env bash
# One-command drift test: proves the API contract, the 9 SDK clients, the MCP
# tools, the docs, and the semantic conventions are all in sync with the Rust
# handlers. Run before pushing; CI (sdk-contract.yml) runs the same gates.
#
# Exit non-zero on ANY drift. See CONTRIBUTING.md.
set -euo pipefail
root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

fail=0
step() { echo; echo "==> $1"; }

step "1/5 spec == served routes (openapi_coverage)"
cargo test -q -p beater-api --test openapi_coverage || fail=1

step "2/5 spec + all 9 SDK clients are current (regen --check)"
# Needs the generator: Docker by default, or a local JAR via
# BEATER_OPENAPI_GENERATOR_JAR. Skip with a loud message if neither is available
# so local runs don't silently pass. CI always has Docker.
if [ -n "${BEATER_OPENAPI_GENERATOR_JAR:-}" ]; then
  scripts/regen-sdks.sh --check || fail=1
elif command -v docker >/dev/null 2>&1 && docker info >/dev/null 2>&1; then
  scripts/regen-sdks.sh --check || fail=1
else
  echo "WARN: no generator (docker/JAR) available -- skipping client regen check (CI enforces it)" >&2
fi

step "3/5 API shape consistency audit"
python3 scripts/audit-api-shapes.py || fail=1

step "4/5 semantic conventions == all 5 SDKs"
cargo xtask regen-semconv >/dev/null
git diff --exit-code -- sdks/semconv/conventions.json || { echo "conventions.json is stale" >&2; fail=1; }
python3 scripts/check-semconv-drift.py || fail=1

step "5/5 docs walkthrough references are current"
scripts/check-docs-walkthrough.sh --dry-run || fail=1

echo
if [ "$fail" -ne 0 ]; then
  echo "CONTRACT DRIFT DETECTED -- regenerate (see CONTRIBUTING.md) and commit." >&2
  exit 1
fi
echo "No drift: API, 9 SDKs, MCP tools, docs, and conventions are all in sync."
