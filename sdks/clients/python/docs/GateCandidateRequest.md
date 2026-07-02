# GateCandidateRequest

Request to gate a single optimization candidate (`gateOptimizationCandidate`).  The caller supplies the candidate it proposed and the per-case baseline-vs-candidate scores it observed, each tagged with its split. The server runs the held-out **Test** gate plus the anti-overfitting guardrail and returns the accept/reject verdict — the proposer never decides acceptance.

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**candidate** | [**GateCandidateChangeRequest**](GateCandidateChangeRequest.md) | The proposed change under evaluation (provenance for the audit trail). | 
**gate_policy** | [**GatePolicy**](GatePolicy.md) | Held-out Test gate policy. Defaults to the standard &#x60;GatePolicy&#x60;. | [optional] 
**overfit_confidence** | **float** | Bootstrap confidence for the generalization-gap CI (default &#x60;0.95&#x60;). | [optional] 
**overfit_resamples** | **int** | Bootstrap resamples for the generalization-gap CI (default &#x60;2000&#x60;). | [optional] 
**overfit_seed** | **int** | Seed for the deterministic generalization-gap bootstrap (default &#x60;1&#x60;). | [optional] 
**overfit_tolerance** | **float** | Largest benign generalization gap (default &#x60;0.0&#x60;). | [optional] 
**scores** | [**List[GateCaseScoreRequest]**](GateCaseScoreRequest.md) | Per-case paired scores. Must include at least one &#x60;test&#x60; case and at least one &#x60;train&#x60;/&#x60;val&#x60; case so both the gate and the gap check are defined. | 

## Example

```python
from beater_client.models.gate_candidate_request import GateCandidateRequest

# TODO update the JSON string below
json = "{}"
# create an instance of GateCandidateRequest from a JSON string
gate_candidate_request_instance = GateCandidateRequest.from_json(json)
# print the JSON string representation of the object
print(GateCandidateRequest.to_json())

# convert the object into a dict
gate_candidate_request_dict = gate_candidate_request_instance.to_dict()
# create an instance of GateCandidateRequest from a dict
gate_candidate_request_from_dict = GateCandidateRequest.from_dict(gate_candidate_request_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


