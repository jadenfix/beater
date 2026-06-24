#!/usr/bin/env bash
set -euo pipefail
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
root="$here/../../.."
venv="/tmp/beater-conf-py"

[ -x "$venv/bin/python" ] || python3 -m venv "$venv"
"$venv/bin/pip" -q install -e "$root/sdks/clients/python" >/dev/null 2>&1 || \
  "$venv/bin/pip" -q install "$root/sdks/clients/python" >/dev/null
"$venv/bin/python" "$here/conformance.py"
