import { expect, test } from "@playwright/test";

test("renders a stock OTLP llm span through table, waterfall, detail, and I/O", async ({
  page
}) => {
  const traceParam = process.env.BEATER_E2E_TRACE_ID
    ? `&trace=${encodeURIComponent(process.env.BEATER_E2E_TRACE_ID)}`
    : "&kind=llm.call&model=gpt-demo&release=compose-demo";
  await page.goto(`/?tenant=demo&project=demo&environment=local${traceParam}`);

  await expect(page.getByRole("heading", { name: "Agent Trace Debugger" })).toBeVisible();
  const traceList = page.getByLabel("Traces");
  await expect(traceList).toContainText("Spans");
  await expect(traceList).toContainText("Latency");
  await expect(traceList).toContainText("Release");
  await expect(traceList).toContainText("refund-agent-run");
  await expect(traceList).toContainText("openai/gpt-demo");

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

  const run = waterfall.locator('[data-span-name="refund-agent-run"]');
  const turn = waterfall.locator('[data-span-name="customer-refund-turn"]');
  const step = waterfall.locator('[data-span-name="execute-refund-step"]');
  const tool = waterfall.locator('[data-span-name="lookup-order-tool"]');
  const mcp = waterfall.locator('[data-span-name="mcp-order-service"]');

  await expect(run).toHaveAttribute("data-kind", "agent.run");
  await expect(turn).toHaveAttribute("data-kind", "agent.turn");
  await expect(step).toHaveAttribute("data-kind", "agent.step");
  await expect(tool).toHaveAttribute("data-kind", "tool.call");
  await expect(mcp).toHaveAttribute("data-kind", "mcp.request");
  await expect(run).toHaveAttribute("data-depth", "0");
  await expect(turn).toHaveAttribute("data-depth", "1");
  await expect(step).toHaveAttribute("data-depth", "2");
  await expect(tool).toHaveAttribute("data-depth", "3");
  await expect(mcp).toHaveAttribute("data-depth", "4");
  await expect(run.locator(".kind-icon")).toHaveAttribute("data-icon", "agent-run");
  await expect(waterfall.locator('[data-span-name="call-policy-model"] .kind-icon')).toHaveAttribute(
    "data-icon",
    "llm"
  );
  await expect(waterfall.locator('[data-span-name="call-policy-model"] .span-track')).toBeVisible();
  await expect(waterfall.locator('[data-span-name="call-policy-model"] .span-bar')).toBeVisible();
  await expect(tool.locator(".kind-icon")).toHaveAttribute("data-icon", "tool");
  await expect(mcp.locator(".kind-icon")).toHaveAttribute("data-icon", "mcp");

  const orderedNames = await waterfall.locator("[data-span-name]").evaluateAll((rows) =>
    rows.map((row) => row.getAttribute("data-span-name"))
  );
  expect(orderedNames.indexOf("refund-agent-run")).toBeLessThan(
    orderedNames.indexOf("customer-refund-turn")
  );
  expect(orderedNames.indexOf("customer-refund-turn")).toBeLessThan(
    orderedNames.indexOf("execute-refund-step")
  );
  expect(orderedNames.indexOf("execute-refund-step")).toBeLessThan(
    orderedNames.indexOf("lookup-order-tool")
  );
  expect(orderedNames.indexOf("lookup-order-tool")).toBeLessThan(
    orderedNames.indexOf("mcp-order-service")
  );

  await waterfall.getByText("call-policy-model").click();

  const detail = page.getByLabel("Span detail");
  await expect(detail).toContainText("openai/gpt-demo");
  await expect(detail).toContainText("Tokens");
  await expect(detail).toContainText("Latency");
  await expect(detail).toContainText("USD 0.002500");
  await expect(detail).toContainText("Can this order be refunded after 31 days?");
  await expect(detail).toContainText("Escalate because the order is outside the standard window.");
});
