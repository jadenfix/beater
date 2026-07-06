

# GateComparisonResponse

The held-out Test-split gate comparison.

## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**baselineMean** | **Double** | Mean baseline score on the Test split. |  |
|**candidateMean** | **Double** | Mean candidate score on the Test split. |  |
|**ciHigh** | **Double** | Upper bound of the delta confidence interval. |  |
|**ciLow** | **Double** | Lower bound of the delta confidence interval. |  |
|**decision** | **GateDecision** | Gate decision: &#x60;pass&#x60;, &#x60;fail_regression&#x60;, or &#x60;inconclusive&#x60;. |  |
|**delta** | **Double** | &#x60;candidate_mean − baseline_mean&#x60; on the Test split. |  |
|**pValue** | **Double** | Two-sided p-value of the paired test. |  |
|**sampleSize** | **Integer** | Number of paired Test cases compared. |  |



