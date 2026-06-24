#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "review_annotation.h"



static review_annotation_t *review_annotation_create_internal(
    char *annotation_id,
    char *created_at,
    any_type_t *payload,
    char *project_id,
    char *queue_id,
    char *reviewer_id,
    char *task_id,
    char *tenant_id,
    beater_api_review_verdict__e verdict
    ) {
    review_annotation_t *review_annotation_local_var = malloc(sizeof(review_annotation_t));
    if (!review_annotation_local_var) {
        return NULL;
    }
    review_annotation_local_var->annotation_id = annotation_id;
    review_annotation_local_var->created_at = created_at;
    review_annotation_local_var->payload = payload;
    review_annotation_local_var->project_id = project_id;
    review_annotation_local_var->queue_id = queue_id;
    review_annotation_local_var->reviewer_id = reviewer_id;
    review_annotation_local_var->task_id = task_id;
    review_annotation_local_var->tenant_id = tenant_id;
    review_annotation_local_var->verdict = verdict;

    review_annotation_local_var->_library_owned = 1;
    return review_annotation_local_var;
}

__attribute__((deprecated)) review_annotation_t *review_annotation_create(
    char *annotation_id,
    char *created_at,
    any_type_t *payload,
    char *project_id,
    char *queue_id,
    char *reviewer_id,
    char *task_id,
    char *tenant_id,
    beater_api_review_verdict__e verdict
    ) {
    return review_annotation_create_internal (
        annotation_id,
        created_at,
        payload,
        project_id,
        queue_id,
        reviewer_id,
        task_id,
        tenant_id,
        verdict
        );
}

void review_annotation_free(review_annotation_t *review_annotation) {
    if(NULL == review_annotation){
        return ;
    }
    if(review_annotation->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "review_annotation_free");
        return ;
    }
    listEntry_t *listEntry;
    if (review_annotation->annotation_id) {
        free(review_annotation->annotation_id);
        review_annotation->annotation_id = NULL;
    }
    if (review_annotation->created_at) {
        free(review_annotation->created_at);
        review_annotation->created_at = NULL;
    }
    if (review_annotation->payload) {
        _free(review_annotation->payload);
        review_annotation->payload = NULL;
    }
    if (review_annotation->project_id) {
        free(review_annotation->project_id);
        review_annotation->project_id = NULL;
    }
    if (review_annotation->queue_id) {
        free(review_annotation->queue_id);
        review_annotation->queue_id = NULL;
    }
    if (review_annotation->reviewer_id) {
        free(review_annotation->reviewer_id);
        review_annotation->reviewer_id = NULL;
    }
    if (review_annotation->task_id) {
        free(review_annotation->task_id);
        review_annotation->task_id = NULL;
    }
    if (review_annotation->tenant_id) {
        free(review_annotation->tenant_id);
        review_annotation->tenant_id = NULL;
    }
    free(review_annotation);
}

cJSON *review_annotation_convertToJSON(review_annotation_t *review_annotation) {
    cJSON *item = cJSON_CreateObject();

    // review_annotation->annotation_id
    if (!review_annotation->annotation_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "annotation_id", review_annotation->annotation_id) == NULL) {
    goto fail; //String
    }


    // review_annotation->created_at
    if (!review_annotation->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", review_annotation->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // review_annotation->payload
    if (!review_annotation->payload) {
        goto fail;
    }
    cJSON *payload_local_JSON = _convertToJSON(review_annotation->payload);
    if(payload_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "payload", payload_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // review_annotation->project_id
    if (!review_annotation->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", review_annotation->project_id) == NULL) {
    goto fail; //String
    }


    // review_annotation->queue_id
    if (!review_annotation->queue_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "queue_id", review_annotation->queue_id) == NULL) {
    goto fail; //String
    }


    // review_annotation->reviewer_id
    if (!review_annotation->reviewer_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "reviewer_id", review_annotation->reviewer_id) == NULL) {
    goto fail; //String
    }


    // review_annotation->task_id
    if (!review_annotation->task_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "task_id", review_annotation->task_id) == NULL) {
    goto fail; //String
    }


    // review_annotation->tenant_id
    if (!review_annotation->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", review_annotation->tenant_id) == NULL) {
    goto fail; //String
    }


    // review_annotation->verdict
    if (beater_api_review_verdict__NULL == review_annotation->verdict) {
        goto fail;
    }
    cJSON *verdict_local_JSON = review_verdict_convertToJSON(review_annotation->verdict);
    if(verdict_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "verdict", verdict_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

review_annotation_t *review_annotation_parseFromJSON(cJSON *review_annotationJSON){

    review_annotation_t *review_annotation_local_var = NULL;

    // define the local variable for review_annotation->payload
    _t *payload_local_nonprim = NULL;

    // define the local variable for review_annotation->verdict
    beater_api_review_verdict__e verdict_local_nonprim = 0;

    // review_annotation->annotation_id
    cJSON *annotation_id = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "annotation_id");
    if (cJSON_IsNull(annotation_id)) {
        annotation_id = NULL;
    }
    if (!annotation_id) {
        goto end;
    }

    
    if(!cJSON_IsString(annotation_id))
    {
    goto end; //String
    }

    // review_annotation->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "created_at");
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

    // review_annotation->payload
    cJSON *payload = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "payload");
    if (cJSON_IsNull(payload)) {
        payload = NULL;
    }
    if (!payload) {
        goto end;
    }

    
    payload_local_nonprim = _parseFromJSON(payload); //custom

    // review_annotation->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "project_id");
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

    // review_annotation->queue_id
    cJSON *queue_id = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "queue_id");
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

    // review_annotation->reviewer_id
    cJSON *reviewer_id = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "reviewer_id");
    if (cJSON_IsNull(reviewer_id)) {
        reviewer_id = NULL;
    }
    if (!reviewer_id) {
        goto end;
    }

    
    if(!cJSON_IsString(reviewer_id))
    {
    goto end; //String
    }

    // review_annotation->task_id
    cJSON *task_id = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "task_id");
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

    // review_annotation->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "tenant_id");
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

    // review_annotation->verdict
    cJSON *verdict = cJSON_GetObjectItemCaseSensitive(review_annotationJSON, "verdict");
    if (cJSON_IsNull(verdict)) {
        verdict = NULL;
    }
    if (!verdict) {
        goto end;
    }

    
    verdict_local_nonprim = review_verdict_parseFromJSON(verdict); //custom


    review_annotation_local_var = review_annotation_create_internal (
        strdup(annotation_id->valuestring),
        strdup(created_at->valuestring),
        payload_local_nonprim,
        strdup(project_id->valuestring),
        strdup(queue_id->valuestring),
        strdup(reviewer_id->valuestring),
        strdup(task_id->valuestring),
        strdup(tenant_id->valuestring),
        verdict_local_nonprim
        );

    return review_annotation_local_var;
end:
    if (payload_local_nonprim) {
        _free(payload_local_nonprim);
        payload_local_nonprim = NULL;
    }
    if (verdict_local_nonprim) {
        verdict_local_nonprim = 0;
    }
    return NULL;

}
