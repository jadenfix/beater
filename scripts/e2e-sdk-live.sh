#!/usr/bin/env bash
# Deep live E2E: build + run beaterd, emit a trace through the Python ergonomic
# SDK over real OTLP/HTTP, and verify it lands and normalizes via the read API.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

PORT="${BEATER_E2E_PORT:-18080}"
GRPC_PORT="${BEATER_E2E_GRPC_PORT:-14317}"
VENV="${BEATER_E2E_VENV:-/tmp/beater-py-venv}"
data_dir="$(mktemp -d)"
log="$(mktemp)"

cleanup() {
  [ -n "${beaterd_pid:-}" ] && kill "$beaterd_pid" 2>/dev/null || true
  rm -rf "$data_dir"
}
trap cleanup EXIT

echo "==> Building beaterd"
cargo build -q -p beaterd

echo "==> Launching beaterd on :$PORT (grpc :$GRPC_PORT), data=$data_dir"
./target/debug/beaterd \
  --addr "127.0.0.1:$PORT" \
  --otlp-grpc-addr "127.0.0.1:$GRPC_PORT" \
  --data-dir "$data_dir" \
  --auth-mode local >"$log" 2>&1 &
beaterd_pid=$!

echo "==> Waiting for health"
for _ in $(seq 1 60); do
  if curl -fsS "http://127.0.0.1:$PORT/health" >/dev/null 2>&1; then ready=1; break; fi
  sleep 0.5
done
if [ -z "${ready:-}" ]; then echo "beaterd did not become healthy:" >&2; cat "$log" >&2; exit 1; fi

echo "==> Ensuring Python SDK + deps in venv"
if [ ! -x "$VENV/bin/python" ]; then python3 -m venv "$VENV"; fi
"$VENV/bin/pip" -q install 'opentelemetry-sdk>=1.20' 'opentelemetry-exporter-otlp-proto-http>=1.20' >/dev/null
"$VENV/bin/pip" -q install -e sdks/python >/dev/null 2>&1 || \
  PYTHONPATH="$root/sdks/python" "$VENV/bin/python" -c "import beater" 2>/dev/null

echo "==> Running live SDK round-trip"
BEATER_BASE_URL="http://127.0.0.1:$PORT" \
BEATER_TENANT_ID=demo BEATER_PROJECT_ID=demo BEATER_ENVIRONMENT_ID=local \
PYTHONPATH="$root/sdks/python" \
  "$VENV/bin/python" sdks/python/tests/e2e_live.py

echo "==> E2E live test passed"
