# Beater\Client\OnlineApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**decideOnlineSampling()**](OnlineApi.md#decideOnlineSampling) | **POST** /v1/online/{tenant_id}/{project_id}/traces/{trace_id}/sampling |  |


## `decideOnlineSampling()`

```php
decideOnlineSampling($tenant_id, $project_id, $trace_id, $online_sampling_policy, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\SamplingDecision
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\OnlineApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$trace_id = 'trace_id_example'; // string | trace_id
$online_sampling_policy = new \Beater\Client\Model\OnlineSamplingPolicy(); // \Beater\Client\Model\OnlineSamplingPolicy
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->decideOnlineSampling($tenant_id, $project_id, $trace_id, $online_sampling_policy, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling OnlineApi->decideOnlineSampling: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **trace_id** | **string**| trace_id | |
| **online_sampling_policy** | [**\Beater\Client\Model\OnlineSamplingPolicy**](../Model/OnlineSamplingPolicy.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\SamplingDecision**](../Model/SamplingDecision.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
