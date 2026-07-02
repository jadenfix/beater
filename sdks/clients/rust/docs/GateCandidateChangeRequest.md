# GateCandidateChangeRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**description** | **String** | Human-readable description of the proposed change. | 
**kind** | **String** | The policy lever this change touches (e.g. `system_prompt`, `model_params`). | 
**proposed_by** | **String** | Which optimizer strategy emitted the candidate (e.g. `llm_rewrite`). | 
**rationale** | **String** | Why the proposer believes this change helps (carried for audit). | 
**target** | **String** | The file / symbol / prompt the change targets. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


