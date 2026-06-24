# \ProviderSecretsAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**CreateProviderSecret**](ProviderSecretsAPI.md#CreateProviderSecret) | **Post** /v1/provider-secrets/{tenant_id}/{project_id} | 
[**ListProviderSecrets**](ProviderSecretsAPI.md#ListProviderSecrets) | **Get** /v1/provider-secrets/{tenant_id}/{project_id} | 
[**RevokeProviderSecret**](ProviderSecretsAPI.md#RevokeProviderSecret) | **Post** /v1/provider-secrets/{tenant_id}/{project_id}/{provider_secret_id}/revoke | 



## CreateProviderSecret

> ProviderSecretMetadata CreateProviderSecret(ctx, tenantId, projectId).CreateProviderSecretHttpRequest(createProviderSecretHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	createProviderSecretHttpRequest := *openapiclient.NewCreateProviderSecretHttpRequest("DisplayName_example", "Provider_example", "SecretValue_example") // CreateProviderSecretHttpRequest | 
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ProviderSecretsAPI.CreateProviderSecret(context.Background(), tenantId, projectId).CreateProviderSecretHttpRequest(createProviderSecretHttpRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ProviderSecretsAPI.CreateProviderSecret``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `CreateProviderSecret`: ProviderSecretMetadata
	fmt.Fprintf(os.Stdout, "Response from `ProviderSecretsAPI.CreateProviderSecret`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiCreateProviderSecretRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------


 **createProviderSecretHttpRequest** | [**CreateProviderSecretHttpRequest**](CreateProviderSecretHttpRequest.md) |  | 
 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**ProviderSecretMetadata**](ProviderSecretMetadata.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## ListProviderSecrets

> []ProviderSecretMetadata ListProviderSecrets(ctx, tenantId, projectId).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ProviderSecretsAPI.ListProviderSecrets(context.Background(), tenantId, projectId).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ProviderSecretsAPI.ListProviderSecrets``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `ListProviderSecrets`: []ProviderSecretMetadata
	fmt.Fprintf(os.Stdout, "Response from `ProviderSecretsAPI.ListProviderSecrets`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiListProviderSecretsRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------


 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**[]ProviderSecretMetadata**](ProviderSecretMetadata.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)


## RevokeProviderSecret

> RevokedProviderSecret RevokeProviderSecret(ctx, tenantId, projectId, providerSecretId).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



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
	providerSecretId := "providerSecretId_example" // string | provider_secret_id
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.ProviderSecretsAPI.RevokeProviderSecret(context.Background(), tenantId, projectId, providerSecretId).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `ProviderSecretsAPI.RevokeProviderSecret``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `RevokeProviderSecret`: RevokedProviderSecret
	fmt.Fprintf(os.Stdout, "Response from `ProviderSecretsAPI.RevokeProviderSecret`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id | 
**projectId** | **string** | project_id | 
**providerSecretId** | **string** | provider_secret_id | 

### Other Parameters

Other parameters are passed through a pointer to a apiRevokeProviderSecretRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------



 **authorization** | **string** | Bearer API token for strict auth | 
 **xBeaterApiKey** | **string** | API key alternative for strict auth | 
 **xBeaterProjectId** | **string** | Strict-auth project scope | 
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope | 

### Return type

[**RevokedProviderSecret**](RevokedProviderSecret.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)

