# OverfitResponse

The anti-overfitting (generalization-gap) assessment.

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**gap** | **float** | &#x60;optimize_lift − holdout_lift&#x60;. | 
**gap_ci_high** | **float** | Upper bound of the bootstrap CI for &#x60;gap&#x60;. | 
**gap_ci_low** | **float** | Lower bound of the bootstrap CI for &#x60;gap&#x60;. | 
**holdout_lift** | **float** | Mean paired lift on the held-out split. | 
**optimize_lift** | **float** | Mean paired lift &#x60;(candidate − baseline)&#x60; on the optimization split. | 
**overfit** | **bool** | &#x60;true&#x60; when the gap&#39;s CI lower bound exceeds tolerance — the candidate&#39;s optimization-set advantage is significantly not reproduced on held-out data. | 

## Example

```python
from beater_client.models.overfit_response import OverfitResponse

# TODO update the JSON string below
json = "{}"
# create an instance of OverfitResponse from a JSON string
overfit_response_instance = OverfitResponse.from_json(json)
# print the JSON string representation of the object
print(OverfitResponse.to_json())

# convert the object into a dict
overfit_response_dict = overfit_response_instance.to_dict()
# create an instance of OverfitResponse from a dict
overfit_response_from_dict = OverfitResponse.from_dict(overfit_response_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


