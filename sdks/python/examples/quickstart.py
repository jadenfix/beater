"""Five-line Beater quickstart: instrument an agent and emit a trace.

Run a local beaterd (e.g. `docker compose up`), then:

    BEATER_TENANT_ID=demo BEATER_PROJECT_ID=demo BEATER_ENVIRONMENT_ID=local \
        python examples/quickstart.py

Then open the dashboard and click the trace.
"""

import beater
from beater import SpanKind


@beater.observe(kind=SpanKind.AGENT_RUN)
def handle_refund(query: str) -> str:
    plan = make_plan(query)
    return call_model(plan)


@beater.observe(kind=SpanKind.AGENT_PLAN)
def make_plan(query: str) -> str:
    return f"look up policy for: {query}"


@beater.observe(kind=SpanKind.LLM_CALL)
def call_model(plan: str) -> str:
    # In a real app: beater.wrap_openai(OpenAI()).chat.completions.create(...)
    beater.set_output("Escalate: order is outside the standard refund window.")
    return "escalate"


if __name__ == "__main__":
    beater.init(service_name="beater-python-quickstart", release_id="quickstart")
    result = handle_refund("late delivery refund after 31 days")
    print(f"agent result: {result}")
    beater.flush()
    print("trace flushed -- open the dashboard to inspect it")
