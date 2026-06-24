/**
 * LangChain.js integration: a callback handler mapping runs to Beater spans.
 *
 *   import { BeaterCallbackHandler } from "@beater/sdk";
 *   await chain.invoke(input, { callbacks: [new BeaterCallbackHandler()] });
 *
 * Implemented structurally (duck-typed) so `@beater/sdk` does not hard-depend on
 * `@langchain/core`. Pass it anywhere a LangChain callback handler is accepted.
 */

import { context, Span, SpanStatusCode, trace } from "@opentelemetry/api";

import { Attr, SpanKind, SpanKindValue } from "../semconv";
import { getTracer } from "../tracing";
import { _internal } from "../observe";

const { toValue } = _internal;

/* eslint-disable @typescript-eslint/no-explicit-any */

export class BeaterCallbackHandler {
  name = "BeaterCallbackHandler";
  awaitHandlers = true;
  private spans = new Map<string, Span>();

  private start(runId: string, parentRunId: string | undefined, name: string, kind: SpanKindValue, input: unknown): void {
    const tracer = getTracer();
    const parent = parentRunId ? this.spans.get(parentRunId) : undefined;
    const ctx = parent ? trace.setSpan(context.active(), parent) : undefined;
    const span = ctx ? tracer.startSpan(name, undefined, ctx) : tracer.startSpan(name);
    span.setAttribute(Attr.SPAN_KIND, kind);
    if (input !== undefined && input !== null) span.setAttribute(Attr.INPUT_VALUE, toValue(input));
    this.spans.set(runId, span);
  }

  private end(runId: string, output?: unknown, error?: unknown): void {
    const span = this.spans.get(runId);
    if (!span) return;
    this.spans.delete(runId);
    if (output !== undefined && output !== null) span.setAttribute(Attr.OUTPUT_VALUE, toValue(output));
    if (error) {
      span.setStatus({ code: SpanStatusCode.ERROR, message: String(error) });
      span.recordException(error as Error);
    } else {
      span.setStatus({ code: SpanStatusCode.OK });
    }
    span.end();
  }

  handleChainStart(chain: any, inputs: any, runId: string, parentRunId?: string): void {
    this.start(runId, parentRunId, chain?.id?.slice?.(-1)?.[0] ?? "chain", SpanKind.AGENT_STEP, inputs);
  }
  handleChainEnd(outputs: any, runId: string): void {
    this.end(runId, outputs);
  }
  handleChainError(err: any, runId: string): void {
    this.end(runId, undefined, err);
  }

  handleLLMStart(llm: any, prompts: any, runId: string, parentRunId?: string): void {
    this.start(runId, parentRunId, "llm", SpanKind.LLM_CALL, prompts);
  }
  handleLLMEnd(output: any, runId: string): void {
    const span = this.spans.get(runId);
    if (span) {
      const usage = output?.llmOutput?.tokenUsage ?? output?.llmOutput?.usage;
      if (usage?.promptTokens != null) span.setAttribute(Attr.LLM_TOKEN_PROMPT, Number(usage.promptTokens));
      if (usage?.completionTokens != null) span.setAttribute(Attr.LLM_TOKEN_COMPLETION, Number(usage.completionTokens));
    }
    let text: string | undefined;
    try {
      text = output?.generations?.[0]?.[0]?.text;
    } catch {
      text = undefined;
    }
    this.end(runId, text);
  }
  handleLLMError(err: any, runId: string): void {
    this.end(runId, undefined, err);
  }

  handleToolStart(tool: any, input: any, runId: string, parentRunId?: string): void {
    this.start(runId, parentRunId, tool?.id?.slice?.(-1)?.[0] ?? "tool", SpanKind.TOOL_CALL, input);
  }
  handleToolEnd(output: any, runId: string): void {
    this.end(runId, output);
  }
  handleToolError(err: any, runId: string): void {
    this.end(runId, undefined, err);
  }

  handleRetrieverStart(retriever: any, query: any, runId: string, parentRunId?: string): void {
    this.start(runId, parentRunId, "retriever", SpanKind.RETRIEVAL_QUERY, query);
  }
  handleRetrieverEnd(documents: any, runId: string): void {
    this.end(runId, documents);
  }
  handleRetrieverError(err: any, runId: string): void {
    this.end(runId, undefined, err);
  }
}
