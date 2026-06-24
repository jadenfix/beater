// Express + OTLP -> Beater example app (R11.4).
//
// A minimal Express service whose request handler emits an agent trace to
// beaterd over stock OpenTelemetry OTLP/HTTP. Demonstrates the TypeScript/JS
// framework adoption path through standards (no Beater SDK required).
//
// Run a local beaterd (`docker compose up`) and then:
//
//   npm install express @opentelemetry/api @opentelemetry/sdk-trace-node \
//     @opentelemetry/exporter-trace-otlp-proto @opentelemetry/resources
//   node examples/typescript/frameworks/express-otlp.mjs
//   curl -X POST localhost:8002/agent -H 'content-type: application/json' \
//     -d '{"prompt":"refund please"}'

import express from "express";
import { trace, SpanStatusCode } from "@opentelemetry/api";
import { NodeTracerProvider } from "@opentelemetry/sdk-trace-node";
import { BatchSpanProcessor } from "@opentelemetry/sdk-trace-base";
import { OTLPTraceExporter } from "@opentelemetry/exporter-trace-otlp-proto";

const endpoint =
  process.env.OTEL_EXPORTER_OTLP_ENDPOINT ?? "http://127.0.0.1:4317";
const headers = {
  "x-beater-tenant-id": process.env.BEATER_TENANT_ID ?? "demo",
  "x-beater-project-id": process.env.BEATER_PROJECT_ID ?? "demo",
  "x-beater-environment-id": process.env.BEATER_ENVIRONMENT_ID ?? "local",
};

const provider = new NodeTracerProvider();
provider.addSpanProcessor(
  new BatchSpanProcessor(new OTLPTraceExporter({ url: `${endpoint}/v1/traces`, headers })),
);
provider.register();
const tracer = trace.getTracer("beater.example.express");
const release = process.env.BEATER_RELEASE_ID ?? "express-example";

const app = express();
app.use(express.json());

app.post("/agent", (req, res) => {
  const prompt = req.body?.prompt ?? "";
  tracer.startActiveSpan(
    "handle_request",
    { attributes: { "beater.span.kind": "agent.run", "beater.release_id": release, "input.value": prompt } },
    (root) => {
      tracer.startActiveSpan(
        "call_model",
        {
          attributes: {
            "beater.span.kind": "llm.call",
            "llm.provider": "openai",
            "llm.model_name": "gpt-4o-mini",
            "beater.release_id": release,
            "input.value": prompt,
            "output.value": "ok",
          },
        },
        (llm) => {
          llm.setStatus({ code: SpanStatusCode.OK });
          llm.end();
        },
      );
      root.end();
      res.json({ decision: "escalate" });
    },
  );
});

const port = Number(process.env.PORT ?? 8002);
app.listen(port, () => console.log(`beater express example on :${port}`));
