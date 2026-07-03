# Beater\Client\ReviewsApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**createReviewQueue()**](ReviewsApi.md#createReviewQueue) | **POST** /v1/review-queues/{tenant_id}/{project_id} |  |
| [**enqueueReviewTaskFromTrace()**](ReviewsApi.md#enqueueReviewTaskFromTrace) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/from-trace |  |
| [**listReviewTasks()**](ReviewsApi.md#listReviewTasks) | **GET** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks |  |
| [**promoteReviewAnnotation()**](ReviewsApi.md#promoteReviewAnnotation) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations/{annotation_id}/promote |  |
| [**submitReviewAnnotation()**](ReviewsApi.md#submitReviewAnnotation) | **POST** /v1/review-queues/{tenant_id}/{project_id}/{queue_id}/tasks/{task_id}/annotations |  |


## `createReviewQueue()`

```php
createReviewQueue($tenant_id, $project_id, $create_review_queue_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\ReviewQueue
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ReviewsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$create_review_queue_http_request = new \Beater\Client\Model\CreateReviewQueueHttpRequest(); // \Beater\Client\Model\CreateReviewQueueHttpRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->createReviewQueue($tenant_id, $project_id, $create_review_queue_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ReviewsApi->createReviewQueue: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **create_review_queue_http_request** | [**\Beater\Client\Model\CreateReviewQueueHttpRequest**](../Model/CreateReviewQueueHttpRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\ReviewQueue**](../Model/ReviewQueue.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `enqueueReviewTaskFromTrace()`

```php
enqueueReviewTaskFromTrace($tenant_id, $project_id, $queue_id, $enqueue_review_task_from_trace_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\ReviewTask
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ReviewsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$queue_id = 'queue_id_example'; // string | queue_id
$enqueue_review_task_from_trace_http_request = new \Beater\Client\Model\EnqueueReviewTaskFromTraceHttpRequest(); // \Beater\Client\Model\EnqueueReviewTaskFromTraceHttpRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->enqueueReviewTaskFromTrace($tenant_id, $project_id, $queue_id, $enqueue_review_task_from_trace_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ReviewsApi->enqueueReviewTaskFromTrace: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **queue_id** | **string**| queue_id | |
| **enqueue_review_task_from_trace_http_request** | [**\Beater\Client\Model\EnqueueReviewTaskFromTraceHttpRequest**](../Model/EnqueueReviewTaskFromTraceHttpRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\ReviewTask**](../Model/ReviewTask.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `listReviewTasks()`

```php
listReviewTasks($tenant_id, $project_id, $queue_id, $state, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\ReviewTask[]
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ReviewsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$queue_id = 'queue_id_example'; // string | queue_id
$state = new \Beater\Client\Model\\Beater\Client\Model\ReviewTaskState(); // \Beater\Client\Model\ReviewTaskState
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->listReviewTasks($tenant_id, $project_id, $queue_id, $state, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ReviewsApi->listReviewTasks: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **queue_id** | **string**| queue_id | |
| **state** | [**\Beater\Client\Model\ReviewTaskState**](../Model/.md)|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\ReviewTask[]**](../Model/ReviewTask.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `promoteReviewAnnotation()`

```php
promoteReviewAnnotation($tenant_id, $project_id, $queue_id, $task_id, $annotation_id, $promote_review_annotation_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\DatasetCase
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ReviewsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$queue_id = 'queue_id_example'; // string | queue_id
$task_id = 'task_id_example'; // string | task_id
$annotation_id = 'annotation_id_example'; // string | annotation_id
$promote_review_annotation_http_request = new \Beater\Client\Model\PromoteReviewAnnotationHttpRequest(); // \Beater\Client\Model\PromoteReviewAnnotationHttpRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->promoteReviewAnnotation($tenant_id, $project_id, $queue_id, $task_id, $annotation_id, $promote_review_annotation_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ReviewsApi->promoteReviewAnnotation: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **queue_id** | **string**| queue_id | |
| **task_id** | **string**| task_id | |
| **annotation_id** | **string**| annotation_id | |
| **promote_review_annotation_http_request** | [**\Beater\Client\Model\PromoteReviewAnnotationHttpRequest**](../Model/PromoteReviewAnnotationHttpRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\DatasetCase**](../Model/DatasetCase.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `submitReviewAnnotation()`

```php
submitReviewAnnotation($tenant_id, $project_id, $queue_id, $task_id, $submit_review_annotation_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\ReviewAnnotation
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ReviewsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$queue_id = 'queue_id_example'; // string | queue_id
$task_id = 'task_id_example'; // string | task_id
$submit_review_annotation_http_request = new \Beater\Client\Model\SubmitReviewAnnotationHttpRequest(); // \Beater\Client\Model\SubmitReviewAnnotationHttpRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->submitReviewAnnotation($tenant_id, $project_id, $queue_id, $task_id, $submit_review_annotation_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ReviewsApi->submitReviewAnnotation: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **queue_id** | **string**| queue_id | |
| **task_id** | **string**| task_id | |
| **submit_review_annotation_http_request** | [**\Beater\Client\Model\SubmitReviewAnnotationHttpRequest**](../Model/SubmitReviewAnnotationHttpRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\ReviewAnnotation**](../Model/ReviewAnnotation.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
