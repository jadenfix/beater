# # Scenario

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**created_at** | **\DateTime** | When the scenario was created. |
**exemplar_trace_id** | **string** |  |
**expected_outcome** | **string** | Expected outcome for replay assertions, if known. | [optional]
**failure_mode** | [**\Beater\Client\Model\FailureMode**](FailureMode.md) | The dominant failure mode this scenario reproduces. |
**perturbation_knobs** | [**\Beater\Client\Model\PerturbationKnobs**](PerturbationKnobs.md) | Suggested perturbation knobs for replay. |
**recurrence_count** | **int** | How many traces exhibited this scenario. |
**redaction_class** | [**\Beater\Client\Model\RedactionClass**](RedactionClass.md) | Redaction classification of the scenario payload. |
**scenario_id** | **string** | Stable, deterministic identifier for the scenario. |
**scope** | [**\Beater\Client\Model\TenantScope**](TenantScope.md) | Tenant/project/environment scope this scenario belongs to. |
**source_trace_ids** | **string[]** | Trace ids the scenario was mined from, sorted ascending. |
**title** | **string** | Human-readable title. |

[[Back to Model list]](../../README.md#models) [[Back to API list]](../../README.md#endpoints) [[Back to README]](../../README.md)
