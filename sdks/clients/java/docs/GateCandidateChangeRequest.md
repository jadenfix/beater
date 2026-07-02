

# GateCandidateChangeRequest

The candidate change being gated. `kind` and `proposed_by` are the RSI optimizer's snake_case enum tags (e.g. `system_prompt`, `llm_rewrite`).

## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**description** | **String** | Human-readable description of the proposed change. |  |
|**kind** | **String** | The policy lever this change touches (e.g. &#x60;system_prompt&#x60;, &#x60;model_params&#x60;). |  |
|**proposedBy** | **String** | Which optimizer strategy emitted the candidate (e.g. &#x60;llm_rewrite&#x60;). |  |
|**rationale** | **String** | Why the proposer believes this change helps (carried for audit). |  |
|**target** | **String** | The file / symbol / prompt the change targets. |  |



