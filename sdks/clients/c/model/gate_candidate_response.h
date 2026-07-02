/*
 * gate_candidate_response.h
 *
 * Verdict for &#x60;gateOptimizationCandidate&#x60;: the held-out Test comparison, the generalization-gap assessment, and the combined acceptance decision.
 */

#ifndef _gate_candidate_response_H_
#define _gate_candidate_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_candidate_response_t gate_candidate_response_t;

#include "gate_comparison_response.h"
#include "overfit_response.h"



typedef struct gate_candidate_response_t {
    int accepted; //boolean
    struct gate_comparison_response_t *gate; //model
    struct overfit_response_t *overfit; //model

    int _library_owned; // Is the library responsible for freeing this object?
} gate_candidate_response_t;

__attribute__((deprecated)) gate_candidate_response_t *gate_candidate_response_create(
    int accepted,
    gate_comparison_response_t *gate,
    overfit_response_t *overfit
);

void gate_candidate_response_free(gate_candidate_response_t *gate_candidate_response);

gate_candidate_response_t *gate_candidate_response_parseFromJSON(cJSON *gate_candidate_responseJSON);

cJSON *gate_candidate_response_convertToJSON(gate_candidate_response_t *gate_candidate_response);

#endif /* _gate_candidate_response_H_ */

