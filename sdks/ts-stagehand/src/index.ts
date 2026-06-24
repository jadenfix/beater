import type { Tracer } from "@opentelemetry/api";

import { BeaterStagehandTracer } from "./tracer.js";
import type {
  BrowserActionName,
} from "./semconv.js";
import type {
  InstrumentOptions,
  PageLike,
  StagehandLike,
} from "./types.js";

export { BeaterStagehandTracer } from "./tracer.js";
export {
  BrowserAttr,
  StepStatus,
  SpanKind,
  BEATER_SPAN_KIND,
} from "./semconv.js";
export type { BrowserActionName } from "./semconv.js";
export type {
  InstrumentOptions,
  ModelDecision,
  PageLike,
  StagehandLike,
} from "./types.js";

const DEFAULT_ENDPOINT = "http://localhost:4317";
const PRIMITIVES: BrowserActionName[] = ["act", "observe", "extract"];

/** Resolve the OTLP endpoint from opts → env → default. */
export function resolveEndpoint(opts?: InstrumentOptions): string {
  return (
    opts?.endpoint ??
    process.env.BEATER_OTLP_ENDPOINT ??
    DEFAULT_ENDPOINT
  );
}

/**
 * Lazily bootstrap an OTLP gRPC trace pipeline and return its tracer.
 *
 * Imports are dynamic so the heavy `@opentelemetry/sdk-node` /
 * `exporter-trace-otlp-grpc` dependencies are only loaded when an app actually
 * exports to Beater (tests inject their own in-memory tracer and never hit
 * this path).
 */
async function bootstrapTracer(opts: InstrumentOptions): Promise<Tracer> {
  const endpoint = resolveEndpoint(opts);
  const serviceName = opts.serviceName ?? "stagehand-browser-agent";

  const { NodeSDK } = await import("@opentelemetry/sdk-node");
  const { OTLPTraceExporter } = await import(
    "@opentelemetry/exporter-trace-otlp-grpc"
  );
  const { Resource } = await import("@opentelemetry/resources");
  const { SemanticResourceAttributes } = await import(
    "@opentelemetry/semantic-conventions"
  );
  const { trace } = await import("@opentelemetry/api");

  const sdk = new NodeSDK({
    resource: new Resource({
      [SemanticResourceAttributes.SERVICE_NAME]: serviceName,
    }),
    traceExporter: new OTLPTraceExporter({ url: endpoint }),
  });
  sdk.start();

  return trace.getTracer("@beater/stagehand-instrumentation", "0.1.0");
}

/**
 * Wrap a Stagehand instance (or a bare page) so every `page.act`,
 * `page.observe`, and `page.extract` call emits canonical Beater `browser.*`
 * spans over OTLP.
 *
 * The original methods are replaced in place; the same object is returned for
 * convenience. Re-instrumenting an already-instrumented page is a no-op.
 *
 * When `opts.tracer` is provided it is used directly (e.g. an in-memory
 * exporter in tests). Otherwise an OTLP gRPC pipeline to Beater is bootstrapped
 * asynchronously and instrumentation begins once it is ready.
 */
export function instrumentStagehand<T extends StagehandLike | PageLike>(
  target: T,
  opts: InstrumentOptions = {},
): T {
  const page = resolvePage(target);
  if (!page) {
    throw new Error(
      "instrumentStagehand: could not locate a page with act/observe/extract on the provided target",
    );
  }

  if (opts.tracer) {
    applyInstrumentation(
      page,
      new BeaterStagehandTracer({ tracer: opts.tracer, engine: opts.engine }),
    );
    return target;
  }

  // No tracer supplied: bootstrap OTLP. We wrap synchronously with a deferred
  // tracer so the returned object is usable immediately; calls made before the
  // pipeline finishes starting are buffered behind the promise.
  const pending = bootstrapTracer(opts).then(
    (tracer) =>
      new BeaterStagehandTracer({ tracer, engine: opts.engine }),
  );
  applyDeferredInstrumentation(page, pending);
  return target;
}

/** Find the page object that carries the AI primitives. */
export function resolvePage(
  target: StagehandLike | PageLike,
): PageLike | undefined {
  const candidate = target as PageLike;
  if (hasPrimitives(candidate)) return candidate;
  const nested = (target as StagehandLike).page;
  if (nested && hasPrimitives(nested)) return nested;
  return undefined;
}

function hasPrimitives(p: PageLike | undefined): p is PageLike {
  return (
    !!p &&
    PRIMITIVES.some((name) => typeof p[name] === "function")
  );
}

const INSTRUMENTED = Symbol.for("beater.stagehand.instrumented");

function applyInstrumentation(
  page: PageLike,
  tracer: BeaterStagehandTracer,
): void {
  if ((page as Record<symbol, unknown>)[INSTRUMENTED]) return;
  (page as Record<symbol, unknown>)[INSTRUMENTED] = true;

  for (const action of PRIMITIVES) {
    const original = page[action];
    if (typeof original !== "function") continue;
    const bound = original.bind(page) as (...a: unknown[]) => unknown;
    page[action] = function instrumented(...args: unknown[]) {
      return tracer.traceCall(action, page, args, () =>
        Promise.resolve(bound(...args)),
      );
    };
  }
}

function applyDeferredInstrumentation(
  page: PageLike,
  pending: Promise<BeaterStagehandTracer>,
): void {
  if ((page as Record<symbol, unknown>)[INSTRUMENTED]) return;
  (page as Record<symbol, unknown>)[INSTRUMENTED] = true;

  for (const action of PRIMITIVES) {
    const original = page[action];
    if (typeof original !== "function") continue;
    const bound = original.bind(page) as (...a: unknown[]) => unknown;
    page[action] = async function instrumented(...args: unknown[]) {
      const tracer = await pending;
      return tracer.traceCall(action, page, args, () =>
        Promise.resolve(bound(...args)),
      );
    };
  }
}
