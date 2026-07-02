# overfit_response_t

## Properties
Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**gap** | **double** | &#x60;optimize_lift − holdout_lift&#x60;. | 
**gap_ci_high** | **double** | Upper bound of the bootstrap CI for &#x60;gap&#x60;. | 
**gap_ci_low** | **double** | Lower bound of the bootstrap CI for &#x60;gap&#x60;. | 
**holdout_lift** | **double** | Mean paired lift on the held-out split. | 
**optimize_lift** | **double** | Mean paired lift &#x60;(candidate − baseline)&#x60; on the optimization split. | 
**overfit** | **int** | &#x60;true&#x60; when the gap&#39;s CI lower bound exceeds tolerance — the candidate&#39;s optimization-set advantage is significantly not reproduced on held-out data. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


