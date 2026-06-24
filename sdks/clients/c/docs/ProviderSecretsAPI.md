# ProviderSecretsAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**ProviderSecretsAPI_createProviderSecret**](ProviderSecretsAPI.md#ProviderSecretsAPI_createProviderSecret) | **POST** /v1/provider-secrets/{tenant_id}/{project_id} | 
[**ProviderSecretsAPI_listProviderSecrets**](ProviderSecretsAPI.md#ProviderSecretsAPI_listProviderSecrets) | **GET** /v1/provider-secrets/{tenant_id}/{project_id} | 
[**ProviderSecretsAPI_revokeProviderSecret**](ProviderSecretsAPI.md#ProviderSecretsAPI_revokeProviderSecret) | **POST** /v1/provider-secrets/{tenant_id}/{project_id}/{provider_secret_id}/revoke | 


# **ProviderSecretsAPI_createProviderSecret**
```c
provider_secret_metadata_t* ProviderSecretsAPI_createProviderSecret(apiClient_t *apiClient, char *tenant_id, char *project_id, create_provider_secret_http_request_t *create_provider_secret_http_request, char *authorization, char *x_beater_api_key, char *x_beater_project_id, char *x_beater_environment_id);
```

### Parameters
Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**apiClient** | **apiClient_t \*** | context containing the client configuration |
**tenant_id** | **char \*** | tenant_id | 
**project_id** | **char \*** | project_id | 
**create_provider_secret_http_request** | **[create_provider_secret_http_request_t](create_provider_secret_http_request.md) \*** |  | 
**authorization** | **char \*** | Bearer API token for strict auth | [optional] 
**x_beater_api_key** | **char \*** | API key alternative for strict auth | [optional] 
**x_beater_project_id** | **char \*** | Strict-auth project scope | [optional] 
**x_beater_environment_id** | **char \*** | Strict-auth environment scope | [optional] 

### Return type

[provider_secret_metadata_t](provider_secret_metadata.md) *


### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **ProviderSecretsAPI_listProviderSecrets**
```c
list_t* ProviderSecretsAPI_listProviderSecrets(apiClient_t *apiClient, char *tenant_id, char *project_id, char *authorization, char *x_beater_api_key, char *x_beater_project_id, char *x_beater_environment_id);
```

### Parameters
Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**apiClient** | **apiClient_t \*** | context containing the client configuration |
**tenant_id** | **char \*** | tenant_id | 
**project_id** | **char \*** | project_id | 
**authorization** | **char \*** | Bearer API token for strict auth | [optional] 
**x_beater_api_key** | **char \*** | API key alternative for strict auth | [optional] 
**x_beater_project_id** | **char \*** | Strict-auth project scope | [optional] 
**x_beater_environment_id** | **char \*** | Strict-auth environment scope | [optional] 

### Return type

[list_t](provider_secret_metadata.md) *


### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **ProviderSecretsAPI_revokeProviderSecret**
```c
revoked_provider_secret_t* ProviderSecretsAPI_revokeProviderSecret(apiClient_t *apiClient, char *tenant_id, char *project_id, char *provider_secret_id, char *authorization, char *x_beater_api_key, char *x_beater_project_id, char *x_beater_environment_id);
```

### Parameters
Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**apiClient** | **apiClient_t \*** | context containing the client configuration |
**tenant_id** | **char \*** | tenant_id | 
**project_id** | **char \*** | project_id | 
**provider_secret_id** | **char \*** | provider_secret_id | 
**authorization** | **char \*** | Bearer API token for strict auth | [optional] 
**x_beater_api_key** | **char \*** | API key alternative for strict auth | [optional] 
**x_beater_project_id** | **char \*** | Strict-auth project scope | [optional] 
**x_beater_environment_id** | **char \*** | Strict-auth environment scope | [optional] 

### Return type

[revoked_provider_secret_t](revoked_provider_secret.md) *


### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

