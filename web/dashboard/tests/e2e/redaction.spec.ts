import { expect, test } from "@playwright/test";

const rawPrompt = "customer SSN 123-45-6789";
const rawCard = "4242-4242-4242-4242";
const rawCompletion = "route the sensitive customer account to privacy review";
const unmaskReason = "gate2-redaction-review";

test("proves redacted I/O hides by default and unmask is reasoned", async ({ page }) => {
  const traceId = process.env.BEATER_E2E_REDACTION_TRACE_ID;
  const spanId = process.env.BEATER_E2E_REDACTION_SPAN_ID;
  const release = process.env.BEATER_E2E_REDACTION_RELEASE;
  const traceParam = traceId
    ? `&trace=${encodeURIComponent(traceId)}`
    : `&kind=llm.call&model=gpt-redaction${
        release ? `&release=${encodeURIComponent(release)}` : ""
      }`;

  await page.goto(`/?tenant=demo&project=demo&environment=local${traceParam}`);
  await expect(page.getByRole("heading", { name: "Agent Trace Debugger" })).toBeVisible();

  const traceList = page.getByLabel("Traces");
  await expect(traceList).toContainText("sensitive-redaction-review");
  await expect(traceList).toContainText("openai/gpt-redaction");

  const waterfall = page.getByLabel("Agent span waterfall");
  const llm = spanId
    ? waterfall.locator(`[data-span-id="${spanId}"]`)
    : waterfall.locator('[data-kind="llm.call"]').filter({ hasText: "sensitive-redaction-review" });
  await expect(llm).toHaveCount(1);
  await expect(llm).toHaveAttribute("data-kind", "llm.call");
  await expect(llm).toHaveAttribute("data-depth", "0");
  await llm.click();

  const detail = page.getByLabel("Span detail");
  await expect(detail).toContainText("openai/gpt-redaction");
  await expect(detail).toContainText("18 total, 10 prompt, 8 completion");
  await expect(detail).toContainText("USD 0.000700");

  const promptIo = detail.getByLabel("Prompt I/O");
  const completionIo = detail.getByLabel("Completion I/O");
  await expect(detail.getByLabel("Span I/O")).toContainText("redacted");
  await expect(promptIo).toContainText("redacted by policy");
  await expect(completionIo).toContainText("redacted by policy");
  await expect(page.locator("body")).not.toContainText(rawPrompt);
  await expect(page.locator("body")).not.toContainText(rawCard);
  expect(await page.content()).not.toContain(rawCard);

  const form = detail.getByLabel("Unmask redacted I/O");
  await expect(form).toBeVisible();
  await form.getByLabel("Reason").fill(unmaskReason);
  await form.getByRole("button", { name: "Unmask" }).click();

  await expect(page).toHaveURL(/unmask=true/);
  await expect(page).toHaveURL(new RegExp(`reason=${unmaskReason}`));
  await expect(detail).toContainText("Unmask requested");
  await expect(detail).toContainText(unmaskReason);
  await expect(promptIo).toContainText(rawPrompt);
  await expect(promptIo).toContainText(rawCard);
  await expect(completionIo).toContainText(rawCompletion);
  await expect(detail.getByRole("link", { name: "Redacted view" })).toBeVisible();

  await detail.getByRole("link", { name: "Redacted view" }).click();
  await expect(page).not.toHaveURL(/unmask=true/);
  await expect(detail.getByLabel("Span I/O")).toContainText("redacted");
  await expect(promptIo).toContainText("redacted by policy");
  await expect(completionIo).toContainText("redacted by policy");
  await expect(page.locator("body")).not.toContainText(rawCard);
});
