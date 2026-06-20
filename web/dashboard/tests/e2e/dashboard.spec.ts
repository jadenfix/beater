import { expect, test } from "@playwright/test";

test("renders a stock OTLP llm span through table, waterfall, detail, and I/O", async ({
  page
}) => {
  const traceParam = process.env.BEATER_E2E_TRACE_ID
    ? `&trace=${encodeURIComponent(process.env.BEATER_E2E_TRACE_ID)}`
    : "&kind=llm.call";
  await page.goto(`/?tenant=demo&project=demo&environment=local${traceParam}`);

  await expect(page.getByRole("heading", { name: "Agent Trace Debugger" })).toBeVisible();
  await expect(page.getByLabel("Traces")).toContainText("refund-agent-run");
  await expect(page.getByLabel("Traces")).toContainText("openai/gpt-demo");

  const waterfall = page.getByLabel("Agent span waterfall");
  for (const kind of [
    "agent.run",
    "agent.turn",
    "agent.plan",
    "agent.step",
    "retrieval.query",
    "memory.read",
    "guardrail.check",
    "llm.call",
    "tool.call",
    "mcp.request",
    "memory.write",
    "evaluator.run",
    "human.review",
    "replay.run"
  ]) {
    await expect(waterfall).toContainText(kind);
  }
  await expect(waterfall).toContainText("lookup-order-tool");

  await waterfall.getByText("call-policy-model").click();

  const detail = page.getByLabel("Span detail");
  await expect(detail).toContainText("openai/gpt-demo");
  await expect(detail).toContainText("Tokens");
  await expect(detail).toContainText("Latency");
  await expect(detail).toContainText("USD 0.002500");
  await expect(detail).toContainText("Can this order be refunded after 31 days?");
  await expect(detail).toContainText("Escalate because the order is outside the standard window.");
});
