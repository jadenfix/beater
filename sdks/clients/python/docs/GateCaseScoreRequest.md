# GateCaseScoreRequest

One case's paired baseline-vs-candidate score, tagged with its split.

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**baseline_score** | **float** | The baseline policy&#39;s score on this case, in &#x60;[0, 1]&#x60; (higher is better). |
**candidate_score** | **float** | The candidate policy&#39;s score on the *same* case (paired with baseline). |
**split** | [**Split**](Split.md) | The split this case belongs to: &#x60;train&#x60;, &#x60;val&#x60;, or &#x60;test&#x60;. |

## Example

```python
from beater_client.models.gate_case_score_request import GateCaseScoreRequest

# TODO update the JSON string below
json = "{}"
# create an instance of GateCaseScoreRequest from a JSON string
gate_case_score_request_instance = GateCaseScoreRequest.from_json(json)
# print the JSON string representation of the object
print(GateCaseScoreRequest.to_json())

# convert the object into a dict
gate_case_score_request_dict = gate_case_score_request_instance.to_dict()
# create an instance of GateCaseScoreRequest from a dict
gate_case_score_request_from_dict = GateCaseScoreRequest.from_dict(gate_case_score_request_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)
