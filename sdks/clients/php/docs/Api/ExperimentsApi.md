# Beater\Client\ExperimentsApi

All URIs are relative to http://localhost, except if the operation defines another base path.

| Method | HTTP request | Description |
| ------------- | ------------- | ------------- |
| [**runDeterministicExperiment()**](ExperimentsApi.md#runDeterministicExperiment) | **POST** /v1/experiments/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/deterministic |  |
| [**runJudgeExperiment()**](ExperimentsApi.md#runJudgeExperiment) | **POST** /v1/experiments/{tenant_id}/{project_id}/{dataset_id}/versions/{version_id}/judge |  |


## `runDeterministicExperiment()`

```php
runDeterministicExperiment($tenant_id, $project_id, $dataset_id, $version_id, $run_experiment_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\ExperimentRunReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ExperimentsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$dataset_id = 'dataset_id_example'; // string | dataset_id
$version_id = 'version_id_example'; // string | version_id
$run_experiment_request = new \Beater\Client\Model\RunExperimentRequest(); // \Beater\Client\Model\RunExperimentRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->runDeterministicExperiment($tenant_id, $project_id, $dataset_id, $version_id, $run_experiment_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ExperimentsApi->runDeterministicExperiment: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **dataset_id** | **string**| dataset_id | |
| **version_id** | **string**| version_id | |
| **run_experiment_request** | [**\Beater\Client\Model\RunExperimentRequest**](../Model/RunExperimentRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\ExperimentRunReport**](../Model/ExperimentRunReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)

## `runJudgeExperiment()`

```php
runJudgeExperiment($tenant_id, $project_id, $dataset_id, $version_id, $run_judge_experiment_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id): \Beater\Client\Model\ExperimentRunReport
```



### Example

```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');



$apiInstance = new Beater\Client\Api\ExperimentsApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$tenant_id = 'tenant_id_example'; // string | tenant_id
$project_id = 'project_id_example'; // string | project_id
$dataset_id = 'dataset_id_example'; // string | dataset_id
$version_id = 'version_id_example'; // string | version_id
$run_judge_experiment_request = new \Beater\Client\Model\RunJudgeExperimentRequest(); // \Beater\Client\Model\RunJudgeExperimentRequest
$authorization = 'authorization_example'; // string | Bearer API token for strict auth
$x_beater_api_key = 'x_beater_api_key_example'; // string | API key alternative for strict auth
$x_beater_project_id = 'x_beater_project_id_example'; // string | Strict-auth project scope
$x_beater_environment_id = 'x_beater_environment_id_example'; // string | Strict-auth environment scope

try {
    $result = $apiInstance->runJudgeExperiment($tenant_id, $project_id, $dataset_id, $version_id, $run_judge_experiment_request, $authorization, $x_beater_api_key, $x_beater_project_id, $x_beater_environment_id);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling ExperimentsApi->runJudgeExperiment: ', $e->getMessage(), PHP_EOL;
}
```

### Parameters

| Name | Type | Description  | Notes |
| ------------- | ------------- | ------------- | ------------- |
| **tenant_id** | **string**| tenant_id | |
| **project_id** | **string**| project_id | |
| **dataset_id** | **string**| dataset_id | |
| **version_id** | **string**| version_id | |
| **run_judge_experiment_request** | [**\Beater\Client\Model\RunJudgeExperimentRequest**](../Model/RunJudgeExperimentRequest.md)|  | |
| **authorization** | **string**| Bearer API token for strict auth | [optional] |
| **x_beater_api_key** | **string**| API key alternative for strict auth | [optional] |
| **x_beater_project_id** | **string**| Strict-auth project scope | [optional] |
| **x_beater_environment_id** | **string**| Strict-auth environment scope | [optional] |

### Return type

[**\Beater\Client\Model\ExperimentRunReport**](../Model/ExperimentRunReport.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: `application/json`
- **Accept**: `application/json`

[[Back to top]](#) [[Back to API list]](../../README.md#endpoints)
[[Back to Model list]](../../README.md#models)
[[Back to README]](../../README.md)
