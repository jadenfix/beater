#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "enqueue_review_task_from_trace_http_request.h"



static enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request_create_internal(
    char *dataset_case_id,
    char *dataset_id,
    long priority,
    char *span_id,
    char *task_id,
    char *trace_id
    ) {
    enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request_local_var = malloc(sizeof(enqueue_review_task_from_trace_http_request_t));
    if (!enqueue_review_task_from_trace_http_request_local_var) {
        return NULL;
    }
    enqueue_review_task_from_trace_http_request_local_var->dataset_case_id = dataset_case_id;
    enqueue_review_task_from_trace_http_request_local_var->dataset_id = dataset_id;
    enqueue_review_task_from_trace_http_request_local_var->priority = priority;
    enqueue_review_task_from_trace_http_request_local_var->span_id = span_id;
    enqueue_review_task_from_trace_http_request_local_var->task_id = task_id;
    enqueue_review_task_from_trace_http_request_local_var->trace_id = trace_id;

    enqueue_review_task_from_trace_http_request_local_var->_library_owned = 1;
    return enqueue_review_task_from_trace_http_request_local_var;
}

__attribute__((deprecated)) enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request_create(
    char *dataset_case_id,
    char *dataset_id,
    long priority,
    char *span_id,
    char *task_id,
    char *trace_id
    ) {
    return enqueue_review_task_from_trace_http_request_create_internal (
        dataset_case_id,
        dataset_id,
        priority,
        span_id,
        task_id,
        trace_id
        );
}

void enqueue_review_task_from_trace_http_request_free(enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request) {
    if(NULL == enqueue_review_task_from_trace_http_request){
        return ;
    }
    if(enqueue_review_task_from_trace_http_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "enqueue_review_task_from_trace_http_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (enqueue_review_task_from_trace_http_request->dataset_case_id) {
        free(enqueue_review_task_from_trace_http_request->dataset_case_id);
        enqueue_review_task_from_trace_http_request->dataset_case_id = NULL;
    }
    if (enqueue_review_task_from_trace_http_request->dataset_id) {
        free(enqueue_review_task_from_trace_http_request->dataset_id);
        enqueue_review_task_from_trace_http_request->dataset_id = NULL;
    }
    if (enqueue_review_task_from_trace_http_request->span_id) {
        free(enqueue_review_task_from_trace_http_request->span_id);
        enqueue_review_task_from_trace_http_request->span_id = NULL;
    }
    if (enqueue_review_task_from_trace_http_request->task_id) {
        free(enqueue_review_task_from_trace_http_request->task_id);
        enqueue_review_task_from_trace_http_request->task_id = NULL;
    }
    if (enqueue_review_task_from_trace_http_request->trace_id) {
        free(enqueue_review_task_from_trace_http_request->trace_id);
        enqueue_review_task_from_trace_http_request->trace_id = NULL;
    }
    free(enqueue_review_task_from_trace_http_request);
}

cJSON *enqueue_review_task_from_trace_http_request_convertToJSON(enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request) {
    cJSON *item = cJSON_CreateObject();

    // enqueue_review_task_from_trace_http_request->dataset_case_id
    if(enqueue_review_task_from_trace_http_request->dataset_case_id) {
    if(cJSON_AddStringToObject(item, "dataset_case_id", enqueue_review_task_from_trace_http_request->dataset_case_id) == NULL) {
    goto fail; //String
    }
    }


    // enqueue_review_task_from_trace_http_request->dataset_id
    if(enqueue_review_task_from_trace_http_request->dataset_id) {
    if(cJSON_AddStringToObject(item, "dataset_id", enqueue_review_task_from_trace_http_request->dataset_id) == NULL) {
    goto fail; //String
    }
    }


    // enqueue_review_task_from_trace_http_request->priority
    if(enqueue_review_task_from_trace_http_request->priority) {
    if(cJSON_AddNumberToObject(item, "priority", enqueue_review_task_from_trace_http_request->priority) == NULL) {
    goto fail; //Numeric
    }
    }


    // enqueue_review_task_from_trace_http_request->span_id
    if(enqueue_review_task_from_trace_http_request->span_id) {
    if(cJSON_AddStringToObject(item, "span_id", enqueue_review_task_from_trace_http_request->span_id) == NULL) {
    goto fail; //String
    }
    }


    // enqueue_review_task_from_trace_http_request->task_id
    if(enqueue_review_task_from_trace_http_request->task_id) {
    if(cJSON_AddStringToObject(item, "task_id", enqueue_review_task_from_trace_http_request->task_id) == NULL) {
    goto fail; //String
    }
    }


    // enqueue_review_task_from_trace_http_request->trace_id
    if (!enqueue_review_task_from_trace_http_request->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", enqueue_review_task_from_trace_http_request->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request_parseFromJSON(cJSON *enqueue_review_task_from_trace_http_requestJSON){

    enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request_local_var = NULL;

    // enqueue_review_task_from_trace_http_request->dataset_case_id
    cJSON *dataset_case_id = cJSON_GetObjectItemCaseSensitive(enqueue_review_task_from_trace_http_requestJSON, "dataset_case_id");
    if (cJSON_IsNull(dataset_case_id)) {
        dataset_case_id = NULL;
    }
    if (dataset_case_id) { 
    if(!cJSON_IsString(dataset_case_id) && !cJSON_IsNull(dataset_case_id))
    {
    goto end; //String
    }
    }

    // enqueue_review_task_from_trace_http_request->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(enqueue_review_task_from_trace_http_requestJSON, "dataset_id");
    if (cJSON_IsNull(dataset_id)) {
        dataset_id = NULL;
    }
    if (dataset_id) { 
    if(!cJSON_IsString(dataset_id) && !cJSON_IsNull(dataset_id))
    {
    goto end; //String
    }
    }

    // enqueue_review_task_from_trace_http_request->priority
    cJSON *priority = cJSON_GetObjectItemCaseSensitive(enqueue_review_task_from_trace_http_requestJSON, "priority");
    if (cJSON_IsNull(priority)) {
        priority = NULL;
    }
    if (priority) { 
    if(!cJSON_IsNumber(priority))
    {
    goto end; //Numeric
    }
    }

    // enqueue_review_task_from_trace_http_request->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(enqueue_review_task_from_trace_http_requestJSON, "span_id");
    if (cJSON_IsNull(span_id)) {
        span_id = NULL;
    }
    if (span_id) { 
    if(!cJSON_IsString(span_id) && !cJSON_IsNull(span_id))
    {
    goto end; //String
    }
    }

    // enqueue_review_task_from_trace_http_request->task_id
    cJSON *task_id = cJSON_GetObjectItemCaseSensitive(enqueue_review_task_from_trace_http_requestJSON, "task_id");
    if (cJSON_IsNull(task_id)) {
        task_id = NULL;
    }
    if (task_id) { 
    if(!cJSON_IsString(task_id) && !cJSON_IsNull(task_id))
    {
    goto end; //String
    }
    }

    // enqueue_review_task_from_trace_http_request->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(enqueue_review_task_from_trace_http_requestJSON, "trace_id");
    if (cJSON_IsNull(trace_id)) {
        trace_id = NULL;
    }
    if (!trace_id) {
        goto end;
    }

    
    if(!cJSON_IsString(trace_id))
    {
    goto end; //String
    }


    enqueue_review_task_from_trace_http_request_local_var = enqueue_review_task_from_trace_http_request_create_internal (
        dataset_case_id && !cJSON_IsNull(dataset_case_id) ? strdup(dataset_case_id->valuestring) : NULL,
        dataset_id && !cJSON_IsNull(dataset_id) ? strdup(dataset_id->valuestring) : NULL,
        priority ? priority->valuedouble : 0,
        span_id && !cJSON_IsNull(span_id) ? strdup(span_id->valuestring) : NULL,
        task_id && !cJSON_IsNull(task_id) ? strdup(task_id->valuestring) : NULL,
        strdup(trace_id->valuestring)
        );

    return enqueue_review_task_from_trace_http_request_local_var;
end:
    return NULL;

}
