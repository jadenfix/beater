#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "review_task.h"



static review_task_t *review_task_create_internal(
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
    ) {
    review_task_t *review_task_local_var = malloc(sizeof(review_task_t));
    if (!review_task_local_var) {
        return NULL;
    }
    review_task_local_var->created_at = created_at;
    review_task_local_var->dataset_case_id = dataset_case_id;
    review_task_local_var->dataset_id = dataset_id;
    review_task_local_var->priority = priority;
    review_task_local_var->project_id = project_id;
    review_task_local_var->queue_id = queue_id;
    review_task_local_var->span_id = span_id;
    review_task_local_var->state = state;
    review_task_local_var->task_id = task_id;
    review_task_local_var->tenant_id = tenant_id;
    review_task_local_var->trace_id = trace_id;
    review_task_local_var->updated_at = updated_at;

    review_task_local_var->_library_owned = 1;
    return review_task_local_var;
}

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
    ) {
    return review_task_create_internal (
        created_at,
        dataset_case_id,
        dataset_id,
        priority,
        project_id,
        queue_id,
        span_id,
        state,
        task_id,
        tenant_id,
        trace_id,
        updated_at
        );
}

void review_task_free(review_task_t *review_task) {
    if(NULL == review_task){
        return ;
    }
    if(review_task->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "review_task_free");
        return ;
    }
    listEntry_t *listEntry;
    if (review_task->created_at) {
        free(review_task->created_at);
        review_task->created_at = NULL;
    }
    if (review_task->dataset_case_id) {
        free(review_task->dataset_case_id);
        review_task->dataset_case_id = NULL;
    }
    if (review_task->dataset_id) {
        free(review_task->dataset_id);
        review_task->dataset_id = NULL;
    }
    if (review_task->project_id) {
        free(review_task->project_id);
        review_task->project_id = NULL;
    }
    if (review_task->queue_id) {
        free(review_task->queue_id);
        review_task->queue_id = NULL;
    }
    if (review_task->span_id) {
        free(review_task->span_id);
        review_task->span_id = NULL;
    }
    if (review_task->task_id) {
        free(review_task->task_id);
        review_task->task_id = NULL;
    }
    if (review_task->tenant_id) {
        free(review_task->tenant_id);
        review_task->tenant_id = NULL;
    }
    if (review_task->trace_id) {
        free(review_task->trace_id);
        review_task->trace_id = NULL;
    }
    if (review_task->updated_at) {
        free(review_task->updated_at);
        review_task->updated_at = NULL;
    }
    free(review_task);
}

