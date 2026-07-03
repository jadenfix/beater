# Beater\Client\ApiKeysApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**createApiKey()**](ApiKeysApi.md#createApiKey) | **POST** /v1/api-keys/{tenant_id}/{project_id}/{environment_id} |  |
| [**revokeApiKey()**](ApiKeysApi.md#revokeApiKey) | **POST** /v1/api-keys/{tenant_id}/{project_id}/{environment_id}/{api_key_id}/revoke |  |


## `createApiKey()`

```php
createApiKey($tenant_id, $project_id, $environment_id, $create_api_key_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\ApiKeyCreatedResponse
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ApiKeysApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$environment_id = 'environment_id_example'; // string | environment_id
$create_api_key_http_request = new \Beater\Client\Model\CreateApiKeyHttpRequest(); // \Beater\Client\Model\CreateApiKeyHttpRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->createApiKey($tenant_id, $project_id, $environment_id, $create_api_key_http_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ApiKeysApi->createApiKey: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **environment_id** | **string**| environment_id | |
| **create_api_key_http_request** | [**\Beater\Client\Model\CreateApiKeyHttpRequest**](../Model/CreateApiKeyHttpRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\ApiKeyCreatedResponse**](../Model/ApiKeyCreatedResponse.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `revokeApiKey()`

```php
revokeApiKey($tenant_id, $project_id, $environment_id, $api_key_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\RevokedApiKey
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ApiKeysApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$environment_id = 'environment_id_example'; // string | environment_id
$api_key_id = 'api_key_id_example'; // string | api_key_id
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->revokeApiKey($tenant_id, $project_id, $environment_id, $api_key_id, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ApiKeysApi->revokeApiKey: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **environment_id** | **string**| environment_id | |
| **api_key_id** | **string**| api_key_id | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\RevokedApiKey**](../Model/RevokedApiKey.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
