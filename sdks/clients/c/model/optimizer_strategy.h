/*
 * optimizer_strategy.h
 *
 * Pluggable optimizer strategies for the recursive self-improvement loop.  Each variant names a concrete prompt/agent optimizer family called for by ARCHITECTURE §20.10 #7.6 (\&quot;named prompt/agent optimizer strategies, gated by held-out statistics\&quot;) and REQUIREMENTS R18.6. The names mirror the reflective-proposal direction of §21.3 and the deferred population search of §21.6c.  **Gating invariant — the differentiator vs. un-gated optimizers.** A strategy only *proposes* [&#x60;CandidateChange&#x60;]s; it never *accepts* one. Every candidate from every strategy MUST flow through the existing held-out **Test** gate plus the &#x60;beater-stats&#x60; confidence interval already implemented here (&#x60;run_deterministic_experiment&#x60; / &#x60;run_judge_experiment&#x60; / &#x60;run_agent_experiment&#x60; → [&#x60;compare_paired_scores&#x60;] → [&#x60;GateDecision&#x60;], §21.3) and the planned §21.4 anti-overfitting guardrail before it can be accepted. Proposal is not acceptance: the strategy emits candidates, the gate decides.
 */

#ifndef _optimizer_strategy_H_
#define _optimizer_strategy_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct optimizer_strategy_t optimizer_strategy_t;


// Enum  for optimizer_strategy

typedef enum { beater_api_optimizer_strategy__NULL = 0, beater_api_optimizer_strategy__llm_rewrite, beater_api_optimizer_strategy__few_shot_bayesian, beater_api_optimizer_strategy__mipro, beater_api_optimizer_strategy__evolutionary, beater_api_optimizer_strategy__gepa, beater_api_optimizer_strategy__param_search } beater_api_optimizer_strategy__e;

char* optimizer_strategy_optimizer_strategy_ToString(beater_api_optimizer_strategy__e optimizer_strategy);

beater_api_optimizer_strategy__e optimizer_strategy_optimizer_strategy_FromString(char* optimizer_strategy);

cJSON *optimizer_strategy_convertToJSON(beater_api_optimizer_strategy__e optimizer_strategy);

beater_api_optimizer_strategy__e optimizer_strategy_parseFromJSON(cJSON *optimizer_strategyJSON);

#endif /* _optimizer_strategy_H_ */

