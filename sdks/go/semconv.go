// Package beater provides ergonomic OpenTelemetry tracing helpers that emit
// spans Beater understands, mirroring the Python and TypeScript SDKs.
package beater

// Span kinds. These are the openinference.span.kind values accepted by the
// beaterd OTLP normalizer. They mirror sdks/python/beater/semconv.py and the
// Rust normalizer in crates/beater-otlp -- keep them in lockstep with the
// server. This file is the single source of truth for the Go SDK.
const (
	KindAgentRun       = "agent.run"
	KindAgentTurn      = "agent.turn"
	KindAgentPlan      = "agent.plan"
	KindAgentStep      = "agent.step"
	KindLLMCall        = "llm.call"
	KindToolCall       = "tool.call"
	KindMCPRequest     = "mcp.request"
	KindRetrievalQuery = "retrieval.query"
	KindMemoryRead     = "memory.read"
	KindMemoryWrite    = "memory.write"
	KindGuardrailCheck = "guardrail.check"
)

// SpanKinds is every accepted span kind, for validation.
var SpanKinds = map[string]struct{}{
	KindAgentRun:       {},
	KindAgentTurn:      {},
	KindAgentPlan:      {},
	KindAgentStep:      {},
	KindLLMCall:        {},
	KindToolCall:       {},
	KindMCPRequest:     {},
	KindRetrievalQuery: {},
	KindMemoryRead:     {},
	KindMemoryWrite:    {},
	KindGuardrailCheck: {},
}

// Canonical span attribute keys.
const (
	AttrSpanKind  = "openinference.span.kind"
	AttrSeq       = "beater.seq"
	AttrReleaseID = "agent.release_id"

	AttrInputValue  = "input.value"
	AttrOutputValue = "output.value"

	AttrLLMProvider        = "llm.provider"
	AttrLLMModelName       = "llm.model_name"
	AttrLLMTokenPrompt     = "llm.token_count.prompt"
	AttrLLMTokenCompletion = "llm.token_count.completion"
	AttrLLMTokenReasoning  = "llm.token_count.reasoning"
	AttrLLMTokenCacheRead  = "llm.token_count.cache_read"
	AttrLLMCostMicros      = "llm.cost.amount_micros"
	AttrLLMCostCurrency    = "llm.cost.currency"
)

// OTLP scope headers used when exporting over gRPC (HTTP carries these in the URL path).
const (
	HeaderTenant      = "x-beater-tenant-id"
	HeaderProject     = "x-beater-project-id"
	HeaderEnvironment = "x-beater-environment-id"
)
