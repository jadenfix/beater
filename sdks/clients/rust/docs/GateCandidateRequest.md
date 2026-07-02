# GateCandidateRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**candidate** | [**models::GateCandidateChangeRequest**](GateCandidateChangeRequest.md) | The proposed change under evaluation (provenance for the audit trail). | 
**gate_policy** | Option<[**models::GatePolicy**](GatePolicy.md)> | Held-out Test gate policy. Defaults to the standard `GatePolicy`. | [optional]
**overfit_confidence** | Option<**f64**> | Bootstrap confidence for the generalization-gap CI (default `0.95`). | [optional]
**overfit_resamples** | Option<**i32**> | Bootstrap resamples for the generalization-gap CI (default `2000`). | [optional]
**overfit_seed** | Option<**i64**> | Seed for the deterministic generalization-gap bootstrap (default `1`). | [optional]
**overfit_tolerance** | Option<**f64**> | Largest benign generalization gap (default `0.0`). | [optional]
**scores** | [**Vec<models::GateCaseScoreRequest>**](GateCaseScoreRequest.md) | Per-case paired scores. Must include at least one `test` case and at least one `train`/`val` case so both the gate and the gap check are defined. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


