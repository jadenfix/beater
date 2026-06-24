/** `observe` higher-order wrapper and `span` helper. */

import { context, Span, SpanStatusCode, trace } from "@opentelemetry/api";

import { Attr, SpanKind, SpanKindValue } from "./semconv";
import { getConfig, getTracer } from "./tracing";

let seq = 0;

function toValue(obj: unknown): string {
  if (typeof obj === "string") return obj;
  try {
    return JSON.stringify(obj);
  } catch {
    return String(obj);
  }
}

function applyCommon(span: Span, kind: SpanKindValue): void {
  span.setAttribute(Attr.SPAN_KIND, kind);
  span.setAttribute(Attr.SEQ, ++seq);
  const config = getConfig();
  if (config?.releaseId) {
    span.setAttribute(Attr.RELEASE_ID, config.releaseId);
  }
}

export function setInput(value: unknown): void {
  const span = trace.getActiveSpan();
  if (span) span.setAttribute(Attr.INPUT_VALUE, toValue(value));
}

export function setOutput(value: unknown): void {
  const span = trace.getActiveSpan();
  if (span) span.setAttribute(Attr.OUTPUT_VALUE, toValue(value));
}

export interface SpanOptions {
  kind?: SpanKindValue;
  input?: unknown;
  attributes?: Record<string, string | number | boolean>;
}

/** Run `fn` inside a Beater span, recording status and re-raising errors. */
export async function span<T>(
  name: string,
  options: SpanOptions,
  fn: (span: Span) => Promise<T> | T,
): Promise<T> {
  const tracer = getTracer();
  return tracer.startActiveSpan(name, async (current) => {
    applyCommon(current, options.kind ?? SpanKind.AGENT_STEP);
    if (options.input !== undefined) current.setAttribute(Attr.INPUT_VALUE, toValue(options.input));
    for (const [key, val] of Object.entries(options.attributes ?? {})) {
      current.setAttribute(key, val);
    }
    try {
      const result = await fn(current);
      current.setStatus({ code: SpanStatusCode.OK });
      return result;
    } catch (err) {
      current.setStatus({ code: SpanStatusCode.ERROR, message: String(err) });
      current.recordException(err as Error);
      throw err;
    } finally {
      current.end();
    }
  });
}

export interface ObserveOptions {
  name?: string;
  kind?: SpanKindValue;
  captureInput?: boolean;
  captureOutput?: boolean;
}

/**
 * Wrap a function so each call becomes a Beater span. Works for sync and async
 * functions (the returned function is always async-safe).
 *
 *   const call = observe(rawCall, { kind: SpanKind.LLM_CALL });
 */
export function observe<A extends unknown[], R>(
  fn: (...args: A) => Promise<R> | R,
  options: ObserveOptions = {},
): (...args: A) => Promise<R> {
  const name = options.name ?? fn.name ?? "anonymous";
  const kind = options.kind ?? SpanKind.AGENT_STEP;
  const captureInput = options.captureInput ?? true;
  const captureOutput = options.captureOutput ?? true;

  return async (...args: A): Promise<R> => {
    const tracer = getTracer();
    return tracer.startActiveSpan(name, async (current) => {
      applyCommon(current, kind);
      if (captureInput && args.length > 0) current.setAttribute(Attr.INPUT_VALUE, toValue(args));
      try {
        const result = await fn(...args);
        if (captureOutput && result !== undefined) {
          current.setAttribute(Attr.OUTPUT_VALUE, toValue(result));
        }
        current.setStatus({ code: SpanStatusCode.OK });
        return result;
      } catch (err) {
        current.setStatus({ code: SpanStatusCode.ERROR, message: String(err) });
        current.recordException(err as Error);
        throw err;
      } finally {
        current.end();
      }
    });
  };
}

export { context };
export const _internal = { toValue, applyCommon };
