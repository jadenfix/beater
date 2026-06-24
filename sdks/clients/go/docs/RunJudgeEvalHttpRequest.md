# RunJudgeEvalHttpRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Case** | [**EvaluationCase**](EvaluationCase.md) |  | 
**Evaluator** | [**EvaluatorSpec**](EvaluatorSpec.md) |  | 
**ProviderSecretId** | **string** |  | 

## Methods

### NewRunJudgeEvalHttpRequest

`func NewRunJudgeEvalHttpRequest(case_ EvaluationCase, evaluator EvaluatorSpec, providerSecretId string, ) *RunJudgeEvalHttpRequest`

NewRunJudgeEvalHttpRequest instantiates a new RunJudgeEvalHttpRequest object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewRunJudgeEvalHttpRequestWithDefaults

`func NewRunJudgeEvalHttpRequestWithDefaults() *RunJudgeEvalHttpRequest`

NewRunJudgeEvalHttpRequestWithDefaults instantiates a new RunJudgeEvalHttpRequest object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetCase

`func (o *RunJudgeEvalHttpRequest) GetCase() EvaluationCase`

GetCase returns the Case field if non-nil, zero value otherwise.

### GetCaseOk

`func (o *RunJudgeEvalHttpRequest) GetCaseOk() (*EvaluationCase, bool)`

GetCaseOk returns a tuple with the Case field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetCase

`func (o *RunJudgeEvalHttpRequest) SetCase(v EvaluationCase)`

SetCase sets Case field to given value.


### GetEvaluator

`func (o *RunJudgeEvalHttpRequest) GetEvaluator() EvaluatorSpec`

GetEvaluator returns the Evaluator field if non-nil, zero value otherwise.

### GetEvaluatorOk

`func (o *RunJudgeEvalHttpRequest) GetEvaluatorOk() (*EvaluatorSpec, bool)`

GetEvaluatorOk returns a tuple with the Evaluator field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetEvaluator

`func (o *RunJudgeEvalHttpRequest) SetEvaluator(v EvaluatorSpec)`

SetEvaluator sets Evaluator field to given value.


### GetProviderSecretId

`func (o *RunJudgeEvalHttpRequest) GetProviderSecretId() string`

GetProviderSecretId returns the ProviderSecretId field if non-nil, zero value otherwise.

### GetProviderSecretIdOk

`func (o *RunJudgeEvalHttpRequest) GetProviderSecretIdOk() (*string, bool)`

GetProviderSecretIdOk returns a tuple with the ProviderSecretId field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetProviderSecretId

`func (o *RunJudgeEvalHttpRequest) SetProviderSecretId(v string)`

SetProviderSecretId sets ProviderSecretId field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


