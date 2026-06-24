/**
 * Canonical `browser.*` semantic-convention attribute keys.
 *
 * These MUST match the Rust source of truth
 * (`crates/beater-browser/src/semconv.rs`) exactly so Beater's OTLP ingest
 * (`beater-otlp`) normalizes spans from this SDK identically to the native
 * capture layer and the other instrumentation SDKs.
 */
export const BrowserAttr = {
  /** Browser engine that executed the step (e.g. `chromium`, `firefox`, `webkit`). */
  ENGINE: "browser.engine",
  /** Action verb for the step (e.g. `act`, `observe`, `extract`). */
  ACTION: "browser.action",
  /** Target selector for the action, when the action targets an element. */
  SELECTOR: "browser.selector",
  /** URL the page was on when the step executed. */
  URL: "browser.url",
  /** Page title observed for the step. */
  TITLE: "browser.title",
  /** Whether the action's selector resolved to an element in the DOM. */
  SELECTOR_EXISTED: "browser.selector_existed",
  /** Whether the resolved element was the intended target (grounding success). */
  MATCHED_ELEMENT: "browser.matched_element",
  /** Monotonic step sequence number within the agent run. */
  STEP_SEQ: "browser.step_seq",
  /** Step status string (`ok` or `error`). */
  STEP_STATUS: "browser.step_status",
  /** Artifact id of the stored DOM snapshot for the step. */
  DOM_ARTIFACT: "browser.dom_artifact_id",
  /** Artifact id of the stored screenshot for the step. */
  SCREENSHOT_ARTIFACT: "browser.screenshot_artifact_id",
  /** The agent's reasoning text for the decision. */
  REASONING: "browser.reasoning",
} as const;

/** Step status values used for `browser.step_status`. */
export const StepStatus = {
  OK: "ok",
  ERROR: "error",
} as const;

/**
 * Beater span-kind attribute. `beater-otlp` reads this key (alongside
 * `openinference.span.kind` / `gen_ai.operation.name`) to classify the agent
 * span kind. We set it explicitly so wrapped calls map to `tool.call` and model
 * decisions map to `llm.call`.
 */
export const BEATER_SPAN_KIND = "beater.span.kind";

/** Agent span-kind values recognized by `beater-otlp`. */
export const SpanKind = {
  TOOL_CALL: "tool.call",
  LLM_CALL: "llm.call",
} as const;

/** The three Stagehand AI primitives this SDK instruments. */
export type BrowserActionName = "act" | "observe" | "extract";
