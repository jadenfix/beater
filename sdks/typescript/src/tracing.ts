/** Tracer setup: configure an OpenTelemetry pipeline that exports to Beater. */

import { trace, Tracer } from "@opentelemetry/api";
import { OTLPTraceExporter } from "@opentelemetry/exporter-trace-otlp-proto";
import { Resource } from "@opentelemetry/resources";
import { BatchSpanProcessor, NodeTracerProvider } from "@opentelemetry/sdk-trace-node";
import type { SpanExporter } from "@opentelemetry/sdk-trace-base";

import { BeaterConfig, BeaterOptions, otlpHttpTracesUrl, resolveConfig } from "./config";

const TRACER_NAME = "beater.sdk";

let currentConfig: BeaterConfig | undefined;
let currentProvider: NodeTracerProvider | undefined;

/**
 * Initialize the Beater tracer. Call once at process start. All options fall
 * back to `BEATER_*` env vars, so `init()` works with no args when configured.
 *
 * `options.exporter` overrides the default OTLP exporter (used for tests/advanced
 * pipelines).
 */
export function init(options: BeaterOptions & { exporter?: SpanExporter } = {}): BeaterConfig {
  const config = resolveConfig(options);
  const headers: Record<string, string> = {};
  if (config.apiKey) {
    headers["authorization"] = `Bearer ${config.apiKey}`;
  }

  const exporter: SpanExporter =
    options.exporter ??
    // compression: "none" — beaterd's OTLP endpoint expects uncompressed protobuf.
    new OTLPTraceExporter({ url: otlpHttpTracesUrl(config), headers, compression: "none" as never });
  const provider = new NodeTracerProvider({
    resource: new Resource({ "service.name": config.serviceName }),
    spanProcessors: [new BatchSpanProcessor(exporter)],
  });
  provider.register();

  currentProvider = provider;
  currentConfig = config;
  return config;
}

export function getConfig(): BeaterConfig | undefined {
  return currentConfig;
}

export function getTracer(): Tracer {
  if (!currentConfig) {
    init();
  }
  return trace.getTracer(TRACER_NAME);
}

export async function flush(): Promise<void> {
  if (currentProvider) {
    await currentProvider.forceFlush();
  }
}

export async function shutdown(): Promise<void> {
  if (currentProvider) {
    await currentProvider.shutdown();
  }
}
