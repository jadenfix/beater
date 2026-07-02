# GateCaseScoreRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**BaselineScore** | **float64** | The baseline policy&#39;s score on this case, in &#x60;[0, 1]&#x60; (higher is better). | 
**CandidateScore** | **float64** | The candidate policy&#39;s score on the *same* case (paired with baseline). | 
**Split** | **string** | The split this case belongs to: &#x60;train&#x60;, &#x60;val&#x60;, or &#x60;test&#x60;. | 

## Methods

### NewGateCaseScoreRequest

`func NewGateCaseScoreRequest(baselineScore float64, candidateScore float64, split string, ) *GateCaseScoreRequest`

NewGateCaseScoreRequest instantiates a new GateCaseScoreRequest object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewGateCaseScoreRequestWithDefaults

`func NewGateCaseScoreRequestWithDefaults() *GateCaseScoreRequest`

NewGateCaseScoreRequestWithDefaults instantiates a new GateCaseScoreRequest object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetBaselineScore

`func (o *GateCaseScoreRequest) GetBaselineScore() float64`

GetBaselineScore returns the BaselineScore field if non-nil, zero value otherwise.

### GetBaselineScoreOk

`func (o *GateCaseScoreRequest) GetBaselineScoreOk() (*float64, bool)`

GetBaselineScoreOk returns a tuple with the BaselineScore field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBaselineScore

`func (o *GateCaseScoreRequest) SetBaselineScore(v float64)`

SetBaselineScore sets BaselineScore field to given value.


### GetCandidateScore

`func (o *GateCaseScoreRequest) GetCandidateScore() float64`

GetCandidateScore returns the CandidateScore field if non-nil, zero value otherwise.

### GetCandidateScoreOk

`func (o *GateCaseScoreRequest) GetCandidateScoreOk() (*float64, bool)`

GetCandidateScoreOk returns a tuple with the CandidateScore field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCandidateScore

`func (o *GateCaseScoreRequest) SetCandidateScore(v float64)`

SetCandidateScore sets CandidateScore field to given value.


### GetSplit

`func (o *GateCaseScoreRequest) GetSplit() string`

GetSplit returns the Split field if non-nil, zero value otherwise.

### GetSplitOk

`func (o *GateCaseScoreRequest) GetSplitOk() (*string, bool)`

GetSplitOk returns a tuple with the Split field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSplit

`func (o *GateCaseScoreRequest) SetSplit(v string)`

SetSplit sets Split field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


