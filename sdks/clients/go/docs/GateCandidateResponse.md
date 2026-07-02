# GateCandidateResponse

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Accepted** | **bool** | &#x60;true&#x60; iff the held-out Test gate &#x60;Pass&#x60;ed AND no significant generalization gap was flagged. This is the only path to acceptance. | 
**Gate** | [**GateComparisonResponse**](GateComparisonResponse.md) | The held-out **Test**-split comparison (paired test + CI vs. the regression bound). | 
**Overfit** | [**OverfitResponse**](OverfitResponse.md) | The generalization-gap assessment (optimization-split lift vs. held-out lift). | 

## Methods

### NewGateCandidateResponse

`func NewGateCandidateResponse(accepted bool, gate GateComparisonResponse, overfit OverfitResponse, ) *GateCandidateResponse`

NewGateCandidateResponse instantiates a new GateCandidateResponse object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewGateCandidateResponseWithDefaults

`func NewGateCandidateResponseWithDefaults() *GateCandidateResponse`

NewGateCandidateResponseWithDefaults instantiates a new GateCandidateResponse object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetAccepted

`func (o *GateCandidateResponse) GetAccepted() bool`

GetAccepted returns the Accepted field if non-nil, zero value otherwise.

### GetAcceptedOk

`func (o *GateCandidateResponse) GetAcceptedOk() (*bool, bool)`

GetAcceptedOk returns a tuple with the Accepted field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetAccepted

`func (o *GateCandidateResponse) SetAccepted(v bool)`

SetAccepted sets Accepted field to given value.


### GetGate

`func (o *GateCandidateResponse) GetGate() GateComparisonResponse`

GetGate returns the Gate field if non-nil, zero value otherwise.

### GetGateOk

`func (o *GateCandidateResponse) GetGateOk() (*GateComparisonResponse, bool)`

GetGateOk returns a tuple with the Gate field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGate

`func (o *GateCandidateResponse) SetGate(v GateComparisonResponse)`

SetGate sets Gate field to given value.


### GetOverfit

`func (o *GateCandidateResponse) GetOverfit() OverfitResponse`

GetOverfit returns the Overfit field if non-nil, zero value otherwise.

### GetOverfitOk

`func (o *GateCandidateResponse) GetOverfitOk() (*OverfitResponse, bool)`

GetOverfitOk returns a tuple with the Overfit field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOverfit

`func (o *GateCandidateResponse) SetOverfit(v OverfitResponse)`

SetOverfit sets Overfit field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


