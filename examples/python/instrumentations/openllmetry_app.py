"""OpenLLMetry -> Beater fixture app (R11.2).

Emits an LLM trace using the **OpenLLMetry** (Traceloop) `gen_ai.*` semantic
conventions over stock OpenTelemetry OTLP/gRPC. Beater ingests `gen_ai.*`
attributes natively, so no Beater SDK is required.

Run a local beaterd (`docker compose up`) and then:

    pip install opentelemetry-sdk opentelemetry-exporter-otlp-proto-grpc
    python examples/python/instrumentations/openllmetry_app.py
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
    return trace.get_tracer("beater.example.openllmetry")


def main() -> None:
    tracer = build_tracer()
    release = os.getenv("BEATER_RELEASE_ID", "openllmetry-example")

    # OpenLLMetry uses the OTel `gen_ai.*` semantic conventions for LLM calls.
    with tracer.start_as_current_span(
        "openai.chat",
        attributes={
            "gen_ai.system": "openai",
            "gen_ai.request.model": "gpt-4o-mini",
            "gen_ai.response.model": "gpt-4o-mini",
            "gen_ai.usage.input_tokens": 42,
            "gen_ai.usage.output_tokens": 18,
            "beater.span.kind": "llm.call",
            "beater.release_id": release,
            "input.value": "summarize the refund policy",
            "output.value": "Refunds within 30 days; this order is outside the window.",
        },
    ):
        pass

    provider = trace.get_tracer_provider()
    provider.force_flush()  # type: ignore[attr-defined]
    provider.shutdown()  # type: ignore[attr-defined]
    print("OpenLLMetry trace flushed -- open the dashboard to inspect it")


if __name__ == "__main__":
    main()
