

# GateCandidateChangeRequest

The candidate change being gated.

## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**description** | **String** | Human-readable description of the proposed change. |  |
|**kind** | **ChangeKind** | The policy lever this change touches (e.g. &#x60;system_prompt&#x60;, &#x60;model_params&#x60;). |  |
|**proposedBy** | **OptimizerStrategy** | Which optimizer strategy emitted the candidate (e.g. &#x60;llm_rewrite&#x60;). |  |
|**rationale** | **String** | Why the proposer believes this change helps (carried for audit). |  |
|**target** | **String** | The file / symbol / prompt the change targets. |  |



