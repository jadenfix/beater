# RollupEstimate

A population-mean roll-up paired with the honesty label saying whether it is inverse-probability weighted or a biased unweighted average (§1 #9). The label travels with the value so a caller can never silently render a tail-sampled average as if it were unbiased.

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**value** | **float** |  | 
**weighting** | [**RollupWeighting**](RollupWeighting.md) |  | 

## Example

```python
from beater_client.models.rollup_estimate import RollupEstimate

# TODO update the JSON string below
json = "{}"
# create an instance of RollupEstimate from a JSON string
rollup_estimate_instance = RollupEstimate.from_json(json)
# print the JSON string representation of the object
print(RollupEstimate.to_json())

# convert the object into a dict
rollup_estimate_dict = rollup_estimate_instance.to_dict()
# create an instance of RollupEstimate from a dict
rollup_estimate_from_dict = RollupEstimate.from_dict(rollup_estimate_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


