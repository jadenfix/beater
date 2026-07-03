# # ConnectorTool

## Properties

Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**description** | **string** | What the tool does. | [optional]
**input_schema** | **object** | JSON Schema of the tool&#39;s &#x60;arguments&#x60;, verbatim from Composio. The agent loop uses this to construct valid calls; [&#x60;crate::skill&#x60;] renders it. | [optional]
**name** | **string** | Human display name. |
**no_auth** | **bool** | &#x60;true&#x60; when the tool executes without a connected account. | [optional]
**slug** | **string** | Tool slug passed to [&#x60;ComposioClient::execute&#x60;] (e.g. &#x60;GITHUB_CREATE_AN_ISSUE&#x60;). |
**tags** | **string[]** | Free-form tags Composio assigns (categories, importance, …). | [optional]
**toolkit** | **string** | Owning toolkit slug (e.g. &#x60;github&#x60;), when known. | [optional]

[[Back to Model list]](../../README.md#models) [[Back to API list]](../../README.md#endpoints) [[Back to README]](../../README.md)
