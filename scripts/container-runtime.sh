#!/usr/bin/env bash
# Container runtime abstraction: run Beater on Docker OR Apple `container`.
#
# Apple `container` (https://github.com/apple/container) is Apple's native
# container runtime for Apple silicon (macOS 26+). Its CLI mirrors Docker for the
# commands we need (build/run/ls/stop/logs), with two differences this shim
# handles: (1) it needs `container system start` before use; (2) it assigns each
# container its own IP rather than publishing ports to localhost.
#
# Source this file, then call crt_* helpers. Select the runtime with
# BEATER_CONTAINER_RUNTIME=docker|container (default: auto-detect, preferring
# docker when both are present for least surprise).
set -euo pipefail

crt_detect() {
  if [ -n "${BEATER_CONTAINER_RUNTIME:-}" ]; then
    echo "$BEATER_CONTAINER_RUNTIME"; return
  fi
  if command -v docker >/dev/null 2>&1; then echo docker; return; fi
  if command -v container >/dev/null 2>&1; then echo container; return; fi
  echo "no container runtime found (install docker or apple 'container')" >&2
  return 1
}

CRT="${CRT:-$(crt_detect)}"
export CRT

crt_cli() { echo "$CRT"; }

# Ensure the runtime is ready to accept commands.
crt_ensure_up() {
  case "$CRT" in
    container)
      container system status >/dev/null 2>&1 || container system start
      ;;
    docker)
      docker info >/dev/null 2>&1 || {
        echo "docker daemon not running; start Docker Desktop or dockerd" >&2; return 1; }
      ;;
  esac
}

# Build the image. Args: <tag> [extra build args...]
crt_build() {
  local tag="$1"; shift || true
  crt_ensure_up
  "$CRT" build -t "$tag" -f Dockerfile "$@" .
}

# Run a container detached. Args: <name> <tag> <port> [extra run args...]
# Docker publishes <port> to localhost; Apple container exposes it on the
# container IP (resolve with crt_address).
crt_run() {
  local name="$1" tag="$2" port="$3"; shift 3 || true
  crt_ensure_up
  "$CRT" run -d --name "$name" -p "${port}:${port}" "$@" "$tag"
}

# Print a reachable base address (host:port) for a running container.
crt_address() {
  local name="$1" port="$2"
  case "$CRT" in
    docker)
      echo "127.0.0.1:${port}"
      ;;
    container)
      # Apple container assigns each container an IP; read it from inspect.
      local ip
      ip="$(container inspect "$name" 2>/dev/null \
        | grep -oE '"address"[^,]*' | head -1 | grep -oE '[0-9.]+' | head -1)"
      if [ -n "$ip" ]; then echo "${ip}:${port}"; else echo "127.0.0.1:${port}"; fi
      ;;
  esac
}

crt_stop() { "$CRT" stop "$1" >/dev/null 2>&1 || true; "$CRT" rm "$1" >/dev/null 2>&1 || true; }
crt_logs() { "$CRT" logs "$1"; }
