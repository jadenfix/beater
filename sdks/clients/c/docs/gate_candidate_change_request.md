# gate_candidate_change_request_t

## Properties
Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**description** | **char \*** | Human-readable description of the proposed change. | 
**kind** | **char \*** | The policy lever this change touches (e.g. &#x60;system_prompt&#x60;, &#x60;model_params&#x60;). | 
**proposed_by** | **char \*** | Which optimizer strategy emitted the candidate (e.g. &#x60;llm_rewrite&#x60;). | 
**rationale** | **char \*** | Why the proposer believes this change helps (carried for audit). | 
**target** | **char \*** | The file / symbol / prompt the change targets. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


