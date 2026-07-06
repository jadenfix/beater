# GateComparisonResponse

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**BaselineMean** | **float64** | Mean baseline score on the Test split. |
**CandidateMean** | **float64** | Mean candidate score on the Test split. |
**CiHigh** | **float64** | Upper bound of the delta confidence interval. |
**CiLow** | **float64** | Lower bound of the delta confidence interval. |
**Decision** | [**GateDecision**](GateDecision.md) | Gate decision: &#x60;pass&#x60;, &#x60;fail_regression&#x60;, or &#x60;inconclusive&#x60;. |
**Delta** | **float64** | &#x60;candidate_mean − baseline_mean&#x60; on the Test split. |
**PValue** | **float64** | Two-sided p-value of the paired test. |
**SampleSize** | **int32** | Number of paired Test cases compared. |

## Methods

### NewGateComparisonResponse

`func NewGateComparisonResponse(baselineMean float64, candidateMean float64, ciHigh float64, ciLow float64, decision GateDecision, delta float64, pValue float64, sampleSize int32, ) *GateComparisonResponse`

NewGateComparisonResponse instantiates a new GateComparisonResponse object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewGateComparisonResponseWithDefaults

`func NewGateComparisonResponseWithDefaults() *GateComparisonResponse`

NewGateComparisonResponseWithDefaults instantiates a new GateComparisonResponse object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetBaselineMean

`func (o *GateComparisonResponse) GetBaselineMean() float64`

GetBaselineMean returns the BaselineMean field if non-nil, zero value otherwise.

### GetBaselineMeanOk

`func (o *GateComparisonResponse) GetBaselineMeanOk() (*float64, bool)`

GetBaselineMeanOk returns a tuple with the BaselineMean field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetBaselineMean

`func (o *GateComparisonResponse) SetBaselineMean(v float64)`

SetBaselineMean sets BaselineMean field to given value.


### GetCandidateMean

`func (o *GateComparisonResponse) GetCandidateMean() float64`

GetCandidateMean returns the CandidateMean field if non-nil, zero value otherwise.

### GetCandidateMeanOk

`func (o *GateComparisonResponse) GetCandidateMeanOk() (*float64, bool)`

GetCandidateMeanOk returns a tuple with the CandidateMean field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCandidateMean

`func (o *GateComparisonResponse) SetCandidateMean(v float64)`

SetCandidateMean sets CandidateMean field to given value.


### GetCiHigh

`func (o *GateComparisonResponse) GetCiHigh() float64`

GetCiHigh returns the CiHigh field if non-nil, zero value otherwise.

### GetCiHighOk

`func (o *GateComparisonResponse) GetCiHighOk() (*float64, bool)`

GetCiHighOk returns a tuple with the CiHigh field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCiHigh

`func (o *GateComparisonResponse) SetCiHigh(v float64)`

SetCiHigh sets CiHigh field to given value.


### GetCiLow

`func (o *GateComparisonResponse) GetCiLow() float64`

GetCiLow returns the CiLow field if non-nil, zero value otherwise.

### GetCiLowOk

`func (o *GateComparisonResponse) GetCiLowOk() (*float64, bool)`

GetCiLowOk returns a tuple with the CiLow field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCiLow

`func (o *GateComparisonResponse) SetCiLow(v float64)`

SetCiLow sets CiLow field to given value.


### GetDecision

`func (o *GateComparisonResponse) GetDecision() GateDecision`

GetDecision returns the Decision field if non-nil, zero value otherwise.

### GetDecisionOk

`func (o *GateComparisonResponse) GetDecisionOk() (*GateDecision, bool)`

GetDecisionOk returns a tuple with the Decision field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDecision

`func (o *GateComparisonResponse) SetDecision(v GateDecision)`

SetDecision sets Decision field to given value.


### GetDelta

`func (o *GateComparisonResponse) GetDelta() float64`

GetDelta returns the Delta field if non-nil, zero value otherwise.

### GetDeltaOk

`func (o *GateComparisonResponse) GetDeltaOk() (*float64, bool)`

GetDeltaOk returns a tuple with the Delta field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDelta

`func (o *GateComparisonResponse) SetDelta(v float64)`

SetDelta sets Delta field to given value.


### GetPValue

`func (o *GateComparisonResponse) GetPValue() float64`

GetPValue returns the PValue field if non-nil, zero value otherwise.

### GetPValueOk

`func (o *GateComparisonResponse) GetPValueOk() (*float64, bool)`

GetPValueOk returns a tuple with the PValue field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetPValue

`func (o *GateComparisonResponse) SetPValue(v float64)`

SetPValue sets PValue field to given value.


### GetSampleSize

`func (o *GateComparisonResponse) GetSampleSize() int32`

GetSampleSize returns the SampleSize field if non-nil, zero value otherwise.

### GetSampleSizeOk

`func (o *GateComparisonResponse) GetSampleSizeOk() (*int32, bool)`

GetSampleSizeOk returns a tuple with the SampleSize field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetSampleSize

`func (o *GateComparisonResponse) SetSampleSize(v int32)`

SetSampleSize sets SampleSize field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)
