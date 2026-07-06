# OptimizerStrategy

Pluggable optimizer strategies for the recursive self-improvement loop.  Each variant names a concrete prompt/agent optimizer family called for by ARCHITECTURE §20.10 #7.6 (\"named prompt/agent optimizer strategies, gated by held-out statistics\") and REQUIREMENTS R18.6. The names mirror the reflective-proposal direction of §21.3 and the deferred population search of §21.6c.  **Gating invariant — the differentiator vs. un-gated optimizers.** A strategy only *proposes* [`CandidateChange`]s; it never *accepts* one. Every candidate from every strategy MUST flow through the existing held-out **Test** gate plus the `beater-stats` confidence interval already implemented here (`run_deterministic_experiment` / `run_judge_experiment` / `run_agent_experiment` → [`compare_paired_scores`] → [`GateDecision`], §21.3) and the planned §21.4 anti-overfitting guardrail before it can be accepted. Proposal is not acceptance: the strategy emits candidates, the gate decides.

## Enum

* `LLM_REWRITE` (value: `'llm_rewrite'`)

* `FEW_SHOT_BAYESIAN` (value: `'few_shot_bayesian'`)

* `MIPRO` (value: `'mipro'`)

* `EVOLUTIONARY` (value: `'evolutionary'`)

* `GEPA` (value: `'gepa'`)

* `PARAM_SEARCH` (value: `'param_search'`)

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


