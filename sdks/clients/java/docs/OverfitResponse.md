

# OverfitResponse

The anti-overfitting (generalization-gap) assessment.

## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**gap** | **Double** | &#x60;optimize_lift − holdout_lift&#x60;. |  |
|**gapCiHigh** | **Double** | Upper bound of the bootstrap CI for &#x60;gap&#x60;. |  |
|**gapCiLow** | **Double** | Lower bound of the bootstrap CI for &#x60;gap&#x60;. |  |
|**holdoutLift** | **Double** | Mean paired lift on the held-out split. |  |
|**optimizeLift** | **Double** | Mean paired lift &#x60;(candidate − baseline)&#x60; on the optimization split. |  |
|**overfit** | **Boolean** | &#x60;true&#x60; when the gap&#39;s CI lower bound exceeds tolerance — the candidate&#39;s optimization-set advantage is significantly not reproduced on held-out data. |  |



