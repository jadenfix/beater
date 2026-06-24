# EvalsApi

All URIs are relative to *http://localhost*

| Method | HTTP request | Description |
|------------- | ------------- | -------------|
| [**runDeterministicEval**](EvalsApi.md#runDeterministicEval) | **POST** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/evals/deterministic |  |
| [**runDeterministicEvalWithHttpInfo**](EvalsApi.md#runDeterministicEvalWithHttpInfo) | **POST** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/evals/deterministic |  |
| [**runJudgeEval**](EvalsApi.md#runJudgeEval) | **POST** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/evals/judge |  |
| [**runJudgeEvalWithHttpInfo**](EvalsApi.md#runJudgeEvalWithHttpInfo) | **POST** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/evals/judge |  |



## runDeterministicEval

> DatasetEvalReport runDeterministicEval(tenantId, projectId, datasetId, versionId, runDeterministicEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.EvalsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        EvalsApi apiInstance = new EvalsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String datasetId = "datasetId_example"; // String | dataset_id
        String versionId = "versionId_example"; // String | version_id
        RunDeterministicEvalRequest runDeterministicEvalRequest = new RunDeterministicEvalRequest(); // RunDeterministicEvalRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            DatasetEvalReport result = apiInstance.runDeterministicEval(tenantId, projectId, datasetId, versionId, runDeterministicEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling EvalsApi#runDeterministicEval");
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
| **datasetId** | **String**| dataset_id | |
| **versionId** | **String**| version_id | |
| **runDeterministicEvalRequest** | [**RunDeterministicEvalRequest**](RunDeterministicEvalRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**DatasetEvalReport**](DatasetEvalReport.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Run a deterministic dataset evaluation |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

## runDeterministicEvalWithHttpInfo

> ApiResponse<DatasetEvalReport> runDeterministicEval runDeterministicEvalWithHttpInfo(tenantId, projectId, datasetId, versionId, runDeterministicEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.EvalsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        EvalsApi apiInstance = new EvalsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String datasetId = "datasetId_example"; // String | dataset_id
        String versionId = "versionId_example"; // String | version_id
        RunDeterministicEvalRequest runDeterministicEvalRequest = new RunDeterministicEvalRequest(); // RunDeterministicEvalRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<DatasetEvalReport> response = apiInstance.runDeterministicEvalWithHttpInfo(tenantId, projectId, datasetId, versionId, runDeterministicEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling EvalsApi#runDeterministicEval");
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
| **datasetId** | **String**| dataset_id | |
| **versionId** | **String**| version_id | |
| **runDeterministicEvalRequest** | [**RunDeterministicEvalRequest**](RunDeterministicEvalRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**DatasetEvalReport**](DatasetEvalReport.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Run a deterministic dataset evaluation |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |


## runJudgeEval

> DatasetEvalReport runJudgeEval(tenantId, projectId, datasetId, versionId, runJudgeDatasetEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.EvalsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        EvalsApi apiInstance = new EvalsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String datasetId = "datasetId_example"; // String | dataset_id
        String versionId = "versionId_example"; // String | version_id
        RunJudgeDatasetEvalRequest runJudgeDatasetEvalRequest = new RunJudgeDatasetEvalRequest(); // RunJudgeDatasetEvalRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            DatasetEvalReport result = apiInstance.runJudgeEval(tenantId, projectId, datasetId, versionId, runJudgeDatasetEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling EvalsApi#runJudgeEval");
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
| **datasetId** | **String**| dataset_id | |
| **versionId** | **String**| version_id | |
| **runJudgeDatasetEvalRequest** | [**RunJudgeDatasetEvalRequest**](RunJudgeDatasetEvalRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**DatasetEvalReport**](DatasetEvalReport.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Run a judge dataset evaluation |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

## runJudgeEvalWithHttpInfo

> ApiResponse<DatasetEvalReport> runJudgeEval runJudgeEvalWithHttpInfo(tenantId, projectId, datasetId, versionId, runJudgeDatasetEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.EvalsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        EvalsApi apiInstance = new EvalsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String datasetId = "datasetId_example"; // String | dataset_id
        String versionId = "versionId_example"; // String | version_id
        RunJudgeDatasetEvalRequest runJudgeDatasetEvalRequest = new RunJudgeDatasetEvalRequest(); // RunJudgeDatasetEvalRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<DatasetEvalReport> response = apiInstance.runJudgeEvalWithHttpInfo(tenantId, projectId, datasetId, versionId, runJudgeDatasetEvalRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling EvalsApi#runJudgeEval");
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
| **datasetId** | **String**| dataset_id | |
| **versionId** | **String**| version_id | |
| **runJudgeDatasetEvalRequest** | [**RunJudgeDatasetEvalRequest**](RunJudgeDatasetEvalRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**DatasetEvalReport**](DatasetEvalReport.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Run a judge dataset evaluation |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

