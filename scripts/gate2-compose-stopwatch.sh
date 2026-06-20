#!/usr/bin/env bash
set -euo pipefail

project="${COMPOSE_PROJECT_NAME:-beater-stopwatch}"
keep="${KEEP_BEATER_COMPOSE:-1}"
reuse="${BEATER_GATE2_REUSE:-0}"
write_proof="${BEATER_GATE2_WRITE_PROOF:-0}"
proof_path="${BEATER_GATE2_STOPWATCH_PROOF:-docs/demos/gate2-compose-stopwatch.md}"
venv_dir="${BEATER_GATE2_QUICKSTART_VENV:-/tmp/beater-gate2-compose-otel-venv}"
local_build="${BEATER_GATE2_LOCAL_BUILD:-0}"
browser_proof="${BEATER_GATE2_BROWSER_PROOF:-0}"
prebuilt_pull_policy="${BEATER_GATE2_PULL_POLICY:-always}"
host_http_port="${BEATER_HTTP_PORT:-8080}"
host_otlp_grpc_port="${BEATER_OTLP_GRPC_PORT:-4317}"
host_dashboard_port="${BEATER_DASHBOARD_PORT:-3000}"
api_url="http://127.0.0.1:$host_http_port"
otlp_url="http://127.0.0.1:$host_otlp_grpc_port"
dashboard_base_url="http://127.0.0.1:$host_dashboard_port"
start_epoch="$(date +%s)"
deadline_epoch=$((start_epoch + 300))
started_at="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"
quickstart_browser_proof_status="not requested"
waterfall_browser_proof_status="not requested"
time_to_quickstart_click_seconds=""
all_kind_trace_id=""
all_kind_dashboard_url=""
git_sha="$(git rev-parse HEAD 2>/dev/null || echo unknown)"
os_arch="$(uname -sm 2>/dev/null || echo unknown)"
docker_version="$(docker --version 2>/dev/null || echo unknown)"
compose_version="$(docker compose version 2>/dev/null || echo unknown)"
all_kinds=(
  agent.run
  agent.turn
  agent.plan
  agent.step
  retrieval.query
  memory.read
  guardrail.check
  llm.call
  tool.call
  mcp.request
  memory.write
  evaluator.run
  human.review
  replay.run
)
if [[ "$local_build" == "1" ]]; then
  compose_files=(-f docker-compose.yml)
  startup_mode="local-build"
  startup_args=(up -d --build postgres nats minio beaterd dashboard)
else
  compose_files=(-f docker-compose.prebuilt.yml)
  startup_mode="prebuilt-image"
  startup_args=(up -d --pull "$prebuilt_pull_policy" postgres nats minio beaterd dashboard)
fi

compose() {
  docker compose "${compose_files[@]}" -p "$project" "$@"
}

cleanup() {
  if [[ "$keep" != "1" ]]; then
    compose down -v --remove-orphans >/dev/null 2>&1 || true
  fi
}

clean_start() {
  if [[ "$reuse" == "1" ]]; then
    return 0
  fi
  compose down -v --remove-orphans >/dev/null 2>&1 || true
  rm -rf "$venv_dir"
}

terminate_tree() {
  local pid="$1"
  local child
  for child in $(pgrep -P "$pid" 2>/dev/null || true); do
    terminate_tree "$child"
  done
  kill "$pid" 2>/dev/null || true
}

kill_tree() {
  local pid="$1"
  local child
  for child in $(pgrep -P "$pid" 2>/dev/null || true); do
    kill_tree "$child"
  done
  kill -9 "$pid" 2>/dev/null || true
}

run_before_deadline() {
  local label="$1"
  shift
  "$@" &
  local pid=$!
  while kill -0 "$pid" 2>/dev/null; do
    if (( $(date +%s) >= deadline_epoch )); then
      echo "Timed out during $label after 300s" >&2
      terminate_tree "$pid"
      sleep 2
      kill_tree "$pid"
      wait "$pid" 2>/dev/null || true
      return 1
    fi
    sleep 1
  done
  wait "$pid"
}

