/*
 * create_gate_request.h
 *
 * 
 */

#ifndef _create_gate_request_H_
#define _create_gate_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_gate_request_t create_gate_request_t;

#include "inconclusive_policy.h"



typedef struct create_gate_request_t {
    char *dataset_id; // string
    char *evaluator_version_id; // string
    char *gate_id; // string
    beater_api_inconclusive_policy__e inconclusive_policy; //referenced enum
    char *name; // string

    int _library_owned; // Is the library responsible for freeing this object?
} create_gate_request_t;

__attribute__((deprecated)) create_gate_request_t *create_gate_request_create(
    char *dataset_id,
    char *evaluator_version_id,
    char *gate_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    char *name
);

void create_gate_request_free(create_gate_request_t *create_gate_request);

create_gate_request_t *create_gate_request_parseFromJSON(cJSON *create_gate_requestJSON);

cJSON *create_gate_request_convertToJSON(create_gate_request_t *create_gate_request);

#endif /* _create_gate_request_H_ */

