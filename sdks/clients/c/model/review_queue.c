#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "review_queue.h"



static review_queue_t *review_queue_create_internal(
    any_type_t *annotation_schema,
    char *created_at,
    char *name,
    char *project_id,
    char *queue_id,
    char *tenant_id
    ) {
    review_queue_t *review_queue_local_var = malloc(sizeof(review_queue_t));
    if (!review_queue_local_var) {
        return NULL;
    }
    review_queue_local_var->annotation_schema = annotation_schema;
    review_queue_local_var->created_at = created_at;
    review_queue_local_var->name = name;
    review_queue_local_var->project_id = project_id;
    review_queue_local_var->queue_id = queue_id;
    review_queue_local_var->tenant_id = tenant_id;

    review_queue_local_var->_library_owned = 1;
    return review_queue_local_var;
}

__attribute__((deprecated)) review_queue_t *review_queue_create(
    any_type_t *annotation_schema,
    char *created_at,
    char *name,
    char *project_id,
    char *queue_id,
    char *tenant_id
    ) {
    return review_queue_create_internal (
        annotation_schema,
        created_at,
        name,
        project_id,
        queue_id,
        tenant_id
        );
}

void review_queue_free(review_queue_t *review_queue) {
    if(NULL == review_queue){
        return ;
    }
    if(review_queue->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "review_queue_free");
        return ;
    }
    listEntry_t *listEntry;
    if (review_queue->annotation_schema) {
        _free(review_queue->annotation_schema);
        review_queue->annotation_schema = NULL;
    }
    if (review_queue->created_at) {
        free(review_queue->created_at);
        review_queue->created_at = NULL;
    }
    if (review_queue->name) {
        free(review_queue->name);
        review_queue->name = NULL;
    }
    if (review_queue->project_id) {
        free(review_queue->project_id);
        review_queue->project_id = NULL;
    }
    if (review_queue->queue_id) {
        free(review_queue->queue_id);
        review_queue->queue_id = NULL;
    }
    if (review_queue->tenant_id) {
        free(review_queue->tenant_id);
        review_queue->tenant_id = NULL;
    }
    free(review_queue);
}

cJSON *review_queue_convertToJSON(review_queue_t *review_queue) {
    cJSON *item = cJSON_CreateObject();

    // review_queue->annotation_schema
    if (!review_queue->annotation_schema) {
        goto fail;
    }
    cJSON *annotation_schema_local_JSON = _convertToJSON(review_queue->annotation_schema);
    if(annotation_schema_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "annotation_schema", annotation_schema_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // review_queue->created_at
    if (!review_queue->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", review_queue->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // review_queue->name
    if (!review_queue->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", review_queue->name) == NULL) {
    goto fail; //String
    }


    // review_queue->project_id
    if (!review_queue->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", review_queue->project_id) == NULL) {
    goto fail; //String
    }


    // review_queue->queue_id
    if (!review_queue->queue_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "queue_id", review_queue->queue_id) == NULL) {
    goto fail; //String
    }


    // review_queue->tenant_id
    if (!review_queue->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", review_queue->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

review_queue_t *review_queue_parseFromJSON(cJSON *review_queueJSON){

    review_queue_t *review_queue_local_var = NULL;

    // define the local variable for review_queue->annotation_schema
    _t *annotation_schema_local_nonprim = NULL;

    // review_queue->annotation_schema
    cJSON *annotation_schema = cJSON_GetObjectItemCaseSensitive(review_queueJSON, "annotation_schema");
    if (cJSON_IsNull(annotation_schema)) {
        annotation_schema = NULL;
    }
    if (!annotation_schema) {
        goto end;
    }

    
    annotation_schema_local_nonprim = _parseFromJSON(annotation_schema); //custom

    // review_queue->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(review_queueJSON, "created_at");
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

    // review_queue->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(review_queueJSON, "name");
    if (cJSON_IsNull(name)) {
        name = NULL;
    }
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }

    // review_queue->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(review_queueJSON, "project_id");
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

    // review_queue->queue_id
    cJSON *queue_id = cJSON_GetObjectItemCaseSensitive(review_queueJSON, "queue_id");
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

    // review_queue->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(review_queueJSON, "tenant_id");
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


    review_queue_local_var = review_queue_create_internal (
        annotation_schema_local_nonprim,
        strdup(created_at->valuestring),
        strdup(name->valuestring),
        strdup(project_id->valuestring),
        strdup(queue_id->valuestring),
        strdup(tenant_id->valuestring)
        );

    return review_queue_local_var;
end:
    if (annotation_schema_local_nonprim) {
        _free(annotation_schema_local_nonprim);
        annotation_schema_local_nonprim = NULL;
    }
    return NULL;

}
