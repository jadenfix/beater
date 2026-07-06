/*
 * gate_case_score_request.h
 *
 * One case&#39;s paired baseline-vs-candidate score, tagged with its split.
 */

#ifndef _gate_case_score_request_H_
#define _gate_case_score_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_case_score_request_t gate_case_score_request_t;

#include "split.h"



typedef struct gate_case_score_request_t {
    double baseline_score; //numeric
    double candidate_score; //numeric
    beater_api_split__e split; //referenced enum

    int _library_owned; // Is the library responsible for freeing this object?
} gate_case_score_request_t;

__attribute__((deprecated)) gate_case_score_request_t *gate_case_score_request_create(
    double baseline_score,
    double candidate_score,
    beater_api_split__e split
);

void gate_case_score_request_free(gate_case_score_request_t *gate_case_score_request);

gate_case_score_request_t *gate_case_score_request_parseFromJSON(cJSON *gate_case_score_requestJSON);

cJSON *gate_case_score_request_convertToJSON(gate_case_score_request_t *gate_case_score_request);

#endif /* _gate_case_score_request_H_ */

