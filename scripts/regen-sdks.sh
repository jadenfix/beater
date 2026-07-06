#!/usr/bin/env bash
# Regenerate the OpenAPI spec and every control-plane SDK from it.
#
# This is the heart of the zero-drift guarantee: ONE spec
# (sdks/openapi/beater-api.json) is generated from the Rust handlers, and every
# Layer-1 client is generated from that spec. Run after any API change, then
# commit the result. CI runs `--check` to fail on drift.
#
# Requires Docker (openapi-generator runs in a pinned container -- no local Java).
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

# Pin the generator for reproducible output.
GENERATOR_IMAGE="openapitools/openapi-generator-cli:v7.11.0"
SPEC="sdks/openapi/beater-api.json"
LANGS=(rust python typescript go java c cpp)

CHECK_MODE=0
if [[ "${1:-}" == "--check" ]]; then
  CHECK_MODE=1
fi

# Optional release version for the generated clients (default keeps configs' 0.1.0).
VERSION="${BEATER_SDK_VERSION:-}"
version_props=()
if [[ -n "$VERSION" ]]; then
  version_props=(--additional-properties "packageVersion=$VERSION,artifactVersion=$VERSION,npmVersion=$VERSION")
fi

echo "==> Regenerating OpenAPI spec from beater-api handlers"
tmp_spec="$(mktemp "${TMPDIR:-/tmp}/beater-openapi.XXXXXX")"
trap 'rm -f "$tmp_spec"' EXIT
cargo run -q -p beater-api --example dump_openapi > "$tmp_spec"
mv "$tmp_spec" "$SPEC"
# Keep the dashboard snapshot identical to the canonical spec.
cp "$SPEC" web/dashboard/openapi/beater-read-api.json

echo "==> Pulling generator image ($GENERATOR_IMAGE)"
docker pull -q "$GENERATOR_IMAGE" >/dev/null

for lang in "${LANGS[@]}"; do
  out="sdks/clients/$lang"
  echo "==> Generating $lang -> $out"
  rm -rf "$out"
  mkdir -p "$out"
  # Run the generator as the host user so output isn't root-owned/read-only on Linux
  # CI runners (where the daemon runs as root); otherwise the patch step below cannot
  # write its temp files. No-op on Docker Desktop, which already maps to the host user.
  docker run --rm \
    --user "$(id -u):$(id -g)" \
    -v "$root:/local" \
    "$GENERATOR_IMAGE" generate \
    -i "/local/$SPEC" \
    -c "/local/sdks/config/$lang.yaml" \
    ${version_props[@]+"${version_props[@]}"} \
    -o "/local/$out" \
    >/dev/null

  # Reproducibly re-apply committed fixes for known openapi-generator output bugs
  # (C/C++ only). This keeps the generated clients buildable WITHOUT hand-editing
  # after each regen -- the patch is the single source of those fixes. Fail loudly
  # (no fuzz, no backups) if the patch no longer applies cleanly to fresh output.
  if [[ -f "sdks/patches/$lang.patch" ]]; then
    echo "    applying sdks/patches/$lang.patch"
    patch -p1 --fuzz=0 --no-backup-if-mismatch -d "$out" < "sdks/patches/$lang.patch"
    if find "$out" -name '*.rej' -o -name '*.orig' | grep -q .; then
      echo "ERROR: patch left .rej/.orig in $out -- patch is stale vs generated output" >&2
      exit 1
    fi
  fi

  # Some generators emit trailing spaces in changed model/docs templates.
  # Normalize only known touched files so `regen --check` and `git diff --check`
  # agree without masking unrelated generator churn.
  whitespace_files=()
  case "$lang" in
    c)
      whitespace_files=(
        "$out/docs/native_ingest_request.md"
        "$out/docs/page_run_summary_items_inner.md"
        "$out/docs/run_summary.md"
        "$out/model/native_ingest_request.c"
        "$out/model/page_run_summary_items_inner.c"
        "$out/model/run_summary.c"
      )
      ;;
    cpp)
      whitespace_files=(
        "$out/src/model/NativeIngestRequest.cpp"
        "$out/src/model/Page_RunSummary_items_inner.cpp"
        "$out/src/model/RunSummary.cpp"
      )
      ;;
    go)
      whitespace_files=(
        "$out/docs/NativeIngestRequest.md"
        "$out/docs/PageRunSummaryItemsInner.md"
        "$out/docs/RunSummary.md"
      )
      ;;
    java)
      whitespace_files=(
        "$out/src/main/java/ai/beater/client/model/AuditAction.java"
        "$out/src/main/java/ai/beater/client/model/NativeIngestRequest.java"
        "$out/src/main/java/ai/beater/client/model/PageRunSummaryItemsInner.java"
        "$out/src/main/java/ai/beater/client/model/RunSummary.java"
      )
      ;;
    python)
      whitespace_files=(
        "$out/docs/NativeIngestRequest.md"
        "$out/docs/PageRunSummaryItemsInner.md"
        "$out/docs/RunSummary.md"
        "$out/test/test_page_run_summary.py"
        "$out/test/test_page_run_summary_items_inner.py"
        "$out/test/test_run_summary.py"
      )
      ;;
    typescript)
      whitespace_files=(
        "$out/src/models/NativeIngestRequest.ts"
      )
      ;;
  esac
  if (( ${#whitespace_files[@]} > 0 )); then
    for generated_file in "${whitespace_files[@]}"; do
      if [[ -f "$generated_file" ]]; then
        perl -0pi -e 's/[ \t]+$//mg; s/\n+\z/\n/' "$generated_file"
      fi
    done
  fi
done

if [[ "$CHECK_MODE" == "1" ]]; then
  echo "==> Checking for drift"
  if ! git diff --quiet -- "$SPEC" web/dashboard/openapi/beater-read-api.json sdks/clients; then
    echo "ERROR: generated artifacts are stale. Run scripts/regen-sdks.sh and commit." >&2
    git --no-pager diff --stat -- "$SPEC" sdks/clients >&2
    exit 1
  fi
  echo "No drift: spec and all SDK clients are current."
fi

echo "Done. Layer-1 clients in sdks/clients/{${LANGS[*]// /,}}."
