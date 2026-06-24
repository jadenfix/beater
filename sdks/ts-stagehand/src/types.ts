import type { Tracer } from "@opentelemetry/api";

/**
 * Duck-typed Playwright page surface we read for span context.
 * Both real Playwright pages and test mocks satisfy this.
 */
export interface PageLike {
  url?: () => string | Promise<string>;
  title?: () => string | Promise<string>;
  act?: (...args: unknown[]) => unknown;
  observe?: (...args: unknown[]) => unknown;
  extract?: (...args: unknown[]) => unknown;
  [key: string]: unknown;
}

/**
 * Duck-typed Stagehand instance. Real `Stagehand` exposes `.page`; we accept a
 * bare page too so callers can instrument either object.
 */
export interface StagehandLike {
  page?: PageLike;
  [key: string]: unknown;
}

export interface InstrumentOptions {
  /**
   * OTLP gRPC endpoint. Defaults to `BEATER_OTLP_ENDPOINT` env var, then
   * `http://localhost:4317`.
   */
  endpoint?: string;
  /** Logical service name reported on the OTLP resource. */
  serviceName?: string;
  /**
   * Provide an existing tracer instead of bootstrapping a new OTLP pipeline.
   * Used by tests (with an in-memory exporter) and by apps that already run an
   * OpenTelemetry SDK.
   */
  tracer?: Tracer;
  /** Browser engine label for `browser.engine`. Defaults to `chromium`. */
  engine?: string;
}

/** A model decision captured from a Stagehand call, surfaced as an `llm.call` span. */
export interface ModelDecision {
  /** Reasoning / thoughts text → `browser.reasoning`. */
  reasoning?: string;
  /** Optional selector the model grounded to → `browser.selector`. */
  selector?: string;
  /** Optional instruction text the decision acted on (span name detail). */
  instruction?: string;
}
