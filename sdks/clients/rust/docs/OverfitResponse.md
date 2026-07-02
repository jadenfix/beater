# OverfitResponse

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**gap** | **f64** | `optimize_lift − holdout_lift`. | 
**gap_ci_high** | **f64** | Upper bound of the bootstrap CI for `gap`. | 
**gap_ci_low** | **f64** | Lower bound of the bootstrap CI for `gap`. | 
**holdout_lift** | **f64** | Mean paired lift on the held-out split. | 
**optimize_lift** | **f64** | Mean paired lift `(candidate − baseline)` on the optimization split. | 
**overfit** | **bool** | `true` when the gap's CI lower bound exceeds tolerance — the candidate's optimization-set advantage is significantly not reproduced on held-out data. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


