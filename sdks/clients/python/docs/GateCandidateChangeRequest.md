# GateCandidateChangeRequest

The candidate change being gated.

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**description** | **str** | Human-readable description of the proposed change. |
**kind** | [**ChangeKind**](ChangeKind.md) | The policy lever this change touches (e.g. &#x60;system_prompt&#x60;, &#x60;model_params&#x60;). |
**proposed_by** | [**OptimizerStrategy**](OptimizerStrategy.md) | Which optimizer strategy emitted the candidate (e.g. &#x60;llm_rewrite&#x60;). |
**rationale** | **str** | Why the proposer believes this change helps (carried for audit). |
**target** | **str** | The file / symbol / prompt the change targets. |

## Example

```python
from beater_client.models.gate_candidate_change_request import GateCandidateChangeRequest

# TODO update the JSON string below
json = "{}"
# create an instance of GateCandidateChangeRequest from a JSON string
gate_candidate_change_request_instance = GateCandidateChangeRequest.from_json(json)
# print the JSON string representation of the object
print(GateCandidateChangeRequest.to_json())

# convert the object into a dict
gate_candidate_change_request_dict = gate_candidate_change_request_instance.to_dict()
# create an instance of GateCandidateChangeRequest from a dict
gate_candidate_change_request_from_dict = GateCandidateChangeRequest.from_dict(gate_candidate_change_request_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)
