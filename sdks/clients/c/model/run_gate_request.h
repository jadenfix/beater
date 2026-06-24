/*
 * run_gate_request.h
 *
 * 
 */

#ifndef _run_gate_request_H_
#define _run_gate_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct run_gate_request_t run_gate_request_t;




typedef struct run_gate_request_t {
    char *experiment_run_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} run_gate_request_t;

__attribute__((deprecated)) run_gate_request_t *run_gate_request_create(
    char *experiment_run_id
);

void run_gate_request_free(run_gate_request_t *run_gate_request);

run_gate_request_t *run_gate_request_parseFromJSON(cJSON *run_gate_requestJSON);

cJSON *run_gate_request_convertToJSON(run_gate_request_t *run_gate_request);

#endif /* _run_gate_request_H_ */

