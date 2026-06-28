#!/usr/bin/env bash
# Verify that every example directory under examples/ is covered by
# examples/smoke-manifest.json and that no manifest entry is stale.
#
# Convention: every immediate subdirectory of examples/ must have an entry in
# smoke-manifest.json declaring a "smoke" command (how to build/run the example).
# This keeps the manifest and the directory tree in sync and gives reviewers a
# clear "how do I try this?" for every example.
#
# Usage:
#   examples/check-examples.sh           # coverage check; exits non-zero on drift
#   examples/check-examples.sh --list    # list example names and their smoke commands

set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
manifest="$root/examples/smoke-manifest.json"
examples_dir="$root/examples"

list_mode=0
for arg in "$@"; do
  case "$arg" in
    --list) list_mode=1 ;;
    *) echo "Unknown flag: $arg" >&2; exit 2 ;;
  esac
done

# ---------------------------------------------------------------------------
# Require jq for JSON parsing.
# ---------------------------------------------------------------------------
if ! command -v jq >/dev/null 2>&1; then
  echo "ERROR: jq is required but not found in PATH." >&2
  exit 1
fi

# ---------------------------------------------------------------------------
# --list mode: print example names and their smoke commands.
# ---------------------------------------------------------------------------
if [[ "$list_mode" -eq 1 ]]; then
  echo "Examples and smoke commands (from $manifest):"
  echo
  while IFS= read -r name; do
    smoke="$(jq -r ".examples[\"$name\"].smoke" "$manifest")"
    notes="$(jq -r ".examples[\"$name\"].notes // empty" "$manifest")"
    printf "  %-16s  %s\n" "$name" "$smoke"
    if [[ -n "$notes" ]]; then
      printf "  %-16s  # %s\n" "" "$notes"
    fi
    echo
  done < <(jq -r '.examples | keys[]' "$manifest")
  exit 0
fi

# ---------------------------------------------------------------------------
# Coverage check: discover example directories; compare against manifest.
# ---------------------------------------------------------------------------
fail=0

step() { echo; echo "==> $1"; }

step "1/2 every example directory has a manifest entry"
while IFS= read -r dir; do
  if jq -e ".examples[\"$dir\"]" "$manifest" >/dev/null 2>&1; then
    echo "  ok  $dir"
  else
    echo "  MISSING  $dir — add an entry to examples/smoke-manifest.json" >&2
    fail=1
  fi
done < <(
  find "$examples_dir" -mindepth 1 -maxdepth 1 -type d ! -name '.*' \
    -exec basename {} \; | sort
)

step "2/2 no stale manifest entries"
while IFS= read -r key; do
  if [[ -d "$examples_dir/$key" ]]; then
    echo "  ok  $key"
  else
    echo "  STALE  $key — directory examples/$key does not exist; remove from manifest" >&2
    fail=1
  fi
done < <(jq -r '.examples | keys[]' "$manifest" | sort)

echo
if [[ "$fail" -ne 0 ]]; then
  echo "COVERAGE DRIFT — update examples/smoke-manifest.json to match the directory tree." >&2
  exit 1
fi

total="$(find "$examples_dir" -mindepth 1 -maxdepth 1 -type d ! -name '.*' | wc -l | tr -d ' ')"
echo "All $total example directories are covered by smoke-manifest.json."
exit 0
