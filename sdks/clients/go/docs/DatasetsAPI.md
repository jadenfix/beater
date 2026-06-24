# \DatasetsAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**CreateDataset**](DatasetsAPI.md#CreateDataset) | **Post** /v1/datasets/{tenant_id}/{project_id} | 
[**CreateDatasetVersion**](DatasetsAPI.md#CreateDatasetVersion) | **Post** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/versions | 
[**PromoteDatasetCaseFromTrace**](DatasetsAPI.md#PromoteDatasetCaseFromTrace) | **Post** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/cases/from-trace | 



## CreateDataset

> Dataset CreateDataset(ctx, tenantId, projectId).CreateDatasetRequest(createDatasetRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	createDatasetRequest := *openapiclient.NewCreateDatasetRequest("Name_example") // CreateDatasetRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.DatasetsAPI.CreateDataset(context.Background(), tenantId, projectId).CreateDatasetRequest(createDatasetRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `DatasetsAPI.CreateDataset``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `CreateDataset`: Dataset
	fmt.Fprintf(os.Stdout, "Response from `DatasetsAPI.CreateDataset`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiCreateDatasetRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------


 **createDatasetRequest** | [**CreateDatasetRequest**](CreateDatasetRequest.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**Dataset**](Dataset.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## CreateDatasetVersion

> DatasetVersionSnapshot CreateDatasetVersion(ctx, tenantId, projectId, datasetId).CreateDatasetVersionRequest(createDatasetVersionRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	datasetId := "datasetId_example" // string | dataset_id
	createDatasetVersionRequest := *openapiclient.NewCreateDatasetVersionRequest() // CreateDatasetVersionRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.DatasetsAPI.CreateDatasetVersion(context.Background(), tenantId, projectId, datasetId).CreateDatasetVersionRequest(createDatasetVersionRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `DatasetsAPI.CreateDatasetVersion``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `CreateDatasetVersion`: DatasetVersionSnapshot
	fmt.Fprintf(os.Stdout, "Response from `DatasetsAPI.CreateDatasetVersion`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**datasetId** | **string** | dataset_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiCreateDatasetVersionRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------



 **createDatasetVersionRequest** | [**CreateDatasetVersionRequest**](CreateDatasetVersionRequest.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**DatasetVersionSnapshot**](DatasetVersionSnapshot.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## PromoteDatasetCaseFromTrace

> DatasetCase PromoteDatasetCaseFromTrace(ctx, tenantId, projectId, datasetId).PromoteTraceCaseRequest(promoteTraceCaseRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	datasetId := "datasetId_example" // string | dataset_id
	promoteTraceCaseRequest := *openapiclient.NewPromoteTraceCaseRequest("TraceId_example") // PromoteTraceCaseRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.DatasetsAPI.PromoteDatasetCaseFromTrace(context.Background(), tenantId, projectId, datasetId).PromoteTraceCaseRequest(promoteTraceCaseRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `DatasetsAPI.PromoteDatasetCaseFromTrace``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `PromoteDatasetCaseFromTrace`: DatasetCase
	fmt.Fprintf(os.Stdout, "Response from `DatasetsAPI.PromoteDatasetCaseFromTrace`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**datasetId** | **string** | dataset_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiPromoteDatasetCaseFromTraceRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------



 **promoteTraceCaseRequest** | [**PromoteTraceCaseRequest**](PromoteTraceCaseRequest.md) |  | 
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

