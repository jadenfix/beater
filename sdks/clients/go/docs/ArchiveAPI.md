# \ArchiveAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**ArchiveTrace**](ArchiveAPI.md#ArchiveTrace) | **Post** /v1/archive/{tenant_id}/{project_id}/{trace_id} | 
[**QueryArchiveSpans**](ArchiveAPI.md#QueryArchiveSpans) | **Get** /v1/archive/{tenant_id}/{project_id}/spans | 



## ArchiveTrace

> ArchiveManifest ArchiveTrace(ctx, tenantId, projectId, traceId).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	traceId := "traceId_example" // string | trace_id
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ArchiveAPI.ArchiveTrace(context.Background(), tenantId, projectId, traceId).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ArchiveAPI.ArchiveTrace``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `ArchiveTrace`: ArchiveManifest
	fmt.Fprintf(os.Stdout, "Response from `ArchiveAPI.ArchiveTrace`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**traceId** | **string** | trace_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiArchiveTraceRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------



 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**ArchiveManifest**](ArchiveManifest.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## QueryArchiveSpans

> ArchiveQueryResponse QueryArchiveSpans(ctx, tenantId, projectId).EnvironmentId(environmentId).TraceId(traceId).SpanId(spanId).Kind(kind).Status(status).Limit(limit).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	environmentId := "environmentId_example" // string |  (optional)
	traceId := "traceId_example" // string |  (optional)
	spanId := "spanId_example" // string |  (optional)
	kind := "kind_example" // string |  (optional)
	status := "status_example" // string |  (optional)
	limit := int32(56) // int32 |  (optional)
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ArchiveAPI.QueryArchiveSpans(context.Background(), tenantId, projectId).EnvironmentId(environmentId).TraceId(traceId).SpanId(spanId).Kind(kind).Status(status).Limit(limit).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ArchiveAPI.QueryArchiveSpans``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `QueryArchiveSpans`: ArchiveQueryResponse
	fmt.Fprintf(os.Stdout, "Response from `ArchiveAPI.QueryArchiveSpans`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiQueryArchiveSpansRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------


 **environmentId** | **string** |  | 
 **traceId** | **string** |  | 
 **spanId** | **string** |  | 
 **kind** | **string** |  | 
 **status** | **string** |  | 
 **limit** | **int32** |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**ArchiveQueryResponse**](ArchiveQueryResponse.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)

