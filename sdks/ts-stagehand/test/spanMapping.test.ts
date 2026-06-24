import { afterEach, beforeEach, describe, expect, it } from "vitest";
import { trace, type Tracer } from "@opentelemetry/api";
import {
  BasicTracerProvider,
  InMemorySpanExporter,
  SimpleSpanProcessor,
  type ReadableSpan,
} from "@opentelemetry/sdk-trace-base";

import { instrumentStagehand, resolveEndpoint, resolvePage } from "../src/index.js";
import { BeaterStagehandTracer } from "../src/tracer.js";
import { BrowserAttr, SpanKind, BEATER_SPAN_KIND } from "../src/semconv.js";

/** A duck-typed Stagehand page that needs no real browser. */
function makeMockPage(opts: {
  url?: string;
  title?: string;
  actResult?: unknown;
  observeResult?: unknown;
  extractResult?: unknown;
  throwOn?: "act" | "observe" | "extract";
} = {}) {
  const calls: { method: string; args: unknown[] }[] = [];
  const page = {
    url: () => opts.url ?? "https://example.com/page",
    title: async () => opts.title ?? "Example Page",
    act: async (...args: unknown[]) => {
      calls.push({ method: "act", args });
      if (opts.throwOn === "act") throw new Error("act boom");
      return opts.actResult ?? { success: true };
    },
    observe: async (...args: unknown[]) => {
      calls.push({ method: "observe", args });
      if (opts.throwOn === "observe") throw new Error("observe boom");
      return opts.observeResult ?? [{ selector: "#cta" }];
    },
    extract: async (...args: unknown[]) => {
      calls.push({ method: "extract", args });
      if (opts.throwOn === "extract") throw new Error("extract boom");
      return opts.extractResult ?? { extraction: "hello" };
    },
  };
  return { page, calls };
}

let exporter: InMemorySpanExporter;
let provider: BasicTracerProvider;
let tracer: Tracer;

beforeEach(() => {
  exporter = new InMemorySpanExporter();
  provider = new BasicTracerProvider();
  provider.addSpanProcessor(new SimpleSpanProcessor(exporter));
  tracer = provider.getTracer("test");
});

afterEach(async () => {
  await provider.shutdown();
});

function spansByName(name: string): ReadableSpan[] {
  return exporter.getFinishedSpans().filter((s) => s.name === name);
}

