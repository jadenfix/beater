# \ReviewsAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**CreateReviewQueue**](ReviewsAPI.md#CreateReviewQueue) | **Post** /v1/review-queues/{tenant_id}/{project_id} | 
[**EnqueueReviewTaskFromTrace**](ReviewsAPI.md#EnqueueReviewTaskFromTrace) | **Post** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/from-trace | 
[**ListReviewTasks**](ReviewsAPI.md#ListReviewTasks) | **Get** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks | 
[**PromoteReviewAnnotation**](ReviewsAPI.md#PromoteReviewAnnotation) | **Post** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations/{annotation_id}/promote | 
[**SubmitReviewAnnotation**](ReviewsAPI.md#SubmitReviewAnnotation) | **Post** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations | 



## CreateReviewQueue

> ReviewQueue CreateReviewQueue(ctx, tenantId, projectId).CreateReviewQueueHttpRequest(createReviewQueueHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/GIT_USER_ID/GIT_REPO_ID/beaterclient"
)

func main() {
	tenantId := "tenantId_example" // string | tenant_id
	projectId := "projectId_example" // string | project_id
	createReviewQueueHttpRequest := *openapiclient.NewCreateReviewQueueHttpRequest(interface{}(123), "Name_example") // CreateReviewQueueHttpRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ReviewsAPI.CreateReviewQueue(context.Background(), tenantId, projectId).CreateReviewQueueHttpRequest(createReviewQueueHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ReviewsAPI.CreateReviewQueue``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `CreateReviewQueue`: ReviewQueue
	fmt.Fprintf(os.Stdout, "Response from `ReviewsAPI.CreateReviewQueue`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiCreateReviewQueueRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------


 **createReviewQueueHttpRequest** | [**CreateReviewQueueHttpRequest**](CreateReviewQueueHttpRequest.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**ReviewQueue**](ReviewQueue.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## EnqueueReviewTaskFromTrace

> ReviewTask EnqueueReviewTaskFromTrace(ctx, tenantId, projectId, queueId).EnqueueReviewTaskFromTraceHttpRequest(enqueueReviewTaskFromTraceHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/GIT_USER_ID/GIT_REPO_ID/beaterclient"
)

func main() {
	tenantId := "tenantId_example" // string | tenant_id
	projectId := "projectId_example" // string | project_id
	queueId := "queueId_example" // string | queue_id
	enqueueReviewTaskFromTraceHttpRequest := *openapiclient.NewEnqueueReviewTaskFromTraceHttpRequest("TraceId_example") // EnqueueReviewTaskFromTraceHttpRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ReviewsAPI.EnqueueReviewTaskFromTrace(context.Background(), tenantId, projectId, queueId).EnqueueReviewTaskFromTraceHttpRequest(enqueueReviewTaskFromTraceHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ReviewsAPI.EnqueueReviewTaskFromTrace``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `EnqueueReviewTaskFromTrace`: ReviewTask
	fmt.Fprintf(os.Stdout, "Response from `ReviewsAPI.EnqueueReviewTaskFromTrace`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**queueId** | **string** | queue_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiEnqueueReviewTaskFromTraceRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------



 **enqueueReviewTaskFromTraceHttpRequest** | [**EnqueueReviewTaskFromTraceHttpRequest**](EnqueueReviewTaskFromTraceHttpRequest.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**ReviewTask**](ReviewTask.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## ListReviewTasks

> []ReviewTask ListReviewTasks(ctx, tenantId, projectId, queueId).State(state).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/GIT_USER_ID/GIT_REPO_ID/beaterclient"
)

func main() {
	tenantId := "tenantId_example" // string | tenant_id
	projectId := "projectId_example" // string | project_id
	queueId := "queueId_example" // string | queue_id
	state := openapiclient.ReviewTaskState("open") // ReviewTaskState |  (optional)
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ReviewsAPI.ListReviewTasks(context.Background(), tenantId, projectId, queueId).State(state).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ReviewsAPI.ListReviewTasks``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `ListReviewTasks`: []ReviewTask
	fmt.Fprintf(os.Stdout, "Response from `ReviewsAPI.ListReviewTasks`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**queueId** | **string** | queue_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiListReviewTasksRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------



 **state** | [**ReviewTaskState**](ReviewTaskState.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**[]ReviewTask**](ReviewTask.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## PromoteReviewAnnotation

> DatasetCase PromoteReviewAnnotation(ctx, tenantId, projectId, queueId, taskId, annotationId).PromoteReviewAnnotationHttpRequest(promoteReviewAnnotationHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/GIT_USER_ID/GIT_REPO_ID/beaterclient"
)

func main() {
	tenantId := "tenantId_example" // string | tenant_id
	projectId := "projectId_example" // string | project_id
	queueId := "queueId_example" // string | queue_id
	taskId := "taskId_example" // string | task_id
	annotationId := "annotationId_example" // string | annotation_id
	promoteReviewAnnotationHttpRequest := *openapiclient.NewPromoteReviewAnnotationHttpRequest("DatasetId_example") // PromoteReviewAnnotationHttpRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ReviewsAPI.PromoteReviewAnnotation(context.Background(), tenantId, projectId, queueId, taskId, annotationId).PromoteReviewAnnotationHttpRequest(promoteReviewAnnotationHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ReviewsAPI.PromoteReviewAnnotation``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `PromoteReviewAnnotation`: DatasetCase
	fmt.Fprintf(os.Stdout, "Response from `ReviewsAPI.PromoteReviewAnnotation`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**queueId** | **string** | queue_id | 
**taskId** | **string** | task_id | 
**annotationId** | **string** | annotation_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiPromoteReviewAnnotationRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------





 **promoteReviewAnnotationHttpRequest** | [**PromoteReviewAnnotationHttpRequest**](PromoteReviewAnnotationHttpRequest.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**DatasetCase**](DatasetCase.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## SubmitReviewAnnotation

> ReviewAnnotation SubmitReviewAnnotation(ctx, tenantId, projectId, queueId, taskId).SubmitReviewAnnotationHttpRequest(submitReviewAnnotationHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/GIT_USER_ID/GIT_REPO_ID/beaterclient"
)

func main() {
	tenantId := "tenantId_example" // string | tenant_id
	projectId := "projectId_example" // string | project_id
	queueId := "queueId_example" // string | queue_id
	taskId := "taskId_example" // string | task_id
	submitReviewAnnotationHttpRequest := *openapiclient.NewSubmitReviewAnnotationHttpRequest(interface{}(123), "ReviewerId_example", openapiclient.ReviewVerdict("pass")) // SubmitReviewAnnotationHttpRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ReviewsAPI.SubmitReviewAnnotation(context.Background(), tenantId, projectId, queueId, taskId).SubmitReviewAnnotationHttpRequest(submitReviewAnnotationHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ReviewsAPI.SubmitReviewAnnotation``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `SubmitReviewAnnotation`: ReviewAnnotation
	fmt.Fprintf(os.Stdout, "Response from `ReviewsAPI.SubmitReviewAnnotation`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**queueId** | **string** | queue_id | 
**taskId** | **string** | task_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiSubmitReviewAnnotationRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------




 **submitReviewAnnotationHttpRequest** | [**SubmitReviewAnnotationHttpRequest**](SubmitReviewAnnotationHttpRequest.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**ReviewAnnotation**](ReviewAnnotation.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)

