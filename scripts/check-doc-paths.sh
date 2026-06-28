#!/usr/bin/env bash
# Scan markdown docs for internal repository path references and assert each
# referenced path exists in the working tree.
#
# Scanned files:
#   README.md  CONTRIBUTING.md  ARCHITECTURE.md  docs/**/*.md
#
# Prefixes checked:
#   crates/  scripts/  sdks/  bins/  web/  examples/  migrations/  .github/
#
# Usage:
#   scripts/check-doc-paths.sh              # normal (exits non-zero on drift)
#   scripts/check-doc-paths.sh --dry-run    # inspect only, never fails
#
# NOTE: this script is focused on *path existence across all docs* (broader
# coverage than scripts/check-docs-walkthrough.sh which checks walkthrough
# command sequencing).  Do not modify check-docs-walkthrough.sh.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

step() { echo; echo "==> $1"; }

DRY_RUN=0
if [[ "${1:-}" == "--dry-run" ]]; then
  DRY_RUN=1
fi

# ---------------------------------------------------------------------------
# SKIP LIST — paths that must NOT be checked for existence.
# Each pattern is a substring match against the extracted path.
# Entries are explained so the intent is clear to future maintainers.
# ---------------------------------------------------------------------------

# Glob / wildcard patterns — not real paths
SKIP_GLOB_CHARS='*'     # anything containing * is a glob, not a real path

# Next.js bracket route params and placeholder tokens — not real FS paths
SKIP_CONTAINS=(
  '['     # e.g. web/dashboard/app/datasets[...]  or  web/dashboard/app/experiments/[id]
  '<'     # e.g. sdks/config/<lang>.yaml  — illustrative placeholder
)

# Exact planned / recommended paths — these are *targets* documented in
# ARCHITECTURE.md's "Target" column or engineering audit recommendations; the
# files do not exist yet and their absence is intentional.
SKIP_EXACT=(
  # Dashboard pages planned in ARCHITECTURE.md §20 Phase 2–4 roadmap rows
  "web/dashboard/app/analytics"               # §20 Phase 2.7 — planned page
  "web/dashboard/app/diff"                    # §20 Phase 2.6 — planned page
  "web/dashboard/app/experiments"             # §20 Phase 2.3 — planned page
  "web/dashboard/app/prompts"                 # §20 Phase 4.7 — planned page
  "web/dashboard/app/review"                  # §20 Phase 2.5 — planned page
  "web/dashboard/app/search"                  # §20 Phase 2.8 — exists locally (untracked) but not yet committed to main
  # SDK features planned in ARCHITECTURE.md §20 Phase 3
  "sdks/python/beater/pytest_plugin.py"       # §20 Phase 3.6 — planned SDK feature
  # Engineering-audit recommendations (docs/engineering/shared-logic-audit.md)
  # These are "should introduce" suggestions, not references to existing files.
  "bins/beaterctl/src/fixtures.rs"            # recommendation: introduce this module
  "crates/beater-api/src/path.rs"             # recommendation: introduce typed paths
  "web/dashboard/lib/dashboard-query.ts"      # recommendation: introduce query helper
)

# ---------------------------------------------------------------------------
# should_skip <path>
# Returns 0 (true) if the path should be skipped, 1 (false) otherwise.
# ---------------------------------------------------------------------------
should_skip() {
  local p="$1"

  # Glob / wildcard
  if [[ "$p" == *"$SKIP_GLOB_CHARS"* ]]; then
    return 0
  fi

  # Contains disqualifying characters
  for tok in "${SKIP_CONTAINS[@]}"; do
    if [[ "$p" == *"$tok"* ]]; then
      return 0
    fi
  done

  # Exact / prefix matches
  for exact in "${SKIP_EXACT[@]}"; do
    if [[ "$p" == "$exact" || "$p" == "${exact}/"* ]]; then
      return 0
    fi
  done

  return 1
}

