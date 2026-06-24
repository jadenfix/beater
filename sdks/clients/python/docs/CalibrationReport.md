# CalibrationReport


## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**calibration_report_id** | **str** |  | 
**cohen_kappa** | **float** |  | 
**confusion** | [**CalibrationConfusion**](CalibrationConfusion.md) |  | 
**created_at** | **datetime** |  | 
**dataset_id** | **str** |  | 
**dataset_version_id** | **str** |  | 
**eval_report_id** | **str** |  | 
**evaluator_version_id** | **str** |  | 
**expected_agreement** | **float** |  | 
**items** | [**List[CalibrationItem]**](CalibrationItem.md) |  | 
**observed_agreement** | **float** |  | 
**policy** | [**CalibrationPolicy**](CalibrationPolicy.md) |  | 
**project_id** | **str** |  | 
**sample_count** | **int** |  | 
**tenant_id** | **str** |  | 

## Example

```python
from beater_client.models.calibration_report import CalibrationReport

# TODO update the JSON string below
json = "{}"
# create an instance of CalibrationReport from a JSON string
calibration_report_instance = CalibrationReport.from_json(json)
# print the JSON string representation of the object
print(CalibrationReport.to_json())

# convert the object into a dict
calibration_report_dict = calibration_report_instance.to_dict()
# create an instance of CalibrationReport from a dict
calibration_report_from_dict = CalibrationReport.from_dict(calibration_report_dict)
```
[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