cJSON *review_task_convertToJSON(review_task_t *review_task) {
    cJSON *item = cJSON_CreateObject();

    // review_task->created_at
    if (!review_task->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", review_task->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // review_task->dataset_case_id
    if(review_task->dataset_case_id) {
    if(cJSON_AddStringToObject(item, "dataset_case_id", review_task->dataset_case_id) == NULL) {
    goto fail; //String
    }
    }


    // review_task->dataset_id
    if(review_task->dataset_id) {
    if(cJSON_AddStringToObject(item, "dataset_id", review_task->dataset_id) == NULL) {
    goto fail; //String
    }
    }


    // review_task->priority
    if (!review_task->priority) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "priority", review_task->priority) == NULL) {
    goto fail; //Numeric
    }


    // review_task->project_id
    if (!review_task->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", review_task->project_id) == NULL) {
    goto fail; //String
    }


    // review_task->queue_id
    if (!review_task->queue_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "queue_id", review_task->queue_id) == NULL) {
    goto fail; //String
    }


    // review_task->span_id
    if(review_task->span_id) {
    if(cJSON_AddStringToObject(item, "span_id", review_task->span_id) == NULL) {
    goto fail; //String
    }
    }


    // review_task->state
    if (beater_api_review_task_state__NULL == review_task->state) {
        goto fail;
    }
    cJSON *state_local_JSON = review_task_state_convertToJSON(review_task->state);
    if(state_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "state", state_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // review_task->task_id
    if (!review_task->task_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "task_id", review_task->task_id) == NULL) {
    goto fail; //String
    }


    // review_task->tenant_id
    if (!review_task->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", review_task->tenant_id) == NULL) {
    goto fail; //String
    }


    // review_task->trace_id
    if (!review_task->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", review_task->trace_id) == NULL) {
    goto fail; //String
    }


    // review_task->updated_at
    if (!review_task->updated_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "updated_at", review_task->updated_at) == NULL) {
    goto fail; //Date-Time
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

review_task_t *review_task_parseFromJSON(cJSON *review_taskJSON){

    review_task_t *review_task_local_var = NULL;

    // define the local variable for review_task->state
    beater_api_review_task_state__e state_local_nonprim = 0;

    // review_task->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "created_at");
    if (cJSON_IsNull(created_at)) {
        created_at = NULL;
    }
    if (!created_at) {
        goto end;
    }

    
    if(!cJSON_IsString(created_at) && !cJSON_IsNull(created_at))
    {
    goto end; //DateTime
    }

    // review_task->dataset_case_id
    cJSON *dataset_case_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "dataset_case_id");
    if (cJSON_IsNull(dataset_case_id)) {
        dataset_case_id = NULL;
    }
    if (dataset_case_id) { 
    if(!cJSON_IsString(dataset_case_id) && !cJSON_IsNull(dataset_case_id))
    {
    goto end; //String
    }
    }

    // review_task->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "dataset_id");
    if (cJSON_IsNull(dataset_id)) {
        dataset_id = NULL;
    }
    if (dataset_id) { 
    if(!cJSON_IsString(dataset_id) && !cJSON_IsNull(dataset_id))
    {
    goto end; //String
    }
    }

    // review_task->priority
    cJSON *priority = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "priority");
    if (cJSON_IsNull(priority)) {
        priority = NULL;
    }
    if (!priority) {
        goto end;
    }

    
    if(!cJSON_IsNumber(priority))
    {
    goto end; //Numeric
    }

    // review_task->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "project_id");
    if (cJSON_IsNull(project_id)) {
        project_id = NULL;
    }
    if (!project_id) {
        goto end;
    }

    
    if(!cJSON_IsString(project_id))
    {
    goto end; //String
    }

    // review_task->queue_id
    cJSON *queue_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "queue_id");
    if (cJSON_IsNull(queue_id)) {
        queue_id = NULL;
    }
    if (!queue_id) {
        goto end;
    }

    
    if(!cJSON_IsString(queue_id))
    {
    goto end; //String
    }

    // review_task->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "span_id");
    if (cJSON_IsNull(span_id)) {
        span_id = NULL;
    }
    if (span_id) { 
    if(!cJSON_IsString(span_id) && !cJSON_IsNull(span_id))
    {
    goto end; //String
    }
    }

    // review_task->state
    cJSON *state = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "state");
    if (cJSON_IsNull(state)) {
        state = NULL;
    }
    if (!state) {
        goto end;
    }

    
    state_local_nonprim = review_task_state_parseFromJSON(state); //custom

    // review_task->task_id
    cJSON *task_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "task_id");
    if (cJSON_IsNull(task_id)) {
        task_id = NULL;
    }
    if (!task_id) {
        goto end;
    }

    
    if(!cJSON_IsString(task_id))
    {
    goto end; //String
    }

    // review_task->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "tenant_id");
    if (cJSON_IsNull(tenant_id)) {
        tenant_id = NULL;
    }
    if (!tenant_id) {
        goto end;
    }

    
    if(!cJSON_IsString(tenant_id))
    {
    goto end; //String
    }

    // review_task->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "trace_id");
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

    // review_task->updated_at
    cJSON *updated_at = cJSON_GetObjectItemCaseSensitive(review_taskJSON, "updated_at");
    if (cJSON_IsNull(updated_at)) {
        updated_at = NULL;
    }
    if (!updated_at) {
        goto end;
    }

    
    if(!cJSON_IsString(updated_at) && !cJSON_IsNull(updated_at))
    {
    goto end; //DateTime
    }


    review_task_local_var = review_task_create_internal (
        strdup(created_at->valuestring),
        dataset_case_id && !cJSON_IsNull(dataset_case_id) ? strdup(dataset_case_id->valuestring) : NULL,
        dataset_id && !cJSON_IsNull(dataset_id) ? strdup(dataset_id->valuestring) : NULL,
        priority->valuedouble,
        strdup(project_id->valuestring),
        strdup(queue_id->valuestring),
        span_id && !cJSON_IsNull(span_id) ? strdup(span_id->valuestring) : NULL,
        state_local_nonprim,
        strdup(task_id->valuestring),
        strdup(tenant_id->valuestring),
        strdup(trace_id->valuestring),
        strdup(updated_at->valuestring)
        );

    return review_task_local_var;
end:
    if (state_local_nonprim) {
        state_local_nonprim = 0;
    }
    return NULL;

}
