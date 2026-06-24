/** Drop-in Anthropic instrumentation: `const client = wrapAnthropic(new Anthropic())`. */

import { SpanStatusCode } from "@opentelemetry/api";

import { Attr, SpanKind } from "../semconv";
import { getTracer } from "../tracing";
import { _internal } from "../observe";

const { toValue, applyCommon } = _internal;

/* eslint-disable @typescript-eslint/no-explicit-any */

function recordUsage(span: any, response: any): void {
  const usage = response?.usage;
  if (!usage) return;
  if (usage.input_tokens != null) span.setAttribute(Attr.LLM_TOKEN_PROMPT, Number(usage.input_tokens));
  if (usage.output_tokens != null) span.setAttribute(Attr.LLM_TOKEN_COMPLETION, Number(usage.output_tokens));
  if (usage.cache_read_input_tokens != null) {
    span.setAttribute(Attr.LLM_TOKEN_CACHE_READ, Number(usage.cache_read_input_tokens));
  }
}

function outputText(response: any): string {
  try {
    const blocks = response.content ?? [];
    return blocks.map((b: any) => b?.text ?? "").join("");
  } catch {
    return "";
  }
}

/** Instrument an Anthropic client in place and return it. */
export function wrapAnthropic<T extends Record<string, any>>(client: T): T {
  if ((client as any)._beaterWrapped) return client;
  const messages = client.messages;
  const original = messages.create.bind(messages);

  messages.create = async function create(...args: any[]): Promise<any> {
    const params = args[0] ?? {};
    const tracer = getTracer();
    return tracer.startActiveSpan("anthropic.messages.create", async (span: any) => {
      applyCommon(span, SpanKind.LLM_CALL);
      span.setAttribute(Attr.LLM_PROVIDER, "anthropic");
      span.setAttribute(Attr.LLM_MODEL_NAME, String(params.model ?? "unknown"));
      if (params.messages) span.setAttribute(Attr.INPUT_VALUE, toValue(params.messages));
      try {
        const response = await original(...args);
        if (response?.model) span.setAttribute(Attr.LLM_MODEL_NAME, String(response.model));
        recordUsage(span, response);
        span.setAttribute(Attr.OUTPUT_VALUE, outputText(response));
        span.setStatus({ code: SpanStatusCode.OK });
        return response;
      } catch (err) {
        span.setStatus({ code: SpanStatusCode.ERROR, message: String(err) });
        span.recordException(err as Error);
        throw err;
      } finally {
        span.end();
      }
    });
  };

  (client as any)._beaterWrapped = true;
  return client;
}
