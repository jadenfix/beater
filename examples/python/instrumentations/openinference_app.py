"""OpenInference -> Beater fixture app (R11.2).

Emits a small agent trace using the **OpenInference** semantic-convention
attributes (the convention used by Arize Phoenix and friends) over stock
OpenTelemetry OTLP/gRPC. Beater ingests OpenInference attributes natively, so no
Beater SDK is required -- this is the zero-SDK onboarding path.

Run a local beaterd (`docker compose up`) and then:

    pip install opentelemetry-sdk opentelemetry-exporter-otlp-proto-grpc
    python examples/python/instrumentations/openinference_app.py

Open the dashboard and click the trace: you should see an agent.run -> llm.call
waterfall with model, tokens, cost, and redacted-capable input/output.
"""

import os

from opentelemetry import trace
from opentelemetry.exporter.otlp.proto.grpc.trace_exporter import OTLPSpanExporter
from opentelemetry.sdk.trace import TracerProvider
from opentelemetry.sdk.trace.export import BatchSpanProcessor


def build_tracer() -> trace.Tracer:
    provider = TracerProvider()
    provider.add_span_processor(
        BatchSpanProcessor(
            OTLPSpanExporter(
                endpoint=os.getenv("OTEL_EXPORTER_OTLP_ENDPOINT", "http://127.0.0.1:4317"),
                insecure=True,
                headers=(
                    ("x-beater-tenant-id", os.getenv("BEATER_TENANT_ID", "demo")),
                    ("x-beater-project-id", os.getenv("BEATER_PROJECT_ID", "demo")),
                    ("x-beater-environment-id", os.getenv("BEATER_ENVIRONMENT_ID", "local")),
                ),
            )
        )
    )
    trace.set_tracer_provider(provider)
    return trace.get_tracer("beater.example.openinference")


def main() -> None:
    tracer = build_tracer()
    release = os.getenv("BEATER_RELEASE_ID", "openinference-example")

    # OpenInference uses `openinference.span.kind` to mark agent/LLM/tool spans.
    with tracer.start_as_current_span(
        "handle_refund",
        attributes={
            "openinference.span.kind": "AGENT",
            "beater.span.kind": "agent.run",
            "beater.release_id": release,
            "input.value": "late delivery refund after 31 days",
        },
    ):
        with tracer.start_as_current_span(
            "call_model",
            attributes={
                "openinference.span.kind": "LLM",
                "beater.span.kind": "llm.call",
                "llm.provider": "openai",
                "llm.model_name": "gpt-4o-mini",
                "llm.token_count.prompt": 42,
                "llm.token_count.completion": 18,
                "llm.cost.amount_micros": 1200,
                "llm.cost.currency": "USD",
                "input.value": "look up refund policy and decide",
                "output.value": "Escalate: order is outside the standard refund window.",
                "beater.release_id": release,
            },
        ):
            pass

    provider = trace.get_tracer_provider()
    provider.force_flush()  # type: ignore[attr-defined]
    provider.shutdown()  # type: ignore[attr-defined]
    print("OpenInference trace flushed -- open the dashboard to inspect it")


if __name__ == "__main__":
    main()
