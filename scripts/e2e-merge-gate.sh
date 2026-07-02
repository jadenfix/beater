#!/usr/bin/env bash
# Deep merge E2E: prove the merge candidate still works as a product loop across
# the API contract, generated clients, MCP transports, CLI smoke paths, live SDKs,
# and the compose/dashboard self-host path.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

export CARGO_NET_RETRY="${CARGO_NET_RETRY:-10}"
export CARGO_HTTP_MULTIPLEXING="${CARGO_HTTP_MULTIPLEXING:-false}"
export RUST_BACKTRACE="${RUST_BACKTRACE:-1}"

step() {
  echo
  echo "==> $1"
}

skip_enabled() {
  local name="$1"
  [[ "${!name:-0}" == "1" ]]
}

require_docker="${BEATER_DEEP_E2E_REQUIRE_DOCKER:-${CI:-0}}"

if skip_enabled BEATER_DEEP_E2E_SKIP_CONTRACT; then
  step "SKIP contract/spec/SDK drift chain"
else
  step "Contract/spec/SDK drift chain"
  scripts/check-contract-sync.sh
fi

step "Build runtime and CLI binaries"
cargo build -q -p beaterd -p beaterctl

step "MCP HTTP route parity and tool catalog"
cargo test -p beater-mcp --test mcp

step "MCP stdio tools/list smoke"
cargo test -p beaterd --test mcp_stdio -- --test-threads=1

step "CLI local OTLP smoke"
cargo test -p beaterctl --test smoke -- --test-threads=1

step "CLI remote HTTP/gRPC smoke and ingest test"
cargo test -p beaterctl --test remote_smoke -- --test-threads=1

if skip_enabled BEATER_DEEP_E2E_SKIP_NATIVE_SDKS; then
  step "SKIP native Python/TypeScript SDK live OTLP round trips"
else
  step "Python ergonomic SDK live OTLP round trip"
  scripts/e2e-sdk-live.sh

  step "TypeScript ergonomic SDK live OTLP round trip"
  scripts/e2e-sdk-live-ts.sh
fi

if skip_enabled BEATER_DEEP_E2E_SKIP_CLIENT_CONFORMANCE; then
  step "SKIP generated-client live conformance"
else
  step "Generated-client live conformance"
  export BEATER_CONFORMANCE_REQUIRE="${BEATER_CONFORMANCE_REQUIRE:-python,typescript,rust}"
  scripts/e2e-clients-live.sh
fi

if skip_enabled BEATER_DEEP_E2E_SKIP_COMPOSE; then
  step "SKIP compose/dashboard self-host smoke"
else
  step "Compose/dashboard self-host smoke"
  if command -v docker >/dev/null 2>&1 && docker info >/dev/null 2>&1; then
    export COMPOSE_PROJECT_NAME="${COMPOSE_PROJECT_NAME:-beater-merge-e2e}"
    export BEATER_HTTP_PORT="${BEATER_HTTP_PORT:-18082}"
    export BEATER_OTLP_GRPC_PORT="${BEATER_OTLP_GRPC_PORT:-14347}"
    export BEATER_DASHBOARD_PORT="${BEATER_DASHBOARD_PORT:-13082}"
    scripts/smoke-compose.sh
  elif [[ "$require_docker" == "1" || "$require_docker" == "true" ]]; then
    echo "Docker is required for the compose/dashboard smoke but is unavailable." >&2
    exit 1
  else
    echo "WARN: docker unavailable -- skipping compose/dashboard smoke." >&2
  fi
fi

echo
echo "Deep merge E2E passed: contract, MCP, CLI, SDK, and self-host smoke are coherent."
