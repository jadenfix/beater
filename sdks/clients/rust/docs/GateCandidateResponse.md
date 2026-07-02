# GateCandidateResponse

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**accepted** | **bool** | `true` iff the held-out Test gate `Pass`ed AND no significant generalization gap was flagged. This is the only path to acceptance. | 
**gate** | [**models::GateComparisonResponse**](GateComparisonResponse.md) | The held-out **Test**-split comparison (paired test + CI vs. the regression bound). | 
**overfit** | [**models::OverfitResponse**](OverfitResponse.md) | The generalization-gap assessment (optimization-split lift vs. held-out lift). | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


