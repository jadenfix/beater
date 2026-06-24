#!/usr/bin/env bash
set -euo pipefail
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
root="$here/../../.."
# Reuse the ergonomic SDK's installed tsx/node_modules to run the TS conformance.
[ -d "$root/sdks/typescript/node_modules" ] || (cd "$root/sdks/typescript" && npm install >/dev/null 2>&1)
cd "$root/sdks/typescript"
node --import tsx "$here/conformance.ts"
