#!/usr/bin/env bash
# Build the beaterd image on whichever runtime is selected (docker or apple
# `container`). Usage: scripts/build-image.sh [tag]
set -euo pipefail
root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"
# shellcheck source=scripts/container-runtime.sh
source scripts/container-runtime.sh

TAG="${1:-beaterd:local}"
echo "==> Building $TAG with runtime: $(crt_cli)"
crt_build "$TAG"
echo "==> Built $TAG"
