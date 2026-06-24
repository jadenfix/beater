"""Live end-to-end test: Python SDK -> beaterd OTLP -> read API.

Emits a real agent trace through the ergonomic SDK, then queries the running
beaterd HTTP API to prove the trace landed and the span kinds/attributes
normalized correctly. Driven by scripts/e2e-sdk-live.sh against a live server.

Exit code 0 = pass.
"""

import json
import os
import sys
import time
import urllib.request

from opentelemetry import trace as otel_trace

import beater
from beater import SpanKind

BASE_URL = os.environ["BEATER_BASE_URL"].rstrip("/")
TENANT = os.environ.get("BEATER_TENANT_ID", "demo")


def get_json(path: str):
    with urllib.request.urlopen(f"{BASE_URL}{path}", timeout=10) as resp:
        return json.loads(resp.read().decode())


def emit_trace() -> str:
    beater.init(service_name="beater-e2e", release_id="e2e")
    captured = {}

    @beater.observe(kind=SpanKind.AGENT_RUN, name="e2e-run")
    def run():
        captured["trace_id"] = format(
            otel_trace.get_current_span().get_span_context().trace_id, "032x"
        )
        plan()
        call_model()

    @beater.observe(kind=SpanKind.AGENT_PLAN, name="e2e-plan")
    def plan():
        beater.set_output("plan: look up policy")

    @beater.observe(kind=SpanKind.LLM_CALL, name="e2e-llm")
    def call_model():
        span = otel_trace.get_current_span()
        span.set_attribute("llm.provider", "openai")
        span.set_attribute("llm.model_name", "gpt-e2e")
        span.set_attribute("llm.token_count.prompt", 12)
        span.set_attribute("llm.token_count.completion", 5)
        beater.set_output("escalate")

    run()
    beater.flush()
    return captured["trace_id"]


def main() -> int:
    trace_id = emit_trace()
    print(f"emitted trace_id={trace_id}")

    # Poll the read API until the trace is queryable (ingest is async/buffered).
    deadline = time.time() + 30
    trace = None
    while time.time() < deadline:
        try:
            trace = get_json(f"/v1/traces/{TENANT}/{trace_id}")
            if trace.get("spans"):
                break
        except Exception:
            pass
        time.sleep(1)

    if not trace or not trace.get("spans"):
        print("FAIL: trace never became queryable", file=sys.stderr)
        return 1

    kinds = {s["kind"] for s in trace["spans"]}
    print(f"landed spans: {len(trace['spans'])} kinds={sorted(kinds)}")

    expected = {"agent.run", "agent.plan", "llm.call"}
    missing = expected - kinds
    if missing:
        print(f"FAIL: missing span kinds {missing}", file=sys.stderr)
        return 1

    llm = next((s for s in trace["spans"] if s["kind"] == "llm.call"), None)
    if not llm or not llm.get("model") or not llm.get("tokens"):
        print(f"FAIL: llm span missing model/tokens: {llm}", file=sys.stderr)
        return 1

    print("PASS: SDK -> beaterd -> read API round-trip verified")
    print(f"  llm model={llm['model']} tokens={llm['tokens']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
