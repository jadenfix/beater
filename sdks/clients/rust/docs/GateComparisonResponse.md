# GateComparisonResponse

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**baseline_mean** | **f64** | Mean baseline score on the Test split. | 
**candidate_mean** | **f64** | Mean candidate score on the Test split. | 
**ci_high** | **f64** | Upper bound of the delta confidence interval. | 
**ci_low** | **f64** | Lower bound of the delta confidence interval. | 
**decision** | **String** | Gate decision: `pass`, `fail_regression`, or `inconclusive`. | 
**delta** | **f64** | `candidate_mean − baseline_mean` on the Test split. | 
**p_value** | **f64** | Two-sided p-value of the paired test. | 
**sample_size** | **i32** | Number of paired Test cases compared. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


