# ApiKeysAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**ApiKeysAPI_createApiKey**](ApiKeysAPI.md#ApiKeysAPI_createApiKey) | **POST** /v1/api-keys/{tenant_id}/{project_id}/{environment_id} | 
[**ApiKeysAPI_revokeApiKey**](ApiKeysAPI.md#ApiKeysAPI_revokeApiKey) | **POST** /v1/api-keys/{tenant_id}/{project_id}/{environment_id}/{api_key_id}/revoke | 


# **ApiKeysAPI_createApiKey**
```c
api_key_created_response_t* ApiKeysAPI_createApiKey(apiClient_t *apiClient, char *tenant_id, char *project_id, char *environment_id, create_api_key_http_request_t *create_api_key_http_request, char *authorization, char *x_beater_api_key, char *x_beater_project_id, char *x_beater_environment_id);
```

### Parameters
Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**apiClient** | **apiClient_t \*** | context containing the client configuration |
**tenant_id** | **char \*** | tenant_id | 
**project_id** | **char \*** | project_id | 
**environment_id** | **char \*** | environment_id | 
**create_api_key_http_request** | **[create_api_key_http_request_t](create_api_key_http_request.md) \*** |  | 
**authorization** | **char \*** | Bearer API token for strict auth | [optional] 
**x_beater_api_key** | **char \*** | API key alternative for strict auth | [optional] 
**x_beater_project_id** | **char \*** | Strict-auth project scope | [optional] 
**x_beater_environment_id** | **char \*** | Strict-auth environment scope | [optional] 

### Return type

[api_key_created_response_t](api_key_created_response.md) *


### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **ApiKeysAPI_revokeApiKey**
```c
revoked_api_key_t* ApiKeysAPI_revokeApiKey(apiClient_t *apiClient, char *tenant_id, char *project_id, char *environment_id, char *api_key_id, char *authorization, char *x_beater_api_key, char *x_beater_project_id, char *x_beater_environment_id);
```

### Parameters
Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**apiClient** | **apiClient_t \*** | context containing the client configuration |
**tenant_id** | **char \*** | tenant_id | 
**project_id** | **char \*** | project_id | 
**environment_id** | **char \*** | environment_id | 
**api_key_id** | **char \*** | api_key_id | 
**authorization** | **char \*** | Bearer API token for strict auth | [optional] 
**x_beater_api_key** | **char \*** | API key alternative for strict auth | [optional] 
**x_beater_project_id** | **char \*** | Strict-auth project scope | [optional] 
**x_beater_environment_id** | **char \*** | Strict-auth environment scope | [optional] 

### Return type

[revoked_api_key_t](revoked_api_key.md) *


### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