wait_url() {
  local url="$1"
  local label="$2"
  until curl -fsS "$url" >/tmp/beater-stopwatch-response 2>/tmp/beater-stopwatch-error; do
    if (( $(date +%s) >= deadline_epoch )); then
      echo "Timed out waiting for $label at $url" >&2
      cat /tmp/beater-stopwatch-error >&2 || true
      return 1
    fi
    sleep 2
  done
}

require_text() {
  local url="$1"
  local needle="$2"
  local body
  body="$(curl -fsS "$url")"
  if [[ "$body" != *"$needle"* ]]; then
    echo "Expected '$needle' in $url" >&2
    return 1
  fi
}

wait_text() {
  local url="$1"
  local needle="$2"
  local label="$3"
  until require_text "$url" "$needle" >/dev/null 2>&1; do
    if (( $(date +%s) >= deadline_epoch )); then
      echo "Timed out waiting for $label to contain '$needle' at $url" >&2
      require_text "$url" "$needle"
      return 1
    fi
    sleep 2
  done
}

first_trace_id() {
  python3 -c 'import json,sys; print(json.load(sys.stdin)["items"][0]["trace_id"])'
}

trap cleanup EXIT

run_before_deadline "clean previous Gate 2 state" clean_start
run_before_deadline "compose startup ($startup_mode)" compose "${startup_args[@]}"
wait_url "$api_url/health" "beaterd"
wait_url "$dashboard_base_url/?tenant=demo&project=demo&environment=local" "dashboard"

run_before_deadline "Python virtualenv creation" python3 -m venv "$venv_dir"
run_before_deadline "pip upgrade" "$venv_dir/bin/pip" install --quiet --upgrade pip
run_before_deadline "OTEL package install" "$venv_dir/bin/pip" install --quiet opentelemetry-sdk opentelemetry-exporter-otlp-proto-grpc
run_before_deadline "five-line OTEL snippet" env OTEL_EXPORTER_OTLP_ENDPOINT="$otlp_url" "$venv_dir/bin/python" examples/python/five_line_otel.py

quickstart_query="$api_url/v1/traces/demo?project_id=demo&environment_id=local&kind=llm.call&model=gpt-quickstart"
wait_text "$quickstart_query" "gpt-quickstart" "five-line OTEL trace"
trace_id="$(curl -fsS "$quickstart_query" | first_trace_id)"
dashboard_url="$dashboard_base_url/?tenant=demo&project=demo&environment=local&trace=$trace_id"

wait_text "$dashboard_url" "Agent Trace Debugger" "dashboard"
wait_text "$dashboard_url" "five-line-llm-call" "dashboard quickstart trace"
wait_text "$dashboard_url" "gpt-quickstart" "dashboard model detail"
wait_text "$dashboard_url" "hello from stock OpenTelemetry" "dashboard prompt detail"
time_to_first_trace_seconds=$(($(date +%s) - start_epoch))

if [[ "$browser_proof" == "1" ]]; then
  (
    cd web/dashboard
    run_before_deadline "dashboard browser proof npm install" npm ci
    run_before_deadline "dashboard browser proof chromium install" npx playwright install chromium
    run_before_deadline "five-line dashboard browser proof" env BEATER_E2E_TRACE_ID="$trace_id" PLAYWRIGHT_BASE_URL="$dashboard_base_url" npm run test:e2e:quickstart
  )
  quickstart_browser_proof_status="passed"
  time_to_quickstart_click_seconds=$(($(date +%s) - start_epoch))
  if (( time_to_quickstart_click_seconds > 300 )); then
    echo "Time-to-quickstart-click exceeded 300s: ${time_to_quickstart_click_seconds}s" >&2
    exit 1
  fi

  run_before_deadline "stock Python all-kind OTEL fixture" env OTEL_EXPORTER_OTLP_ENDPOINT="$otlp_url" "$venv_dir/bin/python" examples/python/otel_smoke.py

  all_kind_query="$api_url/v1/traces/demo?project_id=demo&environment_id=local&kind=llm.call&model=gpt-demo&release=compose-demo"
  wait_text "$all_kind_query" "gpt-demo" "stock Python all-kind OTEL trace"
  all_kind_trace_id="$(curl -fsS "$all_kind_query" | first_trace_id)"
  all_kind_dashboard_url="$dashboard_base_url/?tenant=demo&project=demo&environment=local&trace=$all_kind_trace_id"
  wait_text "$all_kind_dashboard_url" "call-policy-model" "dashboard all-kind llm.call"
  for kind in "${all_kinds[@]}"; do
    wait_text "$all_kind_dashboard_url" "$kind" "dashboard all-kind waterfall"
  done

  (
    cd web/dashboard
    run_before_deadline "all-kind waterfall browser proof" env BEATER_E2E_TRACE_ID="$all_kind_trace_id" PLAYWRIGHT_BASE_URL="$dashboard_base_url" npx playwright test tests/e2e/dashboard.spec.ts
  )
  waterfall_browser_proof_status="passed"
