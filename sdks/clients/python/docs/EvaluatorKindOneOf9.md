# EvaluatorKindOneOf9

Browser recovery: passes when the run either hit no errors or recovered to a successful final step (catches death spirals after a failed action).

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**type** | **str** |  | 

## Example

```python
from beater_client.models.evaluator_kind_one_of9 import EvaluatorKindOneOf9

# TODO update the JSON string below
json = "{}"
# create an instance of EvaluatorKindOneOf9 from a JSON string
evaluator_kind_one_of9_instance = EvaluatorKindOneOf9.from_json(json)
# print the JSON string representation of the object
print(EvaluatorKindOneOf9.to_json())

# convert the object into a dict
evaluator_kind_one_of9_dict = evaluator_kind_one_of9_instance.to_dict()
# create an instance of EvaluatorKindOneOf9 from a dict
evaluator_kind_one_of9_from_dict = EvaluatorKindOneOf9.from_dict(evaluator_kind_one_of9_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


