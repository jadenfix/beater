# # NativeIngestRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**attributes** | **array<string,mixed>** |  |
**auth_context** | [**\Beater\Client\Model\AuthContext**](AuthContext.md) |  | [optional]
**cost** | [**\Beater\Client\Model\Money**](Money.md) |  | [optional]
**end_time** | **\DateTime** |  | [optional]
**idempotency_key** | **string** |  | [optional]
**input** | **mixed** |  | [optional]
**kind** | **string** | Canonical agent span kind such as agent.run or llm.call |
**model** | [**\Beater\Client\Model\ModelRef**](ModelRef.md) |  | [optional]
**name** | **string** |  |
**output** | **mixed** |  | [optional]
**parent_span_id** | **string** |  | [optional]
**redaction_class** | [**\Beater\Client\Model\RedactionClass**](RedactionClass.md) |  |
**scope** | [**\Beater\Client\Model\TenantScope**](TenantScope.md) |  |
**seq** | **int** |  |
**span_id** | **string** |  |
**start_time** | **\DateTime** |  | [optional]
**status** | [**\Beater\Client\Model\SpanStatus**](SpanStatus.md) |  |
**tokens** | [**\Beater\Client\Model\TokenCounts**](TokenCounts.md) |  | [optional]
**trace_id** | **string** |  |

[[Back to Model list]](../../README.md#models) [[Back to API list]](../../README.md#endpoints) [[Back to README]](../../README.md)
