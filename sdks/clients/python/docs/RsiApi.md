# beater_client.RsiApi

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**gate_optimization_candidate**](RsiApi.md#gate_optimization_candidate) | **POST** /v1/rsi/{tenant_id}/{project_id}/gate-candidate | 


# **gate_optimization_candidate**
> GateCandidateResponse gate_optimization_candidate(tenant_id, project_id, gate_candidate_request, authorization=authorization, x_beater_api_key=x_beater_api_key, x_beater_project_id=x_beater_project_id, x_beater_environment_id=x_beater_environment_id)



### Example


```python
import beater_client
from beater_client.models.gate_candidate_request import GateCandidateRequest
from beater_client.models.gate_candidate_response import GateCandidateResponse
from beater_client.rest import ApiException
from pprint import pprint

# Defining the host is optional and defaults to http://localhost
# See configuration.py for a list of all supported configuration parameters.
configuration = beater_client.Configuration(
    host = "http://localhost"
)


# Enter a context with an instance of the API client
with beater_client.ApiClient(configuration) as api_client:
    # Create an instance of the API class
    api_instance = beater_client.RsiApi(api_client)
    tenant_id = 'tenant_id_example' # str | tenant_id
    project_id = 'project_id_example' # str | project_id
    gate_candidate_request = beater_client.GateCandidateRequest() # GateCandidateRequest | 
    authorization = 'authorization_example' # str | Bearer API token for strict auth (optional)
    x_beater_api_key = 'x_beater_api_key_example' # str | API key alternative for strict auth (optional)
    x_beater_project_id = 'x_beater_project_id_example' # str | Strict-auth project scope (optional)
    x_beater_environment_id = 'x_beater_environment_id_example' # str | Strict-auth environment scope (optional)

    try:
        api_response = api_instance.gate_optimization_candidate(tenant_id, project_id, gate_candidate_request, authorization=authorization, x_beater_api_key=x_beater_api_key, x_beater_project_id=x_beater_project_id, x_beater_environment_id=x_beater_environment_id)
        print("The response of RsiApi->gate_optimization_candidate:\n")
        pprint(api_response)
    except Exception as e:
        print("Exception when calling RsiApi->gate_optimization_candidate: %s\n" % e)
```



### Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **tenant_id** | **str**| tenant_id | 
 **project_id** | **str**| project_id | 
 **gate_candidate_request** | [**GateCandidateRequest**](GateCandidateRequest.md)|  | 
 **authorization** | **str**| Bearer API token for strict auth | [optional] 
 **x_beater_api_key** | **str**| API key alternative for strict auth | [optional] 
 **x_beater_project_id** | **str**| Strict-auth project scope | [optional] 
 **x_beater_environment_id** | **str**| Strict-auth environment scope | [optional] 

### Return type

[**GateCandidateResponse**](GateCandidateResponse.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

### HTTP response details

| Status code | Description | Response headers |
|-------------|-------------|------------------|
**200** | Gate an optimization candidate against the held-out Test split and the anti-overfitting guardrail |  -  |
**400** | Invalid request, scope, or under-powered split |  -  |
**401** | Missing or invalid credentials |  -  |
**403** | Credentials lack the required scope |  -  |

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

