# gate_comparison_response_t

## Properties
Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**baseline_mean** | **double** | Mean baseline score on the Test split. |
**candidate_mean** | **double** | Mean candidate score on the Test split. |
**ci_high** | **double** | Upper bound of the delta confidence interval. |
**ci_low** | **double** | Lower bound of the delta confidence interval. |
**decision** | **gate_decision_t \*** | Gate decision: &#x60;pass&#x60;, &#x60;fail_regression&#x60;, or &#x60;inconclusive&#x60;. |
**delta** | **double** | &#x60;candidate_mean − baseline_mean&#x60; on the Test split. |
**p_value** | **double** | Two-sided p-value of the paired test. |
**sample_size** | **int** | Number of paired Test cases compared. |

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)