# ---------------------------------------------------------------------------
# extract_paths <file>
# Prints one candidate path per line extracted from the given markdown file.
# Strategy:
#   1. Backtick spans:  `crates/foo/bar.rs`
#   2. Markdown links:  [text](crates/foo)
# ---------------------------------------------------------------------------
extract_paths() {
  local file="$1"
  local prefix_re='(crates|scripts|sdks|bins|web|examples|migrations|\.github)'

  # Backtick spans and inline references.
  # Exclude ] to avoid capturing the label part of Markdown link syntax
  # [label/path](url) — without the ] exclusion the label bleeds into the url.
  grep -oE "${prefix_re}/[^][:space:]\`\"')},;]+" "$file" 2>/dev/null || true

  # Markdown links  [text](path)
  grep -oE "\]\(${prefix_re}/[^)]+\)" "$file" 2>/dev/null \
    | sed 's/^](\(.*\))$/\1/' || true
}

# ---------------------------------------------------------------------------
# sanitize <raw_path>
# Strips trailing line-reference suffixes (:LINE or :LINE-LINE) and stray
# punctuation left by the regex (e.g. trailing period or comma in prose).
# ---------------------------------------------------------------------------
sanitize() {
  # printf '%s\n' ensures a trailing newline so macOS sed outputs a complete
  # newline-terminated line even when chaining multiple sed filters.
  printf '%s\n' "$1" \
    | sed "s/:[0-9][0-9]*[-,][0-9][0-9]*$//" \
    | sed "s/:[0-9][0-9]*$//" \
    | sed "s/'$//" \
    | sed "s/[.,;:]\$//"
}

# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
step "collecting markdown doc files"

DOC_FILES=()
[[ -f "$root/README.md" ]]      && DOC_FILES+=("$root/README.md")
[[ -f "$root/CONTRIBUTING.md" ]] && DOC_FILES+=("$root/CONTRIBUTING.md")
[[ -f "$root/ARCHITECTURE.md" ]] && DOC_FILES+=("$root/ARCHITECTURE.md")

# docs/**/*.md
while IFS= read -r -d '' f; do
  DOC_FILES+=("$f")
done < <(find "$root/docs" -name "*.md" -print0 2>/dev/null)

echo "  docs scanned: ${#DOC_FILES[@]}"

step "extracting and checking path references"

# Collect all raw candidate paths, sanitize, sort+dedup, then check.
# (Avoid bash 4+ associative arrays — macOS ships bash 3.2.)
tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT

RAW_LIST="$tmpdir/raw.txt"

for docfile in "${DOC_FILES[@]}"; do
  extract_paths "$docfile"
done > "$RAW_LIST"

# Sanitize, sort, and deduplicate
DEDUPED="$tmpdir/deduped.txt"
while IFS= read -r raw; do
  [[ -z "$raw" ]] && continue
  sanitize "$raw"
done < "$RAW_LIST" | sort -u > "$DEDUPED"

missing=0
checked=0
skipped=0

while IFS= read -r path; do
  [[ -z "$path" ]] && continue

  # Apply skip list
  if should_skip "$path"; then
    skipped=$((skipped + 1))
    continue
  fi

  checked=$((checked + 1))

  if [[ ! -e "$root/$path" ]]; then
    # Find first doc that referenced this path for context
    ref_doc=$(grep -rlF "$path" "${DOC_FILES[@]}" 2>/dev/null | head -1)
    rel_doc="${ref_doc#$root/}"
    printf 'MISSING  %-60s  (in %s)\n' "$path" "$rel_doc" >&2
    missing=$((missing + 1))
  fi

done < "$DEDUPED"

echo
echo "  unique paths checked : $checked"
echo "  skipped (planned/glob): $skipped"

echo
if [[ "$missing" -gt 0 ]]; then
  printf 'PATH DRIFT: %d missing path(s) found in docs.\n' "$missing" >&2
  if [[ "$DRY_RUN" -eq 1 ]]; then
    echo "(--dry-run: not failing)" >&2
    exit 0
  fi
  exit 1
fi

echo "OK: all $checked checked doc paths exist in the working tree."
