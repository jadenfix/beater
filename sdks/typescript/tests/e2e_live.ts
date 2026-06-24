// Live E2E: TS SDK -> beaterd OTLP/HTTP -> read API. Run by scripts/e2e-sdk-live-ts.sh
// against a running beaterd. Exit 0 = pass.

import { trace } from "@opentelemetry/api";

import * as beater from "../src/index";
import { SpanKind } from "../src/semconv";

const BASE_URL = (process.env.BEATER_BASE_URL ?? "http://127.0.0.1:18080").replace(/\/+$/, "");
const TENANT = process.env.BEATER_TENANT_ID ?? "demo";

async function getJson(path: string): Promise<any> {
  const res = await fetch(`${BASE_URL}${path}`);
  if (!res.ok) throw new Error(`${path} -> ${res.status}`);
  return res.json();
}

async function main(): Promise<number> {
  beater.init({ serviceName: "beater-e2e-ts", releaseId: "e2e-ts" });

  let traceId = "";
  const run = beater.observe(
    async () => {
      traceId = trace.getActiveSpan()!.spanContext().traceId;
      const plan = beater.observe(async () => beater.setOutput("plan"), {
        kind: SpanKind.AGENT_PLAN,
        name: "ts-plan",
      });
      await plan();
      const llm = beater.observe(
        async () => {
          const s = trace.getActiveSpan()!;
          s.setAttribute("llm.provider", "anthropic");
          s.setAttribute("llm.model_name", "claude-e2e");
          s.setAttribute("llm.token_count.prompt", 9);
          s.setAttribute("llm.token_count.completion", 4);
          beater.setOutput("done");
        },
        { kind: SpanKind.LLM_CALL, name: "ts-llm" },
      );
      await llm();
    },
    { kind: SpanKind.AGENT_RUN, name: "ts-run" },
  );

  await run();
  await beater.flush();
  console.log(`emitted trace_id=${traceId}`);

  const deadline = Date.now() + 30_000;
  let traceView: any;
  while (Date.now() < deadline) {
    try {
      traceView = await getJson(`/v1/traces/${TENANT}/${traceId}`);
      if (traceView?.spans?.length) break;
    } catch {
      /* retry */
    }
    await new Promise((r) => setTimeout(r, 1000));
  }

  if (!traceView?.spans?.length) {
    console.error("FAIL: trace never became queryable");
    return 1;
  }
  const kinds = new Set<string>(traceView.spans.map((s: any) => s.kind));
  console.log(`landed spans: ${traceView.spans.length} kinds=${[...kinds].sort()}`);
  for (const k of ["agent.run", "agent.plan", "llm.call"]) {
    if (!kinds.has(k)) {
      console.error(`FAIL: missing kind ${k}`);
      return 1;
    }
  }
  console.log("PASS: TS SDK -> beaterd -> read API round-trip verified");
  return 0;
}

process.on("unhandledRejection", (reason) => {
  console.error("background rejection (non-fatal export retry?):", reason);
});

main()
  .then((code) => process.exit(code))
  .catch((err) => {
    console.error("FATAL in main:", err);
    process.exit(1);
  });
