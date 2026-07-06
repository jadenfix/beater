# page_run_summary_items_inner_t

## Properties
Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**duration_ms** | **long** |  | [optional]
**ended_at** | **char \*** |  | [optional]
**first_span_name** | **char \*** |  |
**models** | [**list_t**](model_ref.md) \* |  |
**project_id** | **char \*** |  |
**release_ids** | **list_t \*** |  |
**span_count** | **int** |  |
**started_at** | **char \*** |  |
**status** | **span_status_t \*** |  |
**tenant_id** | **char \*** |  |
**total_cost** | [**money_t**](money.md) \* | Legacy raw sum of kept span costs. For tail-sampled populations, prefer &#x60;total_cost_estimate_micros&#x60;, which carries the weighting label. | [optional]
**total_cost_estimate_micros** | [**rollup_estimate_t**](rollup_estimate.md) \* | Population cost estimate over costed spans, in USD micros, with the weighting label required to distinguish inverse-probability weighted roll-ups from biased unweighted fallbacks. | [optional]
**trace_id** | **char \*** |  |

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)
