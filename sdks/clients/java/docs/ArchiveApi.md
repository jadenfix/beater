# ArchiveApi

All URIs are relative to *http://localhost*

| Method | HTTP request | Description |
|------------- | ------------- | -------------|
| [**archiveTrace**](ArchiveApi.md#archiveTrace) | **POST** /v1/archive/{tenant_id}/{project_id}/{trace_id} |  |
| [**archiveTraceWithHttpInfo**](ArchiveApi.md#archiveTraceWithHttpInfo) | **POST** /v1/archive/{tenant_id}/{project_id}/{trace_id} |  |
| [**queryArchiveSpans**](ArchiveApi.md#queryArchiveSpans) | **GET** /v1/archive/{tenant_id}/{project_id}/spans |  |
| [**queryArchiveSpansWithHttpInfo**](ArchiveApi.md#queryArchiveSpansWithHttpInfo) | **GET** /v1/archive/{tenant_id}/{project_id}/spans |  |



## archiveTrace

> ArchiveManifest archiveTrace(tenantId, projectId, traceId, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ArchiveApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ArchiveApi apiInstance = new ArchiveApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String traceId = "traceId_example"; // String | trace_id
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ArchiveManifest result = apiInstance.archiveTrace(tenantId, projectId, traceId, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling ArchiveApi#archiveTrace");
            System.err.println("Status code: " + e.getCode());
            System.err.println("Reason: " + e.getResponseBody());
            System.err.println("Response headers: " + e.getResponseHeaders());
            e.printStackTrace();
        }
    }
}
```

### Parameters


| Name | Type | Description  | Notes |
|------------- | ------------- | ------------- | -------------|
| **tenantId** | **String**| tenant_id | |
| **projectId** | **String**| project_id | |
| **traceId** | **String**| trace_id | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**ArchiveManifest**](ArchiveManifest.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Archive a trace to object storage |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

## archiveTraceWithHttpInfo

> ApiResponse<ArchiveManifest> archiveTrace archiveTraceWithHttpInfo(tenantId, projectId, traceId, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ArchiveApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ArchiveApi apiInstance = new ArchiveApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String traceId = "traceId_example"; // String | trace_id
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<ArchiveManifest> response = apiInstance.archiveTraceWithHttpInfo(tenantId, projectId, traceId, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling ArchiveApi#archiveTrace");
            System.err.println("Status code: " + e.getCode());
            System.err.println("Response headers: " + e.getResponseHeaders());
            System.err.println("Reason: " + e.getResponseBody());
            e.printStackTrace();
        }
    }
}
```

### Parameters


| Name | Type | Description  | Notes |
|------------- | ------------- | ------------- | -------------|
| **tenantId** | **String**| tenant_id | |
| **projectId** | **String**| project_id | |
| **traceId** | **String**| trace_id | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**ArchiveManifest**](ArchiveManifest.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Archive a trace to object storage |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |


## queryArchiveSpans

> ArchiveQueryResponse queryArchiveSpans(tenantId, projectId, environmentId, traceId, spanId, kind, status, limit, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ArchiveApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ArchiveApi apiInstance = new ArchiveApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String environmentId = "environmentId_example"; // String | 
        String traceId = "traceId_example"; // String | 
        String spanId = "spanId_example"; // String | 
        String kind = "kind_example"; // String | 
        String status = "status_example"; // String | 
        Integer limit = 56; // Integer | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ArchiveQueryResponse result = apiInstance.queryArchiveSpans(tenantId, projectId, environmentId, traceId, spanId, kind, status, limit, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling ArchiveApi#queryArchiveSpans");
            System.err.println("Status code: " + e.getCode());
            System.err.println("Reason: " + e.getResponseBody());
            System.err.println("Response headers: " + e.getResponseHeaders());
            e.printStackTrace();
        }
    }
}
```

### Parameters


| Name | Type | Description  | Notes |
|------------- | ------------- | ------------- | -------------|
| **tenantId** | **String**| tenant_id | |
| **projectId** | **String**| project_id | |
| **environmentId** | **String**|  | [optional] |
| **traceId** | **String**|  | [optional] |
| **spanId** | **String**|  | [optional] |
| **kind** | **String**|  | [optional] |
| **status** | **String**|  | [optional] |
| **limit** | **Integer**|  | [optional] |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**ArchiveQueryResponse**](ArchiveQueryResponse.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Query archived spans |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |

## queryArchiveSpansWithHttpInfo

> ApiResponse<ArchiveQueryResponse> queryArchiveSpans queryArchiveSpansWithHttpInfo(tenantId, projectId, environmentId, traceId, spanId, kind, status, limit, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ArchiveApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ArchiveApi apiInstance = new ArchiveApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String environmentId = "environmentId_example"; // String | 
        String traceId = "traceId_example"; // String | 
        String spanId = "spanId_example"; // String | 
        String kind = "kind_example"; // String | 
        String status = "status_example"; // String | 
        Integer limit = 56; // Integer | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<ArchiveQueryResponse> response = apiInstance.queryArchiveSpansWithHttpInfo(tenantId, projectId, environmentId, traceId, spanId, kind, status, limit, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling ArchiveApi#queryArchiveSpans");
            System.err.println("Status code: " + e.getCode());
            System.err.println("Response headers: " + e.getResponseHeaders());
            System.err.println("Reason: " + e.getResponseBody());
            e.printStackTrace();
        }
    }
}
```

### Parameters


| Name | Type | Description  | Notes |
|------------- | ------------- | ------------- | -------------|
| **tenantId** | **String**| tenant_id | |
| **projectId** | **String**| project_id | |
| **environmentId** | **String**|  | [optional] |
| **traceId** | **String**|  | [optional] |
| **spanId** | **String**|  | [optional] |
| **kind** | **String**|  | [optional] |
| **status** | **String**|  | [optional] |
| **limit** | **Integer**|  | [optional] |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**ArchiveQueryResponse**](ArchiveQueryResponse.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Query archived spans |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |

