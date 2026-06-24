/*
 * review_task.h
 *
 * 
 */

#ifndef _review_task_H_
#define _review_task_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct review_task_t review_task_t;

#include "review_task_state.h"



typedef struct review_task_t {
    char *created_at; //date time
    char *dataset_case_id; // string
    char *dataset_id; // string
    long priority; //numeric
    char *project_id; // string
    char *queue_id; // string
    char *span_id; // string
    beater_api_review_task_state__e state; //referenced enum
    char *task_id; // string
    char *tenant_id; // string
    char *trace_id; // string
    char *updated_at; //date time

    int _library_owned; // Is the library responsible for freeing this object?
} review_task_t;

__attribute__((deprecated)) review_task_t *review_task_create(
    char *created_at,
    char *dataset_case_id,
    char *dataset_id,
    long priority,
    char *project_id,
    char *queue_id,
    char *span_id,
    beater_api_review_task_state__e state,
    char *task_id,
    char *tenant_id,
    char *trace_id,
    char *updated_at
);

void review_task_free(review_task_t *review_task);

review_task_t *review_task_parseFromJSON(cJSON *review_taskJSON);

cJSON *review_task_convertToJSON(review_task_t *review_task);

#endif /* _review_task_H_ */

