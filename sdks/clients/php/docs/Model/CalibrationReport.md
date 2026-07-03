# # CalibrationReport

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**brier_score** | **float** |  |
**calibration_report_id** | **string** |  |
**cohen_kappa** | **float** |  |
**cohen_kappa_ci_high** | **float** |  | [optional]
**cohen_kappa_ci_low** | **float** | Percentile-bootstrap 95% confidence interval for &#x60;cohen_kappa&#x60; (multinomial resampling of the confusion table, deterministic seed). Kappa over small calibration samples is high-variance; a bare point estimate invites over-reading. Absent on pre-uncertainty reports. | [optional]
**confusion** | [**\Beater\Client\Model\CalibrationConfusion**](CalibrationConfusion.md) |  |
**created_at** | **\DateTime** |  |
**dataset_id** | **string** |  |
**dataset_version_id** | **string** |  |
**eval_report_id** | **string** |  |
**evaluator_version_id** | **string** |  |
**expected_agreement** | **float** |  |
**expected_calibration_error** | **float** |  |
**items** | [**\Beater\Client\Model\CalibrationItem[]**](CalibrationItem.md) |  |
**observed_agreement** | **float** |  |
**observed_agreement_ci_high** | **float** |  | [optional]
**observed_agreement_ci_low** | **float** | Wilson 95% confidence interval for &#x60;observed_agreement&#x60; — the honest width of an agreement estimate over a (typically small) human-labelled sample. Absent on reports persisted before uncertainty was reported. | [optional]
**policy** | [**\Beater\Client\Model\CalibrationPolicy**](CalibrationPolicy.md) |  |
**project_id** | **string** |  |
**reliability_bins** | [**\Beater\Client\Model\ReliabilityBin[]**](ReliabilityBin.md) |  |
**sample_count** | **int** |  |
**tenant_id** | **string** |  |

[[Back to Model list]](../../README.md#models) [[Back to API list]](../../README.md#endpoints) [[Back to README]](../../README.md)
