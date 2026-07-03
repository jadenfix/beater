# Beater\Client\SpansApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**getSpan()**](SpansApi.md#getSpan) | **GET** /v1/spans/{tenant_id}/{trace_id}/{span_id} |  |
| [**getSpanIo()**](SpansApi.md#getSpanIo) | **GET** /v1/spans/{tenant_id}/{trace_id}/{span_id}/io |  |


## `getSpan()`

```php
getSpan($tenant_id, $trace_id, $span_id, $unmask, $reason, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\CanonicalSpan
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\SpansApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$trace_id = 'trace_id_example'; // string | trace_id
$span_id = 'span_id_example'; // string | span_id
$unmask = True; // bool
$reason = 'reason_example'; // string
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->getSpan($tenant_id, $trace_id, $span_id, $unmask, $reason, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling SpansApi->getSpan: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **trace_id** | **string**| trace_id | |
| **span_id** | **string**| span_id | |
| **unmask** | **bool**|  | [optional] |
| **reason** | **string**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\CanonicalSpan**](../Model/CanonicalSpan.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `getSpanIo()`

```php
getSpanIo($tenant_id, $trace_id, $span_id, $unmask, $reason, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\SpanIoResponse
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\SpansApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$trace_id = 'trace_id_example'; // string | trace_id
$span_id = 'span_id_example'; // string | span_id
$unmask = True; // bool
$reason = 'reason_example'; // string
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->getSpanIo($tenant_id, $trace_id, $span_id, $unmask, $reason, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling SpansApi->getSpanIo: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **trace_id** | **string**| trace_id | |
| **span_id** | **string**| span_id | |
| **unmask** | **bool**|  | [optional] |
| **reason** | **string**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\SpanIoResponse**](../Model/SpanIoResponse.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
