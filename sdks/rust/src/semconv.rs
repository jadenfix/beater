//! Beater semantic conventions — the SINGLE source of truth for span-kind and
//! attribute keys in the Rust SDK.
//!
//! These strings mirror the server normalizer in `crates/beater-otlp` and the
//! canonical kinds in `crates/beater-schema`, plus the Python (`sdks/python`)
//! and TypeScript (`sdks/typescript`) ergonomic SDKs. They are part of the
//! cross-language ingest contract; keep them in lockstep with the server.

/// OpenInference `openinference.span.kind` values accepted by the normalizer.
pub mod span_kind {
    pub const AGENT_RUN: &str = "agent.run";
    pub const AGENT_TURN: &str = "agent.turn";
    pub const AGENT_PLAN: &str = "agent.plan";
    pub const AGENT_STEP: &str = "agent.step";
    pub const LLM_CALL: &str = "llm.call";
    pub const TOOL_CALL: &str = "tool.call";
    pub const MCP_REQUEST: &str = "mcp.request";
    pub const RETRIEVAL_QUERY: &str = "retrieval.query";
    pub const MEMORY_READ: &str = "memory.read";
    pub const MEMORY_WRITE: &str = "memory.write";
    pub const GUARDRAIL_CHECK: &str = "guardrail.check";
}

/// Every accepted span kind, for validation/iteration.
pub const SPAN_KINDS: [&str; 11] = [
    span_kind::AGENT_RUN,
    span_kind::AGENT_TURN,
    span_kind::AGENT_PLAN,
    span_kind::AGENT_STEP,
    span_kind::LLM_CALL,
    span_kind::TOOL_CALL,
    span_kind::MCP_REQUEST,
    span_kind::RETRIEVAL_QUERY,
    span_kind::MEMORY_READ,
    span_kind::MEMORY_WRITE,
    span_kind::GUARDRAIL_CHECK,
];

/// Canonical span attribute keys.
pub mod attr {
    pub const SPAN_KIND: &str = "openinference.span.kind";
    pub const SEQ: &str = "beater.seq";
    pub const RELEASE_ID: &str = "agent.release_id";

    pub const INPUT_VALUE: &str = "input.value";
    pub const OUTPUT_VALUE: &str = "output.value";

    pub const LLM_PROVIDER: &str = "llm.provider";
    pub const LLM_MODEL_NAME: &str = "llm.model_name";
    pub const LLM_TOKEN_PROMPT: &str = "llm.token_count.prompt";
    pub const LLM_TOKEN_COMPLETION: &str = "llm.token_count.completion";
    pub const LLM_TOKEN_REASONING: &str = "llm.token_count.reasoning";
    pub const LLM_TOKEN_CACHE_READ: &str = "llm.token_count.cache_read";
    pub const LLM_COST_MICROS: &str = "llm.cost.amount_micros";
    pub const LLM_COST_CURRENCY: &str = "llm.cost.currency";
}

/// OTLP ingest headers used to scope traces when exporting over gRPC.
pub const HEADER_TENANT: &str = "x-beater-tenant-id";
pub const HEADER_PROJECT: &str = "x-beater-project-id";
pub const HEADER_ENVIRONMENT: &str = "x-beater-environment-id";
