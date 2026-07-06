# GateCandidateChangeRequest

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**Description** | **string** | Human-readable description of the proposed change. |
**Kind** | [**ChangeKind**](ChangeKind.md) | The policy lever this change touches (e.g. &#x60;system_prompt&#x60;, &#x60;model_params&#x60;). |
**ProposedBy** | [**OptimizerStrategy**](OptimizerStrategy.md) | Which optimizer strategy emitted the candidate (e.g. &#x60;llm_rewrite&#x60;). |
**Rationale** | **string** | Why the proposer believes this change helps (carried for audit). |
**Target** | **string** | The file / symbol / prompt the change targets. |

## Methods

### NewGateCandidateChangeRequest

`func NewGateCandidateChangeRequest(description string, kind ChangeKind, proposedBy OptimizerStrategy, rationale string, target string, ) *GateCandidateChangeRequest`

NewGateCandidateChangeRequest instantiates a new GateCandidateChangeRequest object
This constructor will assign default values to properties that have it defined,
and makes sure properties required by API are set, but the set of arguments
will change when the set of required properties is changed

### NewGateCandidateChangeRequestWithDefaults

`func NewGateCandidateChangeRequestWithDefaults() *GateCandidateChangeRequest`

NewGateCandidateChangeRequestWithDefaults instantiates a new GateCandidateChangeRequest object
This constructor will only assign default values to properties that have it defined,
but it doesn't guarantee that properties required by API are set

### GetDescription

`func (o *GateCandidateChangeRequest) GetDescription() string`

GetDescription returns the Description field if non-nil, zero value otherwise.

### GetDescriptionOk

`func (o *GateCandidateChangeRequest) GetDescriptionOk() (*string, bool)`

GetDescriptionOk returns a tuple with the Description field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetDescription

`func (o *GateCandidateChangeRequest) SetDescription(v string)`

SetDescription sets Description field to given value.


### GetKind

`func (o *GateCandidateChangeRequest) GetKind() ChangeKind`

GetKind returns the Kind field if non-nil, zero value otherwise.

### GetKindOk

`func (o *GateCandidateChangeRequest) GetKindOk() (*ChangeKind, bool)`

GetKindOk returns a tuple with the Kind field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetKind

`func (o *GateCandidateChangeRequest) SetKind(v ChangeKind)`

SetKind sets Kind field to given value.


### GetProposedBy

`func (o *GateCandidateChangeRequest) GetProposedBy() OptimizerStrategy`

GetProposedBy returns the ProposedBy field if non-nil, zero value otherwise.

### GetProposedByOk

`func (o *GateCandidateChangeRequest) GetProposedByOk() (*OptimizerStrategy, bool)`

GetProposedByOk returns a tuple with the ProposedBy field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetProposedBy

`func (o *GateCandidateChangeRequest) SetProposedBy(v OptimizerStrategy)`

SetProposedBy sets ProposedBy field to given value.


### GetRationale

`func (o *GateCandidateChangeRequest) GetRationale() string`

GetRationale returns the Rationale field if non-nil, zero value otherwise.

### GetRationaleOk

`func (o *GateCandidateChangeRequest) GetRationaleOk() (*string, bool)`

GetRationaleOk returns a tuple with the Rationale field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetRationale

`func (o *GateCandidateChangeRequest) SetRationale(v string)`

SetRationale sets Rationale field to given value.


### GetTarget

`func (o *GateCandidateChangeRequest) GetTarget() string`

GetTarget returns the Target field if non-nil, zero value otherwise.

### GetTargetOk

`func (o *GateCandidateChangeRequest) GetTargetOk() (*string, bool)`

GetTargetOk returns a tuple with the Target field if it's non-nil, zero value otherwise
and a boolean to check if the value has been set.

### SetTarget

`func (o *GateCandidateChangeRequest) SetTarget(v string)`

SetTarget sets Target field to given value.



[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)
