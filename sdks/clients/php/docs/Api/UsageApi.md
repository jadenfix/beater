# Beater\Client\UsageApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**getUsageSummary()**](UsageApi.md#getUsageSummary) | **GET** /v1/usage/{tenant_id}/{project_id} |  |


## `getUsageSummary()`

```php
getUsageSummary($tenant_id, $project_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\UsageSummary
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\UsageApi(
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
    $result = $apiInstance->getUsageSummary($tenant_id, $project_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling UsageApi->getUsageSummary: ', $e->getMessage(), PHP_EOL;
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

[**\Beater\Client\Model\UsageSummary**](../Model/UsageSummary.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
