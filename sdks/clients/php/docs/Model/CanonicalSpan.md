# # CanonicalSpan

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**attributes** | **array<string,mixed>** |  |
**cost** | [**\Beater\Client\Model\Money**](Money.md) |  | [optional]
**end_time** | **\DateTime** |  | [optional]
**environment_id** | **string** |  |
**input_ref** | [**\Beater\Client\Model\ArtifactRef**](ArtifactRef.md) |  | [optional]
**kind** | **string** | Canonical agent span kind such as agent.run or llm.call |
**model** | [**\Beater\Client\Model\ModelRef**](ModelRef.md) |  | [optional]
**name** | **string** |  |
**normalizer_version** | **string** |  |
**output_ref** | [**\Beater\Client\Model\ArtifactRef**](ArtifactRef.md) |  | [optional]
**parent_span_id** | **string** |  | [optional]
**project_id** | **string** |  |
**raw_ref** | [**\Beater\Client\Model\ArtifactRef**](ArtifactRef.md) |  |
**schema_version** | **int** |  |
**seq** | **int** |  |
**span_id** | **string** |  |
**start_time** | **\DateTime** |  |
**status** | [**\Beater\Client\Model\SpanStatus**](SpanStatus.md) |  |
**tenant_id** | **string** |  |
**tokens** | [**\Beater\Client\Model\TokenCounts**](TokenCounts.md) |  | [optional]
**trace_id** | **string** |  |
**unmapped_attrs** | **mixed** |  |

[[Back to Model list]](../../README.md#models) [[Back to API list]](../../README.md#endpoints) [[Back to README]](../../README.md)
