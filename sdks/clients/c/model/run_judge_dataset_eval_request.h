/*
 * run_judge_dataset_eval_request.h
 *
 * 
 */

#ifndef _run_judge_dataset_eval_request_H_
#define _run_judge_dataset_eval_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct run_judge_dataset_eval_request_t run_judge_dataset_eval_request_t;

#include "evaluator_kind.h"



typedef struct run_judge_dataset_eval_request_t {
    char *agent_release_id; // string
    char *code_hash; // string
    char *evaluator_id; // string
    char *evaluator_version_id; // string
    struct evaluator_kind_t *kind; //model
    char *prompt_version_id; // string
    char *provider_secret_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} run_judge_dataset_eval_request_t;

__attribute__((deprecated)) run_judge_dataset_eval_request_t *run_judge_dataset_eval_request_create(
    char *agent_release_id,
    char *code_hash,
    char *evaluator_id,
    char *evaluator_version_id,
    evaluator_kind_t *kind,
    char *prompt_version_id,
    char *provider_secret_id
);

void run_judge_dataset_eval_request_free(run_judge_dataset_eval_request_t *run_judge_dataset_eval_request);

run_judge_dataset_eval_request_t *run_judge_dataset_eval_request_parseFromJSON(cJSON *run_judge_dataset_eval_requestJSON);

cJSON *run_judge_dataset_eval_request_convertToJSON(run_judge_dataset_eval_request_t *run_judge_dataset_eval_request);

#endif /* _run_judge_dataset_eval_request_H_ */

