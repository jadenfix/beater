/*
 * gate_candidate_request.h
 *
 * Request to gate a single optimization candidate (&#x60;gateOptimizationCandidate&#x60;).  The caller supplies the candidate it proposed and the per-case baseline-vs-candidate scores it observed, each tagged with its split. The server runs the held-out **Test** gate plus the anti-overfitting guardrail and returns the accept/reject verdict — the proposer never decides acceptance.
 */

#ifndef _gate_candidate_request_H_
#define _gate_candidate_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_candidate_request_t gate_candidate_request_t;

#include "gate_candidate_change_request.h"
#include "gate_case_score_request.h"
#include "gate_policy.h"



typedef struct gate_candidate_request_t {
    struct gate_candidate_change_request_t *candidate; //model
    struct gate_policy_t *gate_policy; //model
    double overfit_confidence; //numeric
    int overfit_resamples; //numeric
    long overfit_seed; //numeric
    double overfit_tolerance; //numeric
    list_t *scores; //nonprimitive container

    int _library_owned; // Is the library responsible for freeing this object?
} gate_candidate_request_t;

__attribute__((deprecated)) gate_candidate_request_t *gate_candidate_request_create(
    gate_candidate_change_request_t *candidate,
    gate_policy_t *gate_policy,
    double overfit_confidence,
    int overfit_resamples,
    long overfit_seed,
    double overfit_tolerance,
    list_t *scores
);

void gate_candidate_request_free(gate_candidate_request_t *gate_candidate_request);

gate_candidate_request_t *gate_candidate_request_parseFromJSON(cJSON *gate_candidate_requestJSON);

cJSON *gate_candidate_request_convertToJSON(gate_candidate_request_t *gate_candidate_request);

#endif /* _gate_candidate_request_H_ */

