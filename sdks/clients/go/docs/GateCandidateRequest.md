# GateCandidateRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Candidate** | [**GateCandidateChangeRequest**](GateCandidateChangeRequest.md) | The proposed change under evaluation (provenance for the audit trail). | 
**GatePolicy** | Pointer to [**NullableGatePolicy**](GatePolicy.md) | Held-out Test gate policy. Defaults to the standard &#x60;GatePolicy&#x60;. | [optional] 
**OverfitConfidence** | Pointer to **NullableFloat64** | Bootstrap confidence for the generalization-gap CI (default &#x60;0.95&#x60;). | [optional] 
**OverfitResamples** | Pointer to **NullableInt32** | Bootstrap resamples for the generalization-gap CI (default &#x60;2000&#x60;). | [optional] 
**OverfitSeed** | Pointer to **NullableInt64** | Seed for the deterministic generalization-gap bootstrap (default &#x60;1&#x60;). | [optional] 
**OverfitTolerance** | Pointer to **NullableFloat64** | Largest benign generalization gap (default &#x60;0.0&#x60;). | [optional] 
**Scores** | [**[]GateCaseScoreRequest**](GateCaseScoreRequest.md) | Per-case paired scores. Must include at least one &#x60;test&#x60; case and at least one &#x60;train&#x60;/&#x60;val&#x60; case so both the gate and the gap check are defined. | 

## Methods

### NewGateCandidateRequest

`func NewGateCandidateRequest(candidate GateCandidateChangeRequest, scores []GateCaseScoreRequest, ) *GateCandidateRequest`

NewGateCandidateRequest instantiates a new GateCandidateRequest object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewGateCandidateRequestWithDefaults

`func NewGateCandidateRequestWithDefaults() *GateCandidateRequest`

NewGateCandidateRequestWithDefaults instantiates a new GateCandidateRequest object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetCandidate

`func (o *GateCandidateRequest) GetCandidate() GateCandidateChangeRequest`

GetCandidate returns the Candidate field if non-nil, zero value otherwise.

### GetCandidateOk

`func (o *GateCandidateRequest) GetCandidateOk() (*GateCandidateChangeRequest, bool)`

GetCandidateOk returns a tuple with the Candidate field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCandidate

`func (o *GateCandidateRequest) SetCandidate(v GateCandidateChangeRequest)`

SetCandidate sets Candidate field to given value.


### GetGatePolicy

`func (o *GateCandidateRequest) GetGatePolicy() GatePolicy`

GetGatePolicy returns the GatePolicy field if non-nil, zero value otherwise.

### GetGatePolicyOk

`func (o *GateCandidateRequest) GetGatePolicyOk() (*GatePolicy, bool)`

GetGatePolicyOk returns a tuple with the GatePolicy field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGatePolicy

`func (o *GateCandidateRequest) SetGatePolicy(v GatePolicy)`

SetGatePolicy sets GatePolicy field to given value.

### HasGatePolicy

`func (o *GateCandidateRequest) HasGatePolicy() bool`

HasGatePolicy returns a boolean if a field has been set.

### SetGatePolicyNil

`func (o *GateCandidateRequest) SetGatePolicyNil(b bool)`

 SetGatePolicyNil sets the value for GatePolicy to be an explicit nil

### UnsetGatePolicy
`func (o *GateCandidateRequest) UnsetGatePolicy()`

UnsetGatePolicy ensures that no value is present for GatePolicy, not even an explicit nil
### GetOverfitConfidence

`func (o *GateCandidateRequest) GetOverfitConfidence() float64`

GetOverfitConfidence returns the OverfitConfidence field if non-nil, zero value otherwise.

### GetOverfitConfidenceOk

`func (o *GateCandidateRequest) GetOverfitConfidenceOk() (*float64, bool)`

GetOverfitConfidenceOk returns a tuple with the OverfitConfidence field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOverfitConfidence

`func (o *GateCandidateRequest) SetOverfitConfidence(v float64)`

SetOverfitConfidence sets OverfitConfidence field to given value.

### HasOverfitConfidence

`func (o *GateCandidateRequest) HasOverfitConfidence() bool`

HasOverfitConfidence returns a boolean if a field has been set.

### SetOverfitConfidenceNil

`func (o *GateCandidateRequest) SetOverfitConfidenceNil(b bool)`

 SetOverfitConfidenceNil sets the value for OverfitConfidence to be an explicit nil

### UnsetOverfitConfidence
`func (o *GateCandidateRequest) UnsetOverfitConfidence()`

UnsetOverfitConfidence ensures that no value is present for OverfitConfidence, not even an explicit nil
### GetOverfitResamples

`func (o *GateCandidateRequest) GetOverfitResamples() int32`

GetOverfitResamples returns the OverfitResamples field if non-nil, zero value otherwise.

### GetOverfitResamplesOk

`func (o *GateCandidateRequest) GetOverfitResamplesOk() (*int32, bool)`

GetOverfitResamplesOk returns a tuple with the OverfitResamples field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOverfitResamples

`func (o *GateCandidateRequest) SetOverfitResamples(v int32)`

SetOverfitResamples sets OverfitResamples field to given value.

### HasOverfitResamples

`func (o *GateCandidateRequest) HasOverfitResamples() bool`

HasOverfitResamples returns a boolean if a field has been set.

### SetOverfitResamplesNil

`func (o *GateCandidateRequest) SetOverfitResamplesNil(b bool)`

 SetOverfitResamplesNil sets the value for OverfitResamples to be an explicit nil

### UnsetOverfitResamples
`func (o *GateCandidateRequest) UnsetOverfitResamples()`

UnsetOverfitResamples ensures that no value is present for OverfitResamples, not even an explicit nil
### GetOverfitSeed

`func (o *GateCandidateRequest) GetOverfitSeed() int64`

GetOverfitSeed returns the OverfitSeed field if non-nil, zero value otherwise.

### GetOverfitSeedOk

`func (o *GateCandidateRequest) GetOverfitSeedOk() (*int64, bool)`

GetOverfitSeedOk returns a tuple with the OverfitSeed field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOverfitSeed

`func (o *GateCandidateRequest) SetOverfitSeed(v int64)`

SetOverfitSeed sets OverfitSeed field to given value.

### HasOverfitSeed

`func (o *GateCandidateRequest) HasOverfitSeed() bool`

HasOverfitSeed returns a boolean if a field has been set.

### SetOverfitSeedNil

`func (o *GateCandidateRequest) SetOverfitSeedNil(b bool)`

 SetOverfitSeedNil sets the value for OverfitSeed to be an explicit nil

### UnsetOverfitSeed
`func (o *GateCandidateRequest) UnsetOverfitSeed()`

UnsetOverfitSeed ensures that no value is present for OverfitSeed, not even an explicit nil
### GetOverfitTolerance

`func (o *GateCandidateRequest) GetOverfitTolerance() float64`

GetOverfitTolerance returns the OverfitTolerance field if non-nil, zero value otherwise.

### GetOverfitToleranceOk

`func (o *GateCandidateRequest) GetOverfitToleranceOk() (*float64, bool)`

GetOverfitToleranceOk returns a tuple with the OverfitTolerance field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOverfitTolerance

`func (o *GateCandidateRequest) SetOverfitTolerance(v float64)`

SetOverfitTolerance sets OverfitTolerance field to given value.

### HasOverfitTolerance

`func (o *GateCandidateRequest) HasOverfitTolerance() bool`

HasOverfitTolerance returns a boolean if a field has been set.

### SetOverfitToleranceNil

`func (o *GateCandidateRequest) SetOverfitToleranceNil(b bool)`

 SetOverfitToleranceNil sets the value for OverfitTolerance to be an explicit nil

### UnsetOverfitTolerance
`func (o *GateCandidateRequest) UnsetOverfitTolerance()`

UnsetOverfitTolerance ensures that no value is present for OverfitTolerance, not even an explicit nil
### GetScores

`func (o *GateCandidateRequest) GetScores() []GateCaseScoreRequest`

GetScores returns the Scores field if non-nil, zero value otherwise.

### GetScoresOk

`func (o *GateCandidateRequest) GetScoresOk() (*[]GateCaseScoreRequest, bool)`

GetScoresOk returns a tuple with the Scores field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetScores

`func (o *GateCandidateRequest) SetScores(v []GateCaseScoreRequest)`

SetScores sets Scores field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


