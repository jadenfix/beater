# Beater\Client\SearchApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**searchSpans()**](SearchApi.md#searchSpans) | **GET** /v1/search/{tenant_id}/spans |  |


## `searchSpans()`

```php
searchSpans($tenant_id, $q, $project_id, $environment_id, $trace_id, $span_id, $kind, $status, $model, $tool, $limit, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\SearchResponse
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\SearchApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$q = 'q_example'; // string
$project_id = 'project_id_example'; // string
$environment_id = 'environment_id_example'; // string
$trace_id = 'trace_id_example'; // string
$span_id = 'span_id_example'; // string
$kind = 'kind_example'; // string
$status = 'status_example'; // string
$model = 'model_example'; // string
$tool = 'tool_example'; // string
$limit = 56; // int
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->searchSpans($tenant_id, $q, $project_id, $environment_id, $trace_id, $span_id, $kind, $status, $model, $tool, $limit, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling SearchApi->searchSpans: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **q** | **string**|  | [optional] |
| **project_id** | **string**|  | [optional] |
| **environment_id** | **string**|  | [optional] |
| **trace_id** | **string**|  | [optional] |
| **span_id** | **string**|  | [optional] |
| **kind** | **string**|  | [optional] |
| **status** | **string**|  | [optional] |
| **model** | **string**|  | [optional] |
| **tool** | **string**|  | [optional] |
| **limit** | **int**|  | [optional] |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\SearchResponse**](../Model/SearchResponse.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
