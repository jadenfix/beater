# gate_candidate_request_t

## Properties
Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**candidate** | [**gate_candidate_change_request_t**](gate_candidate_change_request.md) \* | The proposed change under evaluation (provenance for the audit trail). | 
**gate_policy** | [**gate_policy_t**](gate_policy.md) \* | Held-out Test gate policy. Defaults to the standard &#x60;GatePolicy&#x60;. | [optional] 
**overfit_confidence** | **double** | Bootstrap confidence for the generalization-gap CI (default &#x60;0.95&#x60;). | [optional] 
**overfit_resamples** | **int** | Bootstrap resamples for the generalization-gap CI (default &#x60;2000&#x60;). | [optional] 
**overfit_seed** | **long** | Seed for the deterministic generalization-gap bootstrap (default &#x60;1&#x60;). | [optional] 
**overfit_tolerance** | **double** | Largest benign generalization gap (default &#x60;0.0&#x60;). | [optional] 
**scores** | [**list_t**](gate_case_score_request.md) \* | Per-case paired scores. Must include at least one &#x60;test&#x60; case and at least one &#x60;train&#x60;/&#x60;val&#x60; case so both the gate and the gap check are defined. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


