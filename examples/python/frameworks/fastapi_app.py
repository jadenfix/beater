"""FastAPI + OTLP -> Beater example app (R11.4).

A minimal FastAPI service whose request handler emits an agent trace to beaterd
over stock OpenTelemetry OTLP/gRPC. Demonstrates the Python framework adoption
path through standards (no Beater SDK).

Run a local beaterd (`docker compose up`) and then:

    pip install fastapi uvicorn opentelemetry-sdk opentelemetry-exporter-otlp-proto-grpc
    uvicorn examples.python.frameworks.fastapi_app:app --port 8000
    curl -X POST localhost:8000/agent -d '{"prompt":"refund please"}' -H 'content-type: application/json'

Open the dashboard and click the trace.
"""

import os

from fastapi import FastAPI
from opentelemetry import trace
from opentelemetry.exporter.otlp.proto.grpc.trace_exporter import OTLPSpanExporter
from opentelemetry.sdk.trace import TracerProvider
from opentelemetry.sdk.trace.export import BatchSpanProcessor

_provider = TracerProvider()
_provider.add_span_processor(
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
trace.set_tracer_provider(_provider)
_tracer = trace.get_tracer("beater.example.fastapi")

app = FastAPI(title="beater-fastapi-example")


@app.post("/agent")
def run_agent(body: dict) -> dict:
    prompt = body.get("prompt", "")
    release = os.getenv("BEATER_RELEASE_ID", "fastapi-example")
    with _tracer.start_as_current_span(
        "handle_request",
        attributes={"beater.span.kind": "agent.run", "beater.release_id": release, "input.value": prompt},
    ):
        with _tracer.start_as_current_span(
            "call_model",
            attributes={
                "beater.span.kind": "llm.call",
                "llm.provider": "openai",
                "llm.model_name": "gpt-4o-mini",
                "beater.release_id": release,
                "input.value": prompt,
                "output.value": "ok",
            },
        ):
            decision = "escalate"
    return {"decision": decision}
