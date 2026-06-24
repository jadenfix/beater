/*
 * dataset_case.h
 *
 * 
 */

#ifndef _dataset_case_H_
#define _dataset_case_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct dataset_case_t dataset_case_t;

#include "any_type.h"



typedef struct dataset_case_t {
    char *case_id; // string
    char *created_at; //date time
    char *dataset_id; // string
    any_type_t *input; // custom
    list_t *input_artifact_hashes; //primitive container
    char *normalizer_version; // string
    any_type_t *output; // custom
    char *project_id; // string
    any_type_t *reference; // custom
    char *source_environment_id; // string
    char *source_span_id; // string
    char *source_trace_id; // string
    char *tenant_id; // string
    any_type_t *trace; // custom
    int trace_schema_version; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} dataset_case_t;

__attribute__((deprecated)) dataset_case_t *dataset_case_create(
    char *case_id,
    char *created_at,
    char *dataset_id,
    any_type_t *input,
    list_t *input_artifact_hashes,
    char *normalizer_version,
    any_type_t *output,
    char *project_id,
    any_type_t *reference,
    char *source_environment_id,
    char *source_span_id,
    char *source_trace_id,
    char *tenant_id,
    any_type_t *trace,
    int trace_schema_version
);

void dataset_case_free(dataset_case_t *dataset_case);

dataset_case_t *dataset_case_parseFromJSON(cJSON *dataset_caseJSON);

cJSON *dataset_case_convertToJSON(dataset_case_t *dataset_case);

#endif /* _dataset_case_H_ */

