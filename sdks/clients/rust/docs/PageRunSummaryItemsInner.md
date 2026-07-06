# PageRunSummaryItemsInner

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**duration_ms** | Option<**i64**> |  | [optional]
**ended_at** | Option<**String**> |  | [optional]
**first_span_name** | **String** |  | 
**models** | [**Vec<models::ModelRef>**](ModelRef.md) |  | 
**project_id** | **String** |  | 
**release_ids** | **Vec<String>** |  | 
**span_count** | **i32** |  | 
**started_at** | **String** |  | 
**status** | [**models::SpanStatus**](SpanStatus.md) |  | 
**tenant_id** | **String** |  | 
**total_cost** | Option<[**models::Money**](Money.md)> | Legacy raw sum of kept span costs. For tail-sampled populations, prefer `total_cost_estimate_micros`, which carries the weighting label. | [optional]
**total_cost_estimate_micros** | Option<[**models::RollupEstimate**](RollupEstimate.md)> | Population cost estimate over costed spans, in USD micros, with the weighting label required to distinguish inverse-probability weighted roll-ups from biased unweighted fallbacks. | [optional]
**trace_id** | **String** |  | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


