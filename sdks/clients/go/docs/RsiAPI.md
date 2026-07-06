# \RsiAPI

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**GateOptimizationCandidate**](RsiAPI.md#GateOptimizationCandidate) | **Post** /v1/rsi/{tenant_id}/{project_id}/gate-candidate |



## GateOptimizationCandidate

> GateCandidateResponse GateOptimizationCandidate(ctx, tenantId, projectId).GateCandidateRequest(gateCandidateRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()



### Example

```go
package main

import (
	"context"
	"fmt"
	"os"
	openapiclient "github.com/GIT_USER_ID/GIT_REPO_ID/beaterclient"
)

func main() {
	tenantId := "tenantId_example" // string | tenant_id
	projectId := "projectId_example" // string | project_id
	gateCandidateRequest := *openapiclient.NewGateCandidateRequest(*openapiclient.NewGateCandidateChangeRequest("Description_example", openapiclient.ChangeKind("system_prompt"), openapiclient.OptimizerStrategy("llm_rewrite"), "Rationale_example", "Target_example"), []openapiclient.GateCaseScoreRequest{*openapiclient.NewGateCaseScoreRequest(float64(123), float64(123), openapiclient.Split("train"))}) // GateCandidateRequest |
	authorization := "authorization_example" // string | Bearer API token for strict auth (optional)
	xBeaterApiKey := "xBeaterApiKey_example" // string | API key alternative for strict auth (optional)
	xBeaterProjectId := "xBeaterProjectId_example" // string | Strict-auth project scope (optional)
	xBeaterEnvironmentId := "xBeaterEnvironmentId_example" // string | Strict-auth environment scope (optional)

	configuration := openapiclient.NewConfiguration()
	apiClient := openapiclient.NewAPIClient(configuration)
	resp, r, err := apiClient.RsiAPI.GateOptimizationCandidate(context.Background(), tenantId, projectId).GateCandidateRequest(gateCandidateRequest).Authorization(authorization).XBeaterApiKey(xBeaterApiKey).XBeaterProjectId(xBeaterProjectId).XBeaterEnvironmentId(xBeaterEnvironmentId).Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error when calling `RsiAPI.GateOptimizationCandidate``: %v\n", err)
		fmt.Fprintf(os.Stderr, "Full HTTP response: %v\n", r)
	}
	// response from `GateOptimizationCandidate`: GateCandidateResponse
	fmt.Fprintf(os.Stdout, "Response from `RsiAPI.GateOptimizationCandidate`: %v\n", resp)
}
```

### Path Parameters


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
**ctx** | **context.Context** | context for authentication, logging, cancellation, deadlines, tracing, etc.
**tenantId** | **string** | tenant_id |
**projectId** | **string** | project_id |

### Other Parameters

Other parameters are passed through a pointer to a apiGateOptimizationCandidateRequest struct via the builder pattern


Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------


 **gateCandidateRequest** | [**GateCandidateRequest**](GateCandidateRequest.md) |  |
 **authorization** | **string** | Bearer API token for strict auth |
 **xBeaterApiKey** | **string** | API key alternative for strict auth |
 **xBeaterProjectId** | **string** | Strict-auth project scope |
 **xBeaterEnvironmentId** | **string** | Strict-auth environment scope |

### Return type

[**GateCandidateResponse**](GateCandidateResponse.md)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: application/json
- **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints)
[[Back to Model list]](../README.md#documentation-for-models)
[[Back to README]](../README.md)
