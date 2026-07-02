

# GateCaseScoreRequest

One case's paired baseline-vs-candidate score, tagged with its split.

## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**baselineScore** | **Double** | The baseline policy&#39;s score on this case, in &#x60;[0, 1]&#x60; (higher is better). |  |
|**candidateScore** | **Double** | The candidate policy&#39;s score on the *same* case (paired with baseline). |  |
|**split** | **String** | The split this case belongs to: &#x60;train&#x60;, &#x60;val&#x60;, or &#x60;test&#x60;. |  |



