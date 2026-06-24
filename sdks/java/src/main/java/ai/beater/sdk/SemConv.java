package ai.beater.sdk;

import java.util.Set;

/**
 * Beater semantic conventions: the single source of truth for span-kind and
 * attribute keys in the Java SDK.
 *
 * <p>These strings mirror the Rust normalizer in {@code crates/beater-otlp} and
 * the canonical kinds in {@code crates/beater-schema}, and stay in lockstep with
 * the Python and TypeScript SDKs. They are part of the cross-language ingest
 * contract; keep them aligned with the server.
 */
public final class SemConv {

    private SemConv() {}

    // --- OpenInference span kinds (openinference.span.kind values) ---
    public static final String AGENT_RUN = "agent.run";
    public static final String AGENT_TURN = "agent.turn";
    public static final String AGENT_PLAN = "agent.plan";
    public static final String AGENT_STEP = "agent.step";
    public static final String LLM_CALL = "llm.call";
    public static final String TOOL_CALL = "tool.call";
    public static final String MCP_REQUEST = "mcp.request";
    public static final String RETRIEVAL_QUERY = "retrieval.query";
    public static final String MEMORY_READ = "memory.read";
    public static final String MEMORY_WRITE = "memory.write";
    public static final String GUARDRAIL_CHECK = "guardrail.check";

    /** Every accepted span kind, for validation. */
    public static final Set<String> SPAN_KINDS = Set.of(
            AGENT_RUN,
            AGENT_TURN,
            AGENT_PLAN,
            AGENT_STEP,
            LLM_CALL,
            TOOL_CALL,
            MCP_REQUEST,
            RETRIEVAL_QUERY,
            MEMORY_READ,
            MEMORY_WRITE,
            GUARDRAIL_CHECK);

    // --- Canonical span attribute keys ---
    public static final String SPAN_KIND = "openinference.span.kind";
    public static final String SEQ = "beater.seq";
    public static final String RELEASE_ID = "agent.release_id";

    public static final String INPUT_VALUE = "input.value";
    public static final String OUTPUT_VALUE = "output.value";

    public static final String LLM_PROVIDER = "llm.provider";
    public static final String LLM_MODEL_NAME = "llm.model_name";
    public static final String LLM_TOKEN_PROMPT = "llm.token_count.prompt";
    public static final String LLM_TOKEN_COMPLETION = "llm.token_count.completion";
    public static final String LLM_TOKEN_REASONING = "llm.token_count.reasoning";
    public static final String LLM_TOKEN_CACHE_READ = "llm.token_count.cache_read";
    public static final String LLM_COST_MICROS = "llm.cost.amount_micros";
    public static final String LLM_COST_CURRENCY = "llm.cost.currency";

    // --- OTLP ingest headers (used to scope traces over gRPC) ---
    public static final String HEADER_TENANT = "x-beater-tenant-id";
    public static final String HEADER_PROJECT = "x-beater-project-id";
    public static final String HEADER_ENVIRONMENT = "x-beater-environment-id";
}
