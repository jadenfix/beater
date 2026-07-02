# RsiAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**RsiAPI_gateOptimizationCandidate**](RsiAPI.md#RsiAPI_gateOptimizationCandidate) | **POST** /v1/rsi/{tenant_id}/{project_id}/gate-candidate | 


# **RsiAPI_gateOptimizationCandidate**
```c
gate_candidate_response_t* RsiAPI_gateOptimizationCandidate(apiClient_t *apiClient, char *tenant_id, char *project_id, gate_candidate_request_t *gate_candidate_request, char *authorization, char *x_beater_api_key, char *x_beater_project_id, char *x_beater_environment_id);
```

### Parameters
Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**apiClient** | **apiClient_t \*** | context containing the client configuration |
**tenant_id** | **char \*** | tenant_id | 
**project_id** | **char \*** | project_id | 
**gate_candidate_request** | **[gate_candidate_request_t](gate_candidate_request.md) \*** |  | 
**authorization** | **char \*** | Bearer API token for strict auth | [optional] 
**x_beater_api_key** | **char \*** | API key alternative for strict auth | [optional] 
**x_beater_project_id** | **char \*** | Strict-auth project scope | [optional] 
**x_beater_environment_id** | **char \*** | Strict-auth environment scope | [optional] 

### Return type

[gate_candidate_response_t](gate_candidate_response.md) *


### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

