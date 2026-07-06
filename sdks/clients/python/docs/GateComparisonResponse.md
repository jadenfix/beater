# GateComparisonResponse

The held-out Test-split gate comparison.

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**baseline_mean** | **float** | Mean baseline score on the Test split. |
**candidate_mean** | **float** | Mean candidate score on the Test split. |
**ci_high** | **float** | Upper bound of the delta confidence interval. |
**ci_low** | **float** | Lower bound of the delta confidence interval. |
**decision** | [**GateDecision**](GateDecision.md) | Gate decision: &#x60;pass&#x60;, &#x60;fail_regression&#x60;, or &#x60;inconclusive&#x60;. |
**delta** | **float** | &#x60;candidate_mean − baseline_mean&#x60; on the Test split. |
**p_value** | **float** | Two-sided p-value of the paired test. |
**sample_size** | **int** | Number of paired Test cases compared. |

## Example

```python
from beater_client.models.gate_comparison_response import GateComparisonResponse

# TODO update the JSON string below
json = "{}"
# create an instance of GateComparisonResponse from a JSON string
gate_comparison_response_instance = GateComparisonResponse.from_json(json)
# print the JSON string representation of the object
print(GateComparisonResponse.to_json())

# convert the object into a dict
gate_comparison_response_dict = gate_comparison_response_instance.to_dict()
# create an instance of GateComparisonResponse from a dict
gate_comparison_response_from_dict = GateComparisonResponse.from_dict(gate_comparison_response_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)
