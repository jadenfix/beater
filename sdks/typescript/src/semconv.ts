/**
 * Beater semantic conventions — the single place the TS SDK defines span-kind
 * and attribute keys. Every wrapper imports from here so instrumentation cannot
 * drift within the SDK. These mirror the Rust normalizer (`crates/beater-otlp`)
 * and canonical kinds (`crates/beater-schema`); keep them in lockstep.
 */

export const SpanKind = {
  AGENT_RUN: "agent.run",
  AGENT_TURN: "agent.turn",
  AGENT_PLAN: "agent.plan",
  AGENT_STEP: "agent.step",
  LLM_CALL: "llm.call",
  TOOL_CALL: "tool.call",
  MCP_REQUEST: "mcp.request",
  RETRIEVAL_QUERY: "retrieval.query",
  MEMORY_READ: "memory.read",
  MEMORY_WRITE: "memory.write",
  GUARDRAIL_CHECK: "guardrail.check",
} as const;

export type SpanKindValue = (typeof SpanKind)[keyof typeof SpanKind];

export const SPAN_KINDS: ReadonlySet<string> = new Set(Object.values(SpanKind));

export const Attr = {
  SPAN_KIND: "openinference.span.kind",
  SEQ: "beater.seq",
  RELEASE_ID: "agent.release_id",
  INPUT_VALUE: "input.value",
  OUTPUT_VALUE: "output.value",
  LLM_PROVIDER: "llm.provider",
  LLM_MODEL_NAME: "llm.model_name",
  LLM_TOKEN_PROMPT: "llm.token_count.prompt",
  LLM_TOKEN_COMPLETION: "llm.token_count.completion",
  LLM_TOKEN_REASONING: "llm.token_count.reasoning",
  LLM_TOKEN_CACHE_READ: "llm.token_count.cache_read",
  LLM_COST_MICROS: "llm.cost.amount_micros",
  LLM_COST_CURRENCY: "llm.cost.currency",
} as const;

export const HEADER_TENANT = "x-beater-tenant-id";
export const HEADER_PROJECT = "x-beater-project-id";
export const HEADER_ENVIRONMENT = "x-beater-environment-id";
