#!/usr/bin/env bash
# Live conformance for the generated PHP control-plane client: install it from a
# local path repository and run a program that round-trips against beaterd.
set -euo pipefail
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

: "${BEATER_BASE_URL:?BEATER_BASE_URL must be set (live beaterd)}"

# Install into the conformance dir (composer resolves the client via the path
# repo in composer.json and pulls its guzzle dependency from Packagist).
(
  cd "$here"
  composer install --no-interaction --quiet
)

php "$here/conformance.php"
