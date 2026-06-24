# DatasetVersionSnapshot


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**cases** | [**List[DatasetCase]**](DatasetCase.md) |  | 
**created_at** | **datetime** |  | 
**dataset_id** | **str** |  | 
**project_id** | **str** |  | 
**tenant_id** | **str** |  | 
**version_id** | **str** |  | 

## Example

```python
from beater_client.models.dataset_version_snapshot import DatasetVersionSnapshot

# TODO update the JSON string below
json = "{}"
# create an instance of DatasetVersionSnapshot from a JSON string
dataset_version_snapshot_instance = DatasetVersionSnapshot.from_json(json)
# print the JSON string representation of the object
print(DatasetVersionSnapshot.to_json())

# convert the object into a dict
dataset_version_snapshot_dict = dataset_version_snapshot_instance.to_dict()
# create an instance of DatasetVersionSnapshot from a dict
dataset_version_snapshot_from_dict = DatasetVersionSnapshot.from_dict(dataset_version_snapshot_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


