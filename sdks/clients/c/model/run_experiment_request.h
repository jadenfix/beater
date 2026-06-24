/*
 * run_experiment_request.h
 *
 * 
 */

#ifndef _run_experiment_request_H_
#define _run_experiment_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct run_experiment_request_t run_experiment_request_t;

#include "case_output_override_request.h"
#include "evaluator_kind.h"
#include "gate_policy.h"



typedef struct run_experiment_request_t {
    list_t *baseline_outputs; //nonprimitive container
    char *baseline_release_id; // string
    list_t *candidate_outputs; //nonprimitive container
    char *candidate_release_id; // string
    char *evaluator_id; // string
    char *evaluator_version_id; // string
    struct gate_policy_t *gate_policy; //model
    struct evaluator_kind_t *kind; //model

    int _library_owned; // Is the library responsible for freeing this object?
} run_experiment_request_t;

__attribute__((deprecated)) run_experiment_request_t *run_experiment_request_create(
    list_t *baseline_outputs,
    char *baseline_release_id,
    list_t *candidate_outputs,
    char *candidate_release_id,
    char *evaluator_id,
    char *evaluator_version_id,
    gate_policy_t *gate_policy,
    evaluator_kind_t *kind
);

void run_experiment_request_free(run_experiment_request_t *run_experiment_request);

run_experiment_request_t *run_experiment_request_parseFromJSON(cJSON *run_experiment_requestJSON);

cJSON *run_experiment_request_convertToJSON(run_experiment_request_t *run_experiment_request);

#endif /* _run_experiment_request_H_ */