describe("instrumentStagehand span mapping", () => {
  it("emits a tool.call span for act with canonical browser.* attributes", async () => {
    const { page } = makeMockPage({ url: "https://shop.test/cart" });
    instrumentStagehand({ page }, { tracer });

    await (page as any).act("click checkout");

    const spans = spansByName("browser.act");
    expect(spans).toHaveLength(1);
    const attrs = spans[0]!.attributes;
    expect(attrs[BEATER_SPAN_KIND]).toBe(SpanKind.TOOL_CALL);
    expect(attrs[BrowserAttr.ACTION]).toBe("act");
    expect(attrs[BrowserAttr.URL]).toBe("https://shop.test/cart");
    expect(attrs[BrowserAttr.TITLE]).toBe("Example Page");
    expect(attrs[BrowserAttr.STEP_STATUS]).toBe("ok");
    expect(attrs[BrowserAttr.STEP_SEQ]).toBe(0);
    expect(attrs[BrowserAttr.ENGINE]).toBe("chromium");
    // selector hint pulled from the call argument
    expect(attrs[BrowserAttr.SELECTOR]).toBe("click checkout");
  });

  it("maps observe and extract to their own browser.action values", async () => {
    const { page } = makeMockPage();
    instrumentStagehand({ page }, { tracer });

    await (page as any).observe("find the login button");
    await (page as any).extract({ instruction: "the price" });

    const observe = spansByName("browser.observe");
    const extract = spansByName("browser.extract");
    expect(observe).toHaveLength(1);
    expect(extract).toHaveLength(1);
    expect(observe[0]!.attributes[BrowserAttr.ACTION]).toBe("observe");
    expect(extract[0]!.attributes[BrowserAttr.ACTION]).toBe("extract");
    // extract pulled selector hint from the `instruction` field
    expect(extract[0]!.attributes[BrowserAttr.SELECTOR]).toBe("the price");
  });

  it("assigns a monotonic step_seq across all primitives", async () => {
    const { page } = makeMockPage();
    instrumentStagehand({ page }, { tracer });

    await (page as any).act("a");
    await (page as any).observe("b");
    await (page as any).extract({ instruction: "c" });

    const toolCalls = exporter
      .getFinishedSpans()
      .filter((s) => s.attributes[BEATER_SPAN_KIND] === SpanKind.TOOL_CALL)
      .sort(
        (x, y) =>
          (x.attributes[BrowserAttr.STEP_SEQ] as number) -
          (y.attributes[BrowserAttr.STEP_SEQ] as number),
      );
    expect(toolCalls.map((s) => s.attributes[BrowserAttr.STEP_SEQ])).toEqual([
      0, 1, 2,
    ]);
  });

  it("emits an llm.call span with browser.reasoning when the result carries a decision", async () => {
    const { page } = makeMockPage({
      observeResult: {
        reasoning: "The CTA button is the primary action on the page",
        selector: "#cta",
      },
    });
    instrumentStagehand({ page }, { tracer });

    await (page as any).observe("the main button");

    const decisions = exporter
      .getFinishedSpans()
      .filter((s) => s.attributes[BEATER_SPAN_KIND] === SpanKind.LLM_CALL);
    expect(decisions).toHaveLength(1);
    const attrs = decisions[0]!.attributes;
    expect(attrs[BrowserAttr.REASONING]).toBe(
      "The CTA button is the primary action on the page",
    );
    expect(attrs[BrowserAttr.SELECTOR]).toBe("#cta");
    expect(attrs[BrowserAttr.ACTION]).toBe("observe");

    // The parent tool.call span records grounding success.
    const tool = spansByName("browser.observe")[0]!;
    expect(tool.attributes[BrowserAttr.SELECTOR_EXISTED]).toBe(true);
    expect(tool.attributes[BrowserAttr.MATCHED_ELEMENT]).toBe(true);
    // llm.call is a child of the tool.call span.
    expect(decisions[0]!.parentSpanId).toBe(tool.spanContext().spanId);
  });

  it("does not emit an llm.call span when no decision is present", async () => {
    const { page } = makeMockPage({ actResult: { success: true } });
    instrumentStagehand({ page }, { tracer });

    await (page as any).act("scroll down");

    const decisions = exporter
      .getFinishedSpans()
      .filter((s) => s.attributes[BEATER_SPAN_KIND] === SpanKind.LLM_CALL);
    expect(decisions).toHaveLength(0);
  });

  it("marks step_status=error and records the exception on failure", async () => {
    const { page } = makeMockPage({ throwOn: "act" });
    instrumentStagehand({ page }, { tracer });

    await expect((page as any).act("click missing")).rejects.toThrow(
      "act boom",
    );

    const span = spansByName("browser.act")[0]!;
    expect(span.attributes[BrowserAttr.STEP_STATUS]).toBe("error");
    expect(span.status.code).toBe(2 /* ERROR */);
    expect(span.events.some((e) => e.name === "exception")).toBe(true);
  });

  it("preserves the original return value of the wrapped call", async () => {
    const { page } = makeMockPage({ extractResult: { title: "Widget" } });
    instrumentStagehand({ page }, { tracer });

    const result = await (page as any).extract({ instruction: "title" });
    expect(result).toEqual({ title: "Widget" });
  });

  it("respects a custom engine label", async () => {
    const { page } = makeMockPage();
    instrumentStagehand({ page }, { tracer, engine: "firefox" });
    await (page as any).act("x");
    expect(spansByName("browser.act")[0]!.attributes[BrowserAttr.ENGINE]).toBe(
      "firefox",
    );
  });

  it("instruments a Stagehand-like wrapper via .page", async () => {
    const { page } = makeMockPage();
    const stagehand = { page };
    instrumentStagehand(stagehand, { tracer });
    await (stagehand.page as any).observe("button");
    expect(spansByName("browser.observe")).toHaveLength(1);
  });

  it("is idempotent: re-instrumenting does not double-wrap", async () => {
    const { page } = makeMockPage();
    instrumentStagehand({ page }, { tracer });
    instrumentStagehand({ page }, { tracer });
    await (page as any).act("once");
    expect(spansByName("browser.act")).toHaveLength(1);
  });
});

describe("helpers", () => {
  it("resolveEndpoint prefers explicit opts, then env, then default", () => {
    expect(resolveEndpoint({ endpoint: "http://h:1" })).toBe("http://h:1");
    const prev = process.env.BEATER_OTLP_ENDPOINT;
    process.env.BEATER_OTLP_ENDPOINT = "http://env:2";
    expect(resolveEndpoint()).toBe("http://env:2");
    delete process.env.BEATER_OTLP_ENDPOINT;
    expect(resolveEndpoint()).toBe("http://localhost:4317");
    if (prev !== undefined) process.env.BEATER_OTLP_ENDPOINT = prev;
  });

  it("resolvePage finds primitives on a bare page or via .page", () => {
    const { page } = makeMockPage();
    expect(resolvePage(page)).toBe(page);
    expect(resolvePage({ page })).toBe(page);
    expect(resolvePage({ nothing: true } as any)).toBeUndefined();
  });

  it("throws when no instrumentable page is found", () => {
    expect(() => instrumentStagehand({ foo: 1 } as any, { tracer })).toThrow(
      /could not locate a page/,
    );
  });
});

describe("BeaterStagehandTracer direct usage", () => {
  it("can be constructed with an injected tracer and traces a call", async () => {
    const bt = new BeaterStagehandTracer({ tracer });
    const result = await bt.traceCall(
      "act",
      { url: () => "https://x.test", title: () => "X" },
      ["press enter"],
      async () => ({ success: true }),
    );
    expect(result).toEqual({ success: true });
    const span = spansByName("browser.act")[0]!;
    expect(span.attributes[BrowserAttr.URL]).toBe("https://x.test");
    expect(span.attributes[BrowserAttr.SELECTOR]).toBe("press enter");
  });
});
