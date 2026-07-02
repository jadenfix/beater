

# GateCandidateRequest

Request to gate a single optimization candidate (`gateOptimizationCandidate`).  The caller supplies the candidate it proposed and the per-case baseline-vs-candidate scores it observed, each tagged with its split. The server runs the held-out **Test** gate plus the anti-overfitting guardrail and returns the accept/reject verdict — the proposer never decides acceptance.

## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**candidate** | [**GateCandidateChangeRequest**](GateCandidateChangeRequest.md) | The proposed change under evaluation (provenance for the audit trail). |  |
|**gatePolicy** | [**GatePolicy**](GatePolicy.md) | Held-out Test gate policy. Defaults to the standard &#x60;GatePolicy&#x60;. |  [optional] |
|**overfitConfidence** | **Double** | Bootstrap confidence for the generalization-gap CI (default &#x60;0.95&#x60;). |  [optional] |
|**overfitResamples** | **Integer** | Bootstrap resamples for the generalization-gap CI (default &#x60;2000&#x60;). |  [optional] |
|**overfitSeed** | **Long** | Seed for the deterministic generalization-gap bootstrap (default &#x60;1&#x60;). |  [optional] |
|**overfitTolerance** | **Double** | Largest benign generalization gap (default &#x60;0.0&#x60;). |  [optional] |
|**scores** | [**List&lt;GateCaseScoreRequest&gt;**](GateCaseScoreRequest.md) | Per-case paired scores. Must include at least one &#x60;test&#x60; case and at least one &#x60;train&#x60;/&#x60;val&#x60; case so both the gate and the gap check are defined. |  |



