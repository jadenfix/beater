# RollupEstimate

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Value** | **float64** |  | 
**Weighting** | [**RollupWeighting**](RollupWeighting.md) |  | 

## Methods

### NewRollupEstimate

`func NewRollupEstimate(value float64, weighting RollupWeighting, ) *RollupEstimate`

NewRollupEstimate instantiates a new RollupEstimate object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewRollupEstimateWithDefaults

`func NewRollupEstimateWithDefaults() *RollupEstimate`

NewRollupEstimateWithDefaults instantiates a new RollupEstimate object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetValue

`func (o *RollupEstimate) GetValue() float64`

GetValue returns the Value field if non-nil, zero value otherwise.

### GetValueOk

`func (o *RollupEstimate) GetValueOk() (*float64, bool)`

GetValueOk returns a tuple with the Value field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetValue

`func (o *RollupEstimate) SetValue(v float64)`

SetValue sets Value field to given value.


### GetWeighting

`func (o *RollupEstimate) GetWeighting() RollupWeighting`

GetWeighting returns the Weighting field if non-nil, zero value otherwise.

### GetWeightingOk

`func (o *RollupEstimate) GetWeightingOk() (*RollupWeighting, bool)`

GetWeightingOk returns a tuple with the Weighting field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetWeighting

`func (o *RollupEstimate) SetWeighting(v RollupWeighting)`

SetWeighting sets Weighting field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


