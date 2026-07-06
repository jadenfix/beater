/*
 * gate_comparison_response.h
 *
 * The held-out Test-split gate comparison.
 */

#ifndef _gate_comparison_response_H_
#define _gate_comparison_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_comparison_response_t gate_comparison_response_t;

#include "gate_decision.h"



typedef struct gate_comparison_response_t {
    double baseline_mean; //numeric
    double candidate_mean; //numeric
    double ci_high; //numeric
    double ci_low; //numeric
    beater_api_gate_decision__e decision; //referenced enum
    double delta; //numeric
    double p_value; //numeric
    int sample_size; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} gate_comparison_response_t;

__attribute__((deprecated)) gate_comparison_response_t *gate_comparison_response_create(
    double baseline_mean,
    double candidate_mean,
    double ci_high,
    double ci_low,
    beater_api_gate_decision__e decision,
    double delta,
    double p_value,
    int sample_size
);

void gate_comparison_response_free(gate_comparison_response_t *gate_comparison_response);

gate_comparison_response_t *gate_comparison_response_parseFromJSON(cJSON *gate_comparison_responseJSON);

cJSON *gate_comparison_response_convertToJSON(gate_comparison_response_t *gate_comparison_response);

#endif /* _gate_comparison_response_H_ */

