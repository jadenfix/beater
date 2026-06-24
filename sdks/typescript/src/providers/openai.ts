/** Drop-in OpenAI instrumentation: `const client = wrapOpenAI(new OpenAI())`. */

import { SpanStatusCode } from "@opentelemetry/api";

import { Attr, SpanKind } from "../semconv";
import { getTracer } from "../tracing";
import { _internal } from "../observe";

const { toValue, applyCommon } = _internal;

/* eslint-disable @typescript-eslint/no-explicit-any */

function recordUsage(span: any, response: any): void {
  const usage = response?.usage;
  if (!usage) return;
  if (usage.prompt_tokens != null) span.setAttribute(Attr.LLM_TOKEN_PROMPT, Number(usage.prompt_tokens));
  if (usage.completion_tokens != null) span.setAttribute(Attr.LLM_TOKEN_COMPLETION, Number(usage.completion_tokens));
  const reasoning = usage.completion_tokens_details?.reasoning_tokens;
  if (reasoning != null) span.setAttribute(Attr.LLM_TOKEN_REASONING, Number(reasoning));
}

function outputText(response: any): string {
  try {
    const choice = response.choices?.[0];
    return choice?.message?.content ?? choice?.text ?? "";
  } catch {
    return "";
  }
}

/** Instrument an OpenAI client in place and return it. */
export function wrapOpenAI<T extends Record<string, any>>(client: T): T {
  if ((client as any)._beaterWrapped) return client;
  const completions = client.chat.completions;
  const original = completions.create.bind(completions);

  completions.create = async function create(...args: any[]): Promise<any> {
    const params = args[0] ?? {};
    const tracer = getTracer();
    return tracer.startActiveSpan("openai.chat.completions.create", async (span: any) => {
      applyCommon(span, SpanKind.LLM_CALL);
      span.setAttribute(Attr.LLM_PROVIDER, "openai");
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
