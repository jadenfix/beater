#!/usr/bin/env bash
set -euo pipefail
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$here"
# Resolve THIS module's deps only (never mutate the committed generated client,
# which must stay byte-identical to `regen-sdks.sh` output).
go mod tidy >/dev/null 2>&1 || true
go run .
