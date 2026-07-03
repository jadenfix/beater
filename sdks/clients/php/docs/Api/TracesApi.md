# Beater\Client\TracesApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**getTrace()**](TracesApi.md#getTrace) | **GET** /v1/traces/{tenant_id}/{trace_id} |  |
| [**listTraces()**](TracesApi.md#listTraces) | **GET** /v1/traces/{tenant_id} |  |


## `getTrace()`

```php
getTrace($tenant_id, $trace_id, $unmask, $reason, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\TraceView
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\TracesApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$trace_id = 'trace_id_example'; // string | trace_id
$unmask = True; // bool
$reason = 'reason_example'; // string
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->getTrace($tenant_id, $trace_id, $unmask, $reason, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling TracesApi->getTrace: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **trace_id** | **string**| trace_id | |
| **unmask** | **bool**|  | [optional] |
| **reason** | **string**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\TraceView**](../Model/TraceView.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `listTraces()`

```php
listTraces($tenant_id, $project_id, $environment_id, $trace_id, $kind, $status, $started_after, $started_before, $model, $release, $min_cost_micros, $max_cost_micros, $min_latency_ms, $max_latency_ms, $limit, $cursor, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\PageRunSummary
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\TracesApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string
$environment_id = 'environment_id_example'; // string
$trace_id = 'trace_id_example'; // string
$kind = 'kind_example'; // string
$status = 'status_example'; // string
$started_after = 'started_after_example'; // string
$started_before = 'started_before_example'; // string
$model = 'model_example'; // string
$release = 'release_example'; // string
$min_cost_micros = 56; // int
$max_cost_micros = 56; // int
$min_latency_ms = 56; // int
$max_latency_ms = 56; // int
$limit = 56; // int
$cursor = 'cursor_example'; // string
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->listTraces($tenant_id, $project_id, $environment_id, $trace_id, $kind, $status, $started_after, $started_before, $model, $release, $min_cost_micros, $max_cost_micros, $min_latency_ms, $max_latency_ms, $limit, $cursor, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling TracesApi->listTraces: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**|  | [optional] |
| **environment_id** | **string**|  | [optional] |
| **trace_id** | **string**|  | [optional] |
| **kind** | **string**|  | [optional] |
| **status** | **string**|  | [optional] |
| **started_after** | **string**|  | [optional] |
| **started_before** | **string**|  | [optional] |
| **model** | **string**|  | [optional] |
| **release** | **string**|  | [optional] |
| **min_cost_micros** | **int**|  | [optional] |
| **max_cost_micros** | **int**|  | [optional] |
| **min_latency_ms** | **int**|  | [optional] |
| **max_latency_ms** | **int**|  | [optional] |
| **limit** | **int**|  | [optional] |
| **cursor** | **string**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\PageRunSummary**](../Model/PageRunSummary.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
