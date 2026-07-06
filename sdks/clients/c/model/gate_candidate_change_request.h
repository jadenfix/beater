/*
 * gate_candidate_change_request.h
 *
 * The candidate change being gated.
 */

#ifndef _gate_candidate_change_request_H_
#define _gate_candidate_change_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_candidate_change_request_t gate_candidate_change_request_t;

#include "change_kind.h"
#include "optimizer_strategy.h"



typedef struct gate_candidate_change_request_t {
    char *description; // string
    beater_api_change_kind__e kind; //referenced enum
    beater_api_optimizer_strategy__e proposed_by; //referenced enum
    char *rationale; // string
    char *target; // string

    int _library_owned; // Is the library responsible for freeing this object?
} gate_candidate_change_request_t;

__attribute__((deprecated)) gate_candidate_change_request_t *gate_candidate_change_request_create(
    char *description,
    beater_api_change_kind__e kind,
    beater_api_optimizer_strategy__e proposed_by,
    char *rationale,
    char *target
);

void gate_candidate_change_request_free(gate_candidate_change_request_t *gate_candidate_change_request);

gate_candidate_change_request_t *gate_candidate_change_request_parseFromJSON(cJSON *gate_candidate_change_requestJSON);

cJSON *gate_candidate_change_request_convertToJSON(gate_candidate_change_request_t *gate_candidate_change_request);

#endif /* _gate_candidate_change_request_H_ */

