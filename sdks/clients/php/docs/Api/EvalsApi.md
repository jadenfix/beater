# Beater\Client\EvalsApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**runDeterministicEval()**](EvalsApi.md#runDeterministicEval) | **POST** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/evals/deterministic |  |
| [**runJudgeEval()**](EvalsApi.md#runJudgeEval) | **POST** /v1/datasets/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/evals/judge |  |


## `runDeterministicEval()`

```php
runDeterministicEval($tenant_id, $project_id, $dataset_id, $version_id, $run_deterministic_eval_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\DatasetEvalReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\EvalsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$dataset_id = 'dataset_id_example'; // string | dataset_id
$version_id = 'version_id_example'; // string | version_id
$run_deterministic_eval_request = new \Beater\Client\Model\RunDeterministicEvalRequest(); // \Beater\Client\Model\RunDeterministicEvalRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->runDeterministicEval($tenant_id, $project_id, $dataset_id, $version_id, $run_deterministic_eval_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling EvalsApi->runDeterministicEval: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **dataset_id** | **string**| dataset_id | |
| **version_id** | **string**| version_id | |
| **run_deterministic_eval_request** | [**\Beater\Client\Model\RunDeterministicEvalRequest**](../Model/RunDeterministicEvalRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\DatasetEvalReport**](../Model/DatasetEvalReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `runJudgeEval()`

```php
runJudgeEval($tenant_id, $project_id, $dataset_id, $version_id, $run_judge_dataset_eval_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\DatasetEvalReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\EvalsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$dataset_id = 'dataset_id_example'; // string | dataset_id
$version_id = 'version_id_example'; // string | version_id
$run_judge_dataset_eval_request = new \Beater\Client\Model\RunJudgeDatasetEvalRequest(); // \Beater\Client\Model\RunJudgeDatasetEvalRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->runJudgeEval($tenant_id, $project_id, $dataset_id, $version_id, $run_judge_dataset_eval_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling EvalsApi->runJudgeEval: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **dataset_id** | **string**| dataset_id | |
| **version_id** | **string**| version_id | |
| **run_judge_dataset_eval_request** | [**\Beater\Client\Model\RunJudgeDatasetEvalRequest**](../Model/RunJudgeDatasetEvalRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\DatasetEvalReport**](../Model/DatasetEvalReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
