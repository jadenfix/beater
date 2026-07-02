

# GateCandidateResponse

Verdict for `gateOptimizationCandidate`: the held-out Test comparison, the generalization-gap assessment, and the combined acceptance decision.

## Properties

| Name | Type | Description | Notes |
|------------ | ------------- | ------------- | -------------|
|**accepted** | **Boolean** | &#x60;true&#x60; iff the held-out Test gate &#x60;Pass&#x60;ed AND no significant generalization gap was flagged. This is the only path to acceptance. |  |
|**gate** | [**GateComparisonResponse**](GateComparisonResponse.md) | The held-out **Test**-split comparison (paired test + CI vs. the regression bound). |  |
|**overfit** | [**OverfitResponse**](OverfitResponse.md) | The generalization-gap assessment (optimization-split lift vs. held-out lift). |  |



