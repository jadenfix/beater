# Beater\Client\IngestApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**drainTraceIngested()**](IngestApi.md#drainTraceIngested) | **POST** /v1/ingest/{tenant_id}/{project_id}/trace-ingested/drain |  |
| [**drainTraceWrites()**](IngestApi.md#drainTraceWrites) | **POST** /v1/ingest/{tenant_id}/{project_id}/trace-writes/drain |  |
| [**getIngestQueueStatus()**](IngestApi.md#getIngestQueueStatus) | **GET** /v1/ingest/{tenant_id}/{project_id}/queue |  |
| [**importSource()**](IngestApi.md#importSource) | **POST** /v1/import/{tenant_id}/{project_id}/{environment_id} |  |
| [**ingestNative()**](IngestApi.md#ingestNative) | **POST** /v1/traces/native |  |
| [**ingestOtlp()**](IngestApi.md#ingestOtlp) | **POST** /v1/otlp/{tenant_id}/{project_id}/{environment_id}/v1/traces |  |
| [**reconcileTrace()**](IngestApi.md#reconcileTrace) | **POST** /v1/ingest/{tenant_id}/{project_id}/traces/{trace_id}/reconcile |  |
| [**replayDeadLetter()**](IngestApi.md#replayDeadLetter) | **POST** /v1/ingest/{tenant_id}/{project_id}/dead-letters/{message_id}/replay |  |


## `drainTraceIngested()`

```php
drainTraceIngested($tenant_id, $project_id, $limit, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\TraceIngestedDrainReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$limit = 56; // int
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->drainTraceIngested($tenant_id, $project_id, $limit, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->drainTraceIngested: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **limit** | **int**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\TraceIngestedDrainReport**](../Model/TraceIngestedDrainReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `drainTraceWrites()`

```php
drainTraceWrites($tenant_id, $project_id, $limit, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\TraceWriteDrainReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$limit = 56; // int
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->drainTraceWrites($tenant_id, $project_id, $limit, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->drainTraceWrites: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **limit** | **int**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\TraceWriteDrainReport**](../Model/TraceWriteDrainReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `getIngestQueueStatus()`

```php
getIngestQueueStatus($tenant_id, $project_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\IngestQueueStatus
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->getIngestQueueStatus($tenant_id, $project_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->getIngestQueueStatus: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\IngestQueueStatus**](../Model/IngestQueueStatus.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `importSource()`

```php
importSource($tenant_id, $project_id, $environment_id, $import_source_http_request, $durability, $authorization, $x_beater_api_key): \Beater\Client\Model\IngestOutcome
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$environment_id = 'environment_id_example'; // string | environment_id
$import_source_http_request = new \Beater\Client\Model\ImportSourceHttpRequest(); // \Beater\Client\Model\ImportSourceHttpRequest
$durability = 'durability_example'; // string
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth

try {
    $result = $apiInstance->importSource($tenant_id, $project_id, $environment_id, $import_source_http_request, $durability, $authorization, $x_beater_api_key);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->importSource: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **environment_id** | **string**| environment_id | |
| **import_source_http_request** | [**\Beater\Client\Model\ImportSourceHttpRequest**](../Model/ImportSourceHttpRequest.md)|  | |
| **durability** | **string**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |

### Return type

[**\Beater\Client\Model\IngestOutcome**](../Model/IngestOutcome.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `ingestNative()`

```php
ingestNative($native_ingest_request, $durability, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\IngestOutcome
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$native_ingest_request = new \Beater\Client\Model\NativeIngestRequest(); // \Beater\Client\Model\NativeIngestRequest
$durability = 'durability_example'; // string
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->ingestNative($native_ingest_request, $durability, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->ingestNative: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **native_ingest_request** | [**\Beater\Client\Model\NativeIngestRequest**](../Model/NativeIngestRequest.md)|  | |
| **durability** | **string**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\IngestOutcome**](../Model/IngestOutcome.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `ingestOtlp()`

```php
ingestOtlp($tenant_id, $project_id, $environment_id, $durability, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\OtlpIngestOutcome
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$environment_id = 'environment_id_example'; // string | environment_id
$durability = 'durability_example'; // string
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->ingestOtlp($tenant_id, $project_id, $environment_id, $durability, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->ingestOtlp: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **environment_id** | **string**| environment_id | |
| **durability** | **string**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\OtlpIngestOutcome**](../Model/OtlpIngestOutcome.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `reconcileTrace()`

```php
reconcileTrace($tenant_id, $project_id, $trace_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\TraceIngestedReconcileReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$trace_id = 'trace_id_example'; // string | trace_id
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->reconcileTrace($tenant_id, $project_id, $trace_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->reconcileTrace: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **trace_id** | **string**| trace_id | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\TraceIngestedReconcileReport**](../Model/TraceIngestedReconcileReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `replayDeadLetter()`

```php
replayDeadLetter($tenant_id, $project_id, $message_id, $reset_attempts, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\DeadLetterReplayReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\IngestApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$message_id = 'message_id_example'; // string | message_id
$reset_attempts = True; // bool
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->replayDeadLetter($tenant_id, $project_id, $message_id, $reset_attempts, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling IngestApi->replayDeadLetter: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **message_id** | **string**| message_id | |
| **reset_attempts** | **bool**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\DeadLetterReplayReport**](../Model/DeadLetterReplayReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
