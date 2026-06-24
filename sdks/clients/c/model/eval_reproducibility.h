/*
 * eval_reproducibility.h
 *
 * 
 */

#ifndef _eval_reproducibility_H_
#define _eval_reproducibility_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct eval_reproducibility_t eval_reproducibility_t;

#include "any_type.h"



typedef struct eval_reproducibility_t {
    char *agent_release_id; // string
    char *code_hash; // string
    char *dataset_case_id; // string
    char *dataset_version_id; // string
    char *evaluator_version_id; // string
    list_t *input_artifact_hashes; //primitive container
    char *judge_model_id; // string
    any_type_t *judge_parameters; // custom
    char *judge_provider; // string
    char *judge_rubric_version; // string
    long judge_seed; //numeric
    char *normalizer_version; // string
    char *prompt_version_id; // string
    int trace_schema_version; //numeric
    char *wasi_abi_version; // string
    char *wasm_hash; // string

    int _library_owned; // Is the library responsible for freeing this object?
} eval_reproducibility_t;

__attribute__((deprecated)) eval_reproducibility_t *eval_reproducibility_create(
    char *agent_release_id,
    char *code_hash,
    char *dataset_case_id,
    char *dataset_version_id,
    char *evaluator_version_id,
    list_t *input_artifact_hashes,
    char *judge_model_id,
    any_type_t *judge_parameters,
    char *judge_provider,
    char *judge_rubric_version,
    long judge_seed,
    char *normalizer_version,
    char *prompt_version_id,
    int trace_schema_version,
    char *wasi_abi_version,
    char *wasm_hash
);

void eval_reproducibility_free(eval_reproducibility_t *eval_reproducibility);

eval_reproducibility_t *eval_reproducibility_parseFromJSON(cJSON *eval_reproducibilityJSON);

cJSON *eval_reproducibility_convertToJSON(eval_reproducibility_t *eval_reproducibility);

#endif /* _eval_reproducibility_H_ */

