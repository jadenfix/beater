# OverfitResponse

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Gap** | **float64** | &#x60;optimize_lift − holdout_lift&#x60;. | 
**GapCiHigh** | **float64** | Upper bound of the bootstrap CI for &#x60;gap&#x60;. | 
**GapCiLow** | **float64** | Lower bound of the bootstrap CI for &#x60;gap&#x60;. | 
**HoldoutLift** | **float64** | Mean paired lift on the held-out split. | 
**OptimizeLift** | **float64** | Mean paired lift &#x60;(candidate − baseline)&#x60; on the optimization split. | 
**Overfit** | **bool** | &#x60;true&#x60; when the gap&#39;s CI lower bound exceeds tolerance — the candidate&#39;s optimization-set advantage is significantly not reproduced on held-out data. | 

## Methods

### NewOverfitResponse

`func NewOverfitResponse(gap float64, gapCiHigh float64, gapCiLow float64, holdoutLift float64, optimizeLift float64, overfit bool, ) *OverfitResponse`

NewOverfitResponse instantiates a new OverfitResponse object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewOverfitResponseWithDefaults

`func NewOverfitResponseWithDefaults() *OverfitResponse`

NewOverfitResponseWithDefaults instantiates a new OverfitResponse object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetGap

`func (o *OverfitResponse) GetGap() float64`

GetGap returns the Gap field if non-nil, zero value otherwise.

### GetGapOk

`func (o *OverfitResponse) GetGapOk() (*float64, bool)`

GetGapOk returns a tuple with the Gap field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGap

`func (o *OverfitResponse) SetGap(v float64)`

SetGap sets Gap field to given value.


### GetGapCiHigh

`func (o *OverfitResponse) GetGapCiHigh() float64`

GetGapCiHigh returns the GapCiHigh field if non-nil, zero value otherwise.

### GetGapCiHighOk

`func (o *OverfitResponse) GetGapCiHighOk() (*float64, bool)`

GetGapCiHighOk returns a tuple with the GapCiHigh field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGapCiHigh

`func (o *OverfitResponse) SetGapCiHigh(v float64)`

SetGapCiHigh sets GapCiHigh field to given value.


### GetGapCiLow

`func (o *OverfitResponse) GetGapCiLow() float64`

GetGapCiLow returns the GapCiLow field if non-nil, zero value otherwise.

### GetGapCiLowOk

`func (o *OverfitResponse) GetGapCiLowOk() (*float64, bool)`

GetGapCiLowOk returns a tuple with the GapCiLow field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetGapCiLow

`func (o *OverfitResponse) SetGapCiLow(v float64)`

SetGapCiLow sets GapCiLow field to given value.


### GetHoldoutLift

`func (o *OverfitResponse) GetHoldoutLift() float64`

GetHoldoutLift returns the HoldoutLift field if non-nil, zero value otherwise.

### GetHoldoutLiftOk

`func (o *OverfitResponse) GetHoldoutLiftOk() (*float64, bool)`

GetHoldoutLiftOk returns a tuple with the HoldoutLift field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetHoldoutLift

`func (o *OverfitResponse) SetHoldoutLift(v float64)`

SetHoldoutLift sets HoldoutLift field to given value.


### GetOptimizeLift

`func (o *OverfitResponse) GetOptimizeLift() float64`

GetOptimizeLift returns the OptimizeLift field if non-nil, zero value otherwise.

### GetOptimizeLiftOk

`func (o *OverfitResponse) GetOptimizeLiftOk() (*float64, bool)`

GetOptimizeLiftOk returns a tuple with the OptimizeLift field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOptimizeLift

`func (o *OverfitResponse) SetOptimizeLift(v float64)`

SetOptimizeLift sets OptimizeLift field to given value.


### GetOverfit

`func (o *OverfitResponse) GetOverfit() bool`

GetOverfit returns the Overfit field if non-nil, zero value otherwise.

### GetOverfitOk

`func (o *OverfitResponse) GetOverfitOk() (*bool, bool)`

GetOverfitOk returns a tuple with the Overfit field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetOverfit

`func (o *OverfitResponse) SetOverfit(v bool)`

SetOverfit sets Overfit field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


