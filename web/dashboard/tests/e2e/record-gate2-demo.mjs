import { chromium } from "@playwright/test";
import { copyFile, mkdir, rm, writeFile } from "node:fs/promises";
import { dirname, join, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const dashboardRoot = resolve(dirname(fileURLToPath(import.meta.url)), "../..");
const repoRoot = resolve(dashboardRoot, "../..");
const baseUrl = process.env.PLAYWRIGHT_BASE_URL ?? "http://127.0.0.1:3000";
const traceParam = process.env.BEATER_E2E_TRACE_ID
  ? `&trace=${encodeURIComponent(process.env.BEATER_E2E_TRACE_ID)}`
  : "&kind=llm.call";
const demoDir = resolve(repoRoot, "docs/demos");
const scratchDir = resolve(dashboardRoot, "test-results/gate2-demo-video");
const videoPath = join(demoDir, "gate2-browser-demo.webm");
const notesPath = join(demoDir, "gate2-browser-demo.md");

await rm(scratchDir, { force: true, recursive: true });
await mkdir(scratchDir, { recursive: true });
await mkdir(demoDir, { recursive: true });

const browser = await chromium.launch();
const context = await browser.newContext({
  recordVideo: {
    dir: scratchDir,
    size: { width: 1440, height: 1000 }
  },
  viewport: { width: 1440, height: 1000 }
});
const page = await context.newPage();

await page.goto(`${baseUrl}/?tenant=demo&project=demo&environment=local${traceParam}`);
await page.getByRole("heading", { name: "Agent Trace Debugger" }).waitFor();
const waterfall = page.getByLabel("Agent span waterfall");
await requireAttribute(waterfall.locator('[data-span-name="refund-agent-run"]'), "data-depth", "0");
await requireAttribute(waterfall.locator('[data-span-name="customer-refund-turn"]'), "data-depth", "1");
await requireAttribute(waterfall.locator('[data-span-name="execute-refund-step"]'), "data-depth", "2");
await requireAttribute(waterfall.locator('[data-span-name="lookup-order-tool"]'), "data-depth", "3");
await requireAttribute(waterfall.locator('[data-span-name="mcp-order-service"]'), "data-depth", "4");
await requireAttribute(
  waterfall.locator('[data-span-name="call-policy-model"] .kind-icon'),
  "data-icon",
  "llm"
);
await requireAttribute(
  waterfall.locator('[data-span-name="mcp-order-service"] .kind-icon'),
  "data-icon",
  "mcp"
);
await waterfall.getByText("call-policy-model").click();
const detail = page.getByLabel("Span detail");
await detail
  .locator(".io")
  .filter({ hasText: "Input" })
  .getByText("Can this order be refunded after 31 days?")
  .waitFor();
await page.waitForTimeout(1000);
await page.getByLabel("Agent span waterfall").getByText("lookup-order-tool").click();
await detail.locator(".io").filter({ hasText: "Input" }).getByText("ord_123").waitFor();
await page.waitForTimeout(1000);

const video = page.video();
await context.close();
await browser.close();

if (!video) {
  throw new Error("Playwright did not produce a video artifact");
}

await copyFile(await video.path(), videoPath);
await writeFile(
  notesPath,
  `# Gate 2 Browser Demo

Recorded from the stock OpenTelemetry Python trace produced by \`examples/python/otel_smoke.py\`.

- Artifact: \`gate2-browser-demo.webm\`
- Dashboard: \`${baseUrl}/?tenant=demo&project=demo&environment=local${traceParam}\`
- Shows: trace table, color/icon-coded all-kind agent waterfall, run -> turn -> step -> tool -> MCP nesting, \`llm.call\` prompt/completion/model/tokens/cost/latency, and tool-call I/O.

Regenerate with:

\`\`\`bash
BEATER_GATE2_RECORD_DEMO=1 scripts/gate2-proof.sh
\`\`\`

For the Docker Compose stopwatch proof that uses the literal five-line snippet,
run the prebuilt-image path:

\`\`\`bash
BEATER_GATE2_WRITE_PROOF=1 KEEP_BEATER_COMPOSE=0 scripts/gate2-compose-stopwatch.sh
\`\`\`

For a local source build measurement, add \`BEATER_GATE2_LOCAL_BUILD=1\`.
`
);

console.log(`Recorded Gate 2 browser demo to ${videoPath}`);

async function requireAttribute(locator, name, expected) {
  await locator.waitFor();
  const actual = await locator.getAttribute(name);
  if (actual !== expected) {
    throw new Error(`expected ${name}=${expected}, got ${actual}`);
  }
}
