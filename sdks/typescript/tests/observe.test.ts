import assert from "node:assert";
import { test } from "node:test";

import { InMemorySpanExporter } from "@opentelemetry/sdk-trace-base";

import * as beater from "../src/index";
import { Attr, SpanKind, SPAN_KINDS } from "../src/semconv";
import { wrapOpenAI } from "../src/providers/openai";

// OTel's global registration is process-wide, so init() once and reset between tests.
const exporter = new InMemorySpanExporter();
beater.init({ tenantId: "t", projectId: "p", environmentId: "e", releaseId: "rel-1", exporter });

function setup(): InMemorySpanExporter {
  exporter.reset();
  return exporter;
}

function byName(spans: ReturnType<InMemorySpanExporter["getFinishedSpans"]>, name: string) {
  const span = spans.find((s) => s.name === name);
  assert.ok(span, `expected a span named ${name}`);
  return span!;
}

test("observe records kind, release, and output", async () => {
  const exporter = setup();
  const call = beater.observe(async (prompt: string) => `answer:${prompt}`, {
    kind: SpanKind.LLM_CALL,
    name: "call",
  });
  const result = await call("hi");
  assert.equal(result, "answer:hi");
  await beater.flush();

  const span = byName(exporter.getFinishedSpans(), "call");
  assert.equal(span.attributes[Attr.SPAN_KIND], SpanKind.LLM_CALL);
  assert.equal(span.attributes[Attr.RELEASE_ID], "rel-1");
  assert.match(String(span.attributes[Attr.OUTPUT_VALUE]), /answer:hi/);
});

test("observe records errors", async () => {
  const exporter = setup();
  const boom = beater.observe(
    async () => {
      throw new Error("nope");
    },
    { name: "boom" },
  );
  await assert.rejects(boom());
  await beater.flush();
  const span = byName(exporter.getFinishedSpans(), "boom");
  assert.equal(span.status.code, 2 /* ERROR */);
});

test("wrapOpenAI emits llm.call span with tokens", async () => {
  const exporter = setup();
  const client = wrapOpenAI({
    chat: {
      completions: {
        create: async () => ({
          model: "gpt-4.1",
          usage: { prompt_tokens: 11, completion_tokens: 7 },
          choices: [{ message: { content: "hello there" } }],
        }),
      },
    },
  } as any);

  await client.chat.completions.create({ model: "gpt-4.1", messages: [{ role: "user", content: "hi" }] });
  await beater.flush();

  const span = byName(exporter.getFinishedSpans(), "openai.chat.completions.create");
  assert.equal(span.attributes[Attr.LLM_PROVIDER], "openai");
  assert.equal(span.attributes[Attr.LLM_MODEL_NAME], "gpt-4.1");
  assert.equal(span.attributes[Attr.LLM_TOKEN_PROMPT], 11);
  assert.equal(span.attributes[Attr.LLM_TOKEN_COMPLETION], 7);
  assert.match(String(span.attributes[Attr.OUTPUT_VALUE]), /hello there/);
});

test("semconv kinds match the server normalizer set", () => {
  const expected = new Set([
    "agent.run", "agent.turn", "agent.plan", "agent.step", "llm.call",
    "tool.call", "mcp.request", "retrieval.query", "memory.read",
    "memory.write", "guardrail.check",
  ]);
  assert.deepEqual(new Set(SPAN_KINDS), expected);
});
