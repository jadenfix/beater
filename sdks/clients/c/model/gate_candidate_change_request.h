/*
 * gate_candidate_change_request.h
 *
 * The candidate change being gated. &#x60;kind&#x60; and &#x60;proposed_by&#x60; are the RSI optimizer&#39;s snake_case enum tags (e.g. &#x60;system_prompt&#x60;, &#x60;llm_rewrite&#x60;).
 */

#ifndef _gate_candidate_change_request_H_
#define _gate_candidate_change_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_candidate_change_request_t gate_candidate_change_request_t;




typedef struct gate_candidate_change_request_t {
    char *description; // string
    char *kind; // string
    char *proposed_by; // string
    char *rationale; // string
    char *target; // string

    int _library_owned; // Is the library responsible for freeing this object?
} gate_candidate_change_request_t;

__attribute__((deprecated)) gate_candidate_change_request_t *gate_candidate_change_request_create(
    char *description,
    char *kind,
    char *proposed_by,
    char *rationale,
    char *target
);

void gate_candidate_change_request_free(gate_candidate_change_request_t *gate_candidate_change_request);

gate_candidate_change_request_t *gate_candidate_change_request_parseFromJSON(cJSON *gate_candidate_change_requestJSON);

cJSON *gate_candidate_change_request_convertToJSON(gate_candidate_change_request_t *gate_candidate_change_request);

#endif /* _gate_candidate_change_request_H_ */

