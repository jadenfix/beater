# gate_candidate_response_t

## Properties
Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**accepted** | **int** | &#x60;true&#x60; iff the held-out Test gate &#x60;Pass&#x60;ed AND no significant generalization gap was flagged. This is the only path to acceptance. | 
**gate** | [**gate_comparison_response_t**](gate_comparison_response.md) \* | The held-out **Test**-split comparison (paired test + CI vs. the regression bound). | 
**overfit** | [**overfit_response_t**](overfit_response.md) \* | The generalization-gap assessment (optimization-split lift vs. held-out lift). | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


