

# RunSummary


## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**durationMs** | **Long** |  |  [optional] |
|**endedAt** | **OffsetDateTime** |  |  [optional] |
|**firstSpanName** | **String** |  |  |
|**models** | [**List&lt;ModelRef&gt;**](ModelRef.md) |  |  |
|**projectId** | **String** |  |  |
|**releaseIds** | **List&lt;String&gt;** |  |  |
|**spanCount** | **Integer** |  |  |
|**startedAt** | **OffsetDateTime** |  |  |
|**status** | **SpanStatus** |  |  |
|**tenantId** | **String** |  |  |
|**totalCost** | [**Money**](Money.md) | Legacy raw sum of kept span costs. For tail-sampled populations, prefer &#x60;total_cost_estimate_micros&#x60;, which carries the weighting label. |  [optional] |
|**totalCostEstimateMicros** | [**RollupEstimate**](RollupEstimate.md) | Population cost estimate over costed spans, in USD micros, with the weighting label required to distinguish inverse-probability weighted roll-ups from biased unweighted fallbacks. |  [optional] |
|**traceId** | **String** |  |  |



