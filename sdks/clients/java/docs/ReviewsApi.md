# ReviewsApi

All URIs are relative to *http://localhost*

| Method | HTTP request | Description |
|------------- | ------------- | -------------|
| [**createReviewQueue**](ReviewsApi.md#createReviewQueue) | **POST** /v1/review-queues/{tenant_id}/{project_id} |  |
| [**createReviewQueueWithHttpInfo**](ReviewsApi.md#createReviewQueueWithHttpInfo) | **POST** /v1/review-queues/{tenant_id}/{project_id} |  |
| [**enqueueReviewTaskFromTrace**](ReviewsApi.md#enqueueReviewTaskFromTrace) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/from-trace |  |
| [**enqueueReviewTaskFromTraceWithHttpInfo**](ReviewsApi.md#enqueueReviewTaskFromTraceWithHttpInfo) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/from-trace |  |
| [**listReviewTasks**](ReviewsApi.md#listReviewTasks) | **GET** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks |  |
| [**listReviewTasksWithHttpInfo**](ReviewsApi.md#listReviewTasksWithHttpInfo) | **GET** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks |  |
| [**promoteReviewAnnotation**](ReviewsApi.md#promoteReviewAnnotation) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations/{annotation_id}/promote |  |
| [**promoteReviewAnnotationWithHttpInfo**](ReviewsApi.md#promoteReviewAnnotationWithHttpInfo) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations/{annotation_id}/promote |  |
| [**submitReviewAnnotation**](ReviewsApi.md#submitReviewAnnotation) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations |  |
| [**submitReviewAnnotationWithHttpInfo**](ReviewsApi.md#submitReviewAnnotationWithHttpInfo) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations |  |



## createReviewQueue

> ReviewQueue createReviewQueue(tenantId, projectId, createReviewQueueHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        CreateReviewQueueHttpRequest createReviewQueueHttpRequest = new CreateReviewQueueHttpRequest(); // CreateReviewQueueHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ReviewQueue result = apiInstance.createReviewQueue(tenantId, projectId, createReviewQueueHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#createReviewQueue");
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
| **createReviewQueueHttpRequest** | [**CreateReviewQueueHttpRequest**](CreateReviewQueueHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**ReviewQueue**](ReviewQueue.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Create a human review queue |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |

## createReviewQueueWithHttpInfo

> ApiResponse<ReviewQueue> createReviewQueue createReviewQueueWithHttpInfo(tenantId, projectId, createReviewQueueHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        CreateReviewQueueHttpRequest createReviewQueueHttpRequest = new CreateReviewQueueHttpRequest(); // CreateReviewQueueHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<ReviewQueue> response = apiInstance.createReviewQueueWithHttpInfo(tenantId, projectId, createReviewQueueHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#createReviewQueue");
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
| **createReviewQueueHttpRequest** | [**CreateReviewQueueHttpRequest**](CreateReviewQueueHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**ReviewQueue**](ReviewQueue.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Create a human review queue |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |


## enqueueReviewTaskFromTrace

> ReviewTask enqueueReviewTaskFromTrace(tenantId, projectId, queueId, enqueueReviewTaskFromTraceHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        EnqueueReviewTaskFromTraceHttpRequest enqueueReviewTaskFromTraceHttpRequest = new EnqueueReviewTaskFromTraceHttpRequest(); // EnqueueReviewTaskFromTraceHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ReviewTask result = apiInstance.enqueueReviewTaskFromTrace(tenantId, projectId, queueId, enqueueReviewTaskFromTraceHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#enqueueReviewTaskFromTrace");
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
| **queueId** | **String**| queue_id | |
| **enqueueReviewTaskFromTraceHttpRequest** | [**EnqueueReviewTaskFromTraceHttpRequest**](EnqueueReviewTaskFromTraceHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**ReviewTask**](ReviewTask.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Enqueue a review task from a trace |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

## enqueueReviewTaskFromTraceWithHttpInfo

> ApiResponse<ReviewTask> enqueueReviewTaskFromTrace enqueueReviewTaskFromTraceWithHttpInfo(tenantId, projectId, queueId, enqueueReviewTaskFromTraceHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        EnqueueReviewTaskFromTraceHttpRequest enqueueReviewTaskFromTraceHttpRequest = new EnqueueReviewTaskFromTraceHttpRequest(); // EnqueueReviewTaskFromTraceHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<ReviewTask> response = apiInstance.enqueueReviewTaskFromTraceWithHttpInfo(tenantId, projectId, queueId, enqueueReviewTaskFromTraceHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#enqueueReviewTaskFromTrace");
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
| **queueId** | **String**| queue_id | |
| **enqueueReviewTaskFromTraceHttpRequest** | [**EnqueueReviewTaskFromTraceHttpRequest**](EnqueueReviewTaskFromTraceHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**ReviewTask**](ReviewTask.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Enqueue a review task from a trace |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |


## listReviewTasks

> List<ReviewTask> listReviewTasks(tenantId, projectId, queueId, state, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        ReviewTaskState state = ReviewTaskState.fromValue("open"); // ReviewTaskState | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            List<ReviewTask> result = apiInstance.listReviewTasks(tenantId, projectId, queueId, state, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#listReviewTasks");
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
| **queueId** | **String**| queue_id | |
| **state** | [**ReviewTaskState**](.md)|  | [optional] [enum: open, submitted, cancelled] |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**List&lt;ReviewTask&gt;**](ReviewTask.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | List review tasks |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

## listReviewTasksWithHttpInfo

> ApiResponse<List<ReviewTask>> listReviewTasks listReviewTasksWithHttpInfo(tenantId, projectId, queueId, state, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        ReviewTaskState state = ReviewTaskState.fromValue("open"); // ReviewTaskState | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<List<ReviewTask>> response = apiInstance.listReviewTasksWithHttpInfo(tenantId, projectId, queueId, state, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#listReviewTasks");
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
| **queueId** | **String**| queue_id | |
| **state** | [**ReviewTaskState**](.md)|  | [optional] [enum: open, submitted, cancelled] |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**List&lt;ReviewTask&gt;**](ReviewTask.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | List review tasks |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |


## promoteReviewAnnotation

> DatasetCase promoteReviewAnnotation(tenantId, projectId, queueId, taskId, annotationId, promoteReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        String taskId = "taskId_example"; // String | task_id
        String annotationId = "annotationId_example"; // String | annotation_id
        PromoteReviewAnnotationHttpRequest promoteReviewAnnotationHttpRequest = new PromoteReviewAnnotationHttpRequest(); // PromoteReviewAnnotationHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            DatasetCase result = apiInstance.promoteReviewAnnotation(tenantId, projectId, queueId, taskId, annotationId, promoteReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#promoteReviewAnnotation");
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
| **queueId** | **String**| queue_id | |
| **taskId** | **String**| task_id | |
| **annotationId** | **String**| annotation_id | |
| **promoteReviewAnnotationHttpRequest** | [**PromoteReviewAnnotationHttpRequest**](PromoteReviewAnnotationHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**DatasetCase**](DatasetCase.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Promote a review annotation to a dataset case |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

## promoteReviewAnnotationWithHttpInfo

> ApiResponse<DatasetCase> promoteReviewAnnotation promoteReviewAnnotationWithHttpInfo(tenantId, projectId, queueId, taskId, annotationId, promoteReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        String taskId = "taskId_example"; // String | task_id
        String annotationId = "annotationId_example"; // String | annotation_id
        PromoteReviewAnnotationHttpRequest promoteReviewAnnotationHttpRequest = new PromoteReviewAnnotationHttpRequest(); // PromoteReviewAnnotationHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<DatasetCase> response = apiInstance.promoteReviewAnnotationWithHttpInfo(tenantId, projectId, queueId, taskId, annotationId, promoteReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#promoteReviewAnnotation");
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
| **queueId** | **String**| queue_id | |
| **taskId** | **String**| task_id | |
| **annotationId** | **String**| annotation_id | |
| **promoteReviewAnnotationHttpRequest** | [**PromoteReviewAnnotationHttpRequest**](PromoteReviewAnnotationHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**DatasetCase**](DatasetCase.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Promote a review annotation to a dataset case |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |


## submitReviewAnnotation

> ReviewAnnotation submitReviewAnnotation(tenantId, projectId, queueId, taskId, submitReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        String taskId = "taskId_example"; // String | task_id
        SubmitReviewAnnotationHttpRequest submitReviewAnnotationHttpRequest = new SubmitReviewAnnotationHttpRequest(); // SubmitReviewAnnotationHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ReviewAnnotation result = apiInstance.submitReviewAnnotation(tenantId, projectId, queueId, taskId, submitReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println(result);
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#submitReviewAnnotation");
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
| **queueId** | **String**| queue_id | |
| **taskId** | **String**| task_id | |
| **submitReviewAnnotationHttpRequest** | [**SubmitReviewAnnotationHttpRequest**](SubmitReviewAnnotationHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

[**ReviewAnnotation**](ReviewAnnotation.md)


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Submit a review annotation |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

## submitReviewAnnotationWithHttpInfo

> ApiResponse<ReviewAnnotation> submitReviewAnnotation submitReviewAnnotationWithHttpInfo(tenantId, projectId, queueId, taskId, submitReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId)



### Example

```java
// Import classes:
import ai.beater.client.ApiClient;
import ai.beater.client.ApiException;
import ai.beater.client.ApiResponse;
import ai.beater.client.Configuration;
import ai.beater.client.models.*;
import ai.beater.client.api.ReviewsApi;

public class Example {
    public static void main(String[] args) {
        ApiClient defaultClient = Configuration.getDefaultApiClient();
        defaultClient.setBasePath("http://localhost");

        ReviewsApi apiInstance = new ReviewsApi(defaultClient);
        String tenantId = "tenantId_example"; // String | tenant_id
        String projectId = "projectId_example"; // String | project_id
        String queueId = "queueId_example"; // String | queue_id
        String taskId = "taskId_example"; // String | task_id
        SubmitReviewAnnotationHttpRequest submitReviewAnnotationHttpRequest = new SubmitReviewAnnotationHttpRequest(); // SubmitReviewAnnotationHttpRequest | 
        String authorization = "authorization_example"; // String | Bearer API token for strict auth
        String xBeaterApiKey = "xBeaterApiKey_example"; // String | API key alternative for strict auth
        String xBeaterProjectId = "xBeaterProjectId_example"; // String | Strict-auth project scope
        String xBeaterEnvironmentId = "xBeaterEnvironmentId_example"; // String | Strict-auth environment scope
        try {
            ApiResponse<ReviewAnnotation> response = apiInstance.submitReviewAnnotationWithHttpInfo(tenantId, projectId, queueId, taskId, submitReviewAnnotationHttpRequest, authorization, xBeaterApiKey, xBeaterProjectId, xBeaterEnvironmentId);
            System.out.println("Status code: " + response.getStatusCode());
            System.out.println("Response headers: " + response.getHeaders());
            System.out.println("Response body: " + response.getData());
        } catch (ApiException e) {
            System.err.println("Exception when calling ReviewsApi#submitReviewAnnotation");
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
| **queueId** | **String**| queue_id | |
| **taskId** | **String**| task_id | |
| **submitReviewAnnotationHttpRequest** | [**SubmitReviewAnnotationHttpRequest**](SubmitReviewAnnotationHttpRequest.md)|  | |
| **authorization** | **String**| Bearer API token for strict auth | [optional] |
| **xBeaterApiKey** | **String**| API key alternative for strict auth | [optional] |
| **xBeaterProjectId** | **String**| Strict-auth project scope | [optional] |
| **xBeaterEnvironmentId** | **String**| Strict-auth environment scope | [optional] |

### Return type

ApiResponse<[**ReviewAnnotation**](ReviewAnnotation.md)>


### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

### HTTP response details
| Status code | Description | Response headers |
|-------------|-------------|------------------|
| **200** | Submit a review annotation |  -  |
| **400** | Invalid request, scope, or filter |  -  |
| **401** | Missing or invalid credentials |  -  |
| **403** | Credentials lack the required scope |  -  |
| **404** | Resource not found |  -  |

