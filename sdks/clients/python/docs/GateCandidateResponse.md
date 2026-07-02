# GateCandidateResponse

Verdict for `gateOptimizationCandidate`: the held-out Test comparison, the generalization-gap assessment, and the combined acceptance decision.

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**accepted** | **bool** | &#x60;true&#x60; iff the held-out Test gate &#x60;Pass&#x60;ed AND no significant generalization gap was flagged. This is the only path to acceptance. | 
**gate** | [**GateComparisonResponse**](GateComparisonResponse.md) | The held-out **Test**-split comparison (paired test + CI vs. the regression bound). | 
**overfit** | [**OverfitResponse**](OverfitResponse.md) | The generalization-gap assessment (optimization-split lift vs. held-out lift). | 

## Example

```python
from beater_client.models.gate_candidate_response import GateCandidateResponse

# TODO update the JSON string below
json = "{}"
# create an instance of GateCandidateResponse from a JSON string
gate_candidate_response_instance = GateCandidateResponse.from_json(json)
# print the JSON string representation of the object
print(GateCandidateResponse.to_json())

# convert the object into a dict
gate_candidate_response_dict = gate_candidate_response_instance.to_dict()
# create an instance of GateCandidateResponse from a dict
gate_candidate_response_from_dict = GateCandidateResponse.from_dict(gate_candidate_response_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