fi

ended_at="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"
duration_seconds=$(($(date +%s) - start_epoch))
image_summary="$(compose images 2>/dev/null || true)"
if (( time_to_first_trace_seconds > 300 )); then
  echo "Time-to-first-trace exceeded 300s: ${time_to_first_trace_seconds}s" >&2
  exit 1
fi
if (( duration_seconds > 300 )); then
  echo "Total proof duration exceeded 300s: ${duration_seconds}s" >&2
  exit 1
fi

if [[ "$write_proof" == "1" ]]; then
  mkdir -p "$(dirname "$proof_path")"
  cat >"$proof_path" <<EOF
# Gate 2 Compose Stopwatch Proof

- Started: $started_at
- Ended: $ended_at
- Time-to-first-trace: ${time_to_first_trace_seconds}s
- Time-to-quickstart-click: ${time_to_quickstart_click_seconds:-not requested}
- Total duration: ${duration_seconds}s
- Limit: 300s
- Git SHA: \`$git_sha\`
- OS/arch: \`$os_arch\`
- Docker: \`$docker_version\`
- Docker Compose: \`$compose_version\`
- Startup mode: $startup_mode
- Clean start: $([[ "$reuse" == "1" ]] && echo "no" || echo "yes")
- Reuse override: \`BEATER_GATE2_REUSE=$reuse\`
- Prebuilt pull policy: \`$prebuilt_pull_policy\`
- Compose project: $project
- Quickstart snippet: \`examples/python/five_line_otel.py\`
- OTLP endpoint: \`$otlp_url\`
- Quickstart trace: \`$trace_id\`
- Quickstart dashboard: $dashboard_url
- Quickstart browser proof: $quickstart_browser_proof_status
- All-kind nested trace: \`${all_kind_trace_id:-not requested}\`
- All-kind dashboard: ${all_kind_dashboard_url:-not requested}
- All-kind waterfall browser proof: $waterfall_browser_proof_status

## Compose Images

\`\`\`text
$image_summary
\`\`\`

This is an automated local stopwatch proof. The mandate still requires an
outside-person run to fully close Gate 2.

Regenerate:

\`\`\`bash
BEATER_GATE2_WRITE_PROOF=1 BEATER_GATE2_BROWSER_PROOF=1 KEEP_BEATER_COMPOSE=0 scripts/gate2-compose-stopwatch.sh
\`\`\`
EOF
fi

cat <<EOF
Gate 2 compose stopwatch passed in ${time_to_first_trace_seconds}s to first trace (${duration_seconds}s total).

Time to quickstart browser click:
  ${time_to_quickstart_click_seconds:-not requested}

Open the dashboard:
  $dashboard_url

All-kind waterfall dashboard:
  ${all_kind_dashboard_url:-not requested}

Five-line snippet:
  examples/python/five_line_otel.py

OTLP endpoint:
  $otlp_url

Startup mode:
  $startup_mode

Clean start:
  $([[ "$reuse" == "1" ]] && echo "no (BEATER_GATE2_REUSE=1)" || echo "yes")

Set KEEP_BEATER_COMPOSE=0 to tear containers down automatically.
Set BEATER_GATE2_LOCAL_BUILD=1 to build images from local source instead of
pulling prebuilt GHCR images.
Set BEATER_GATE2_REUSE=1 to skip the pre-run Compose down/volume removal and
Python virtualenv deletion for local warm-loop debugging only.
Set BEATER_GATE2_BROWSER_PROOF=1 to run the Playwright browser proof for the
five-line quickstart trace and all-kind nested agent waterfall inside the same
300s stopwatch window.
EOF
