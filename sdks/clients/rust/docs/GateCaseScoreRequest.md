# GateCaseScoreRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**baseline_score** | **f64** | The baseline policy's score on this case, in `[0, 1]` (higher is better). | 
**candidate_score** | **f64** | The candidate policy's score on the *same* case (paired with baseline). | 
**split** | **String** | The split this case belongs to: `train`, `val`, or `test`. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


