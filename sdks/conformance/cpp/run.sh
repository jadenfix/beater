#!/usr/bin/env bash
# Live conformance for the generated C++ (cpp-restsdk) control-plane client.
# Builds the generated client + a conformance program that round-trips
# health + createDataset + listTraces against beaterd with typed responses.
set -euo pipefail
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$here"

: "${BEATER_BASE_URL:?BEATER_BASE_URL must be set (live beaterd)}"

build="$here/build"
echo "  configuring + building generated C++ client + conformance program"
cmake -S "$here" -B "$build" \
  -DCMAKE_PREFIX_PATH="/opt/homebrew;/opt/homebrew/opt/openssl@3" >/dev/null
cmake --build "$build" --target beater_cpp_conformance -j4 >/dev/null

"$build/beater_cpp_conformance"
