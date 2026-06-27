"""Plain OpenTelemetry GenAI -> Beater fixture app (R11.2).

The most vendor-neutral path: stock OpenTelemetry with the official OTel
`gen_ai.*` semantic conventions and no LLM-vendor instrumentation library at all.
This is the "zero-SDK OTLP onboarding" baseline -- if you already export OTel
spans, you point the exporter at beaterd and you are done.

Run a local beaterd (`docker compose up`) and then:

    pip install opentelemetry-sdk opentelemetry-exporter-otlp-proto-grpc
    python examples/python/instrumentations/otel_genai_app.py
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
    return trace.get_tracer("beater.example.otel-genai")


def main() -> None:
    tracer = build_tracer()
    release = os.getenv("BEATER_RELEASE_ID", "otel-genai-example")

    with tracer.start_as_current_span(
        "agent.run",
        attributes={"beater.span.kind": "agent.run", "beater.release_id": release},
    ):
        with tracer.start_as_current_span(
            "chat gpt-4o-mini",
            attributes={
                # Official OpenTelemetry GenAI semantic conventions.
                "gen_ai.operation.name": "chat",
                "gen_ai.system": "openai",
                "gen_ai.request.model": "gpt-4o-mini",
                "gen_ai.usage.input_tokens": 30,
                "gen_ai.usage.output_tokens": 12,
                "beater.span.kind": "llm.call",
                "beater.release_id": release,
            },
        ):
            pass

    provider = trace.get_tracer_provider()
    provider.force_flush()  # type: ignore[attr-defined]
    provider.shutdown()  # type: ignore[attr-defined]
    print("OTel GenAI trace flushed -- open the dashboard to inspect it")


if __name__ == "__main__":
    main()
