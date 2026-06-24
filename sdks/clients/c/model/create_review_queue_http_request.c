#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_review_queue_http_request.h"



static create_review_queue_http_request_t *create_review_queue_http_request_create_internal(
    any_type_t *annotation_schema,
    char *name,
    char *queue_id
    ) {
    create_review_queue_http_request_t *create_review_queue_http_request_local_var = malloc(sizeof(create_review_queue_http_request_t));
    if (!create_review_queue_http_request_local_var) {
        return NULL;
    }
    create_review_queue_http_request_local_var->annotation_schema = annotation_schema;
    create_review_queue_http_request_local_var->name = name;
    create_review_queue_http_request_local_var->queue_id = queue_id;

    create_review_queue_http_request_local_var->_library_owned = 1;
    return create_review_queue_http_request_local_var;
}

__attribute__((deprecated)) create_review_queue_http_request_t *create_review_queue_http_request_create(
    any_type_t *annotation_schema,
    char *name,
    char *queue_id
    ) {
    return create_review_queue_http_request_create_internal (
        annotation_schema,
        name,
        queue_id
        );
}

void create_review_queue_http_request_free(create_review_queue_http_request_t *create_review_queue_http_request) {
    if(NULL == create_review_queue_http_request){
        return ;
    }
    if(create_review_queue_http_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "create_review_queue_http_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (create_review_queue_http_request->annotation_schema) {
        _free(create_review_queue_http_request->annotation_schema);
        create_review_queue_http_request->annotation_schema = NULL;
    }
    if (create_review_queue_http_request->name) {
        free(create_review_queue_http_request->name);
        create_review_queue_http_request->name = NULL;
    }
    if (create_review_queue_http_request->queue_id) {
        free(create_review_queue_http_request->queue_id);
        create_review_queue_http_request->queue_id = NULL;
    }
    free(create_review_queue_http_request);
}

cJSON *create_review_queue_http_request_convertToJSON(create_review_queue_http_request_t *create_review_queue_http_request) {
    cJSON *item = cJSON_CreateObject();

    // create_review_queue_http_request->annotation_schema
    if (!create_review_queue_http_request->annotation_schema) {
        goto fail;
    }
    cJSON *annotation_schema_local_JSON = _convertToJSON(create_review_queue_http_request->annotation_schema);
    if(annotation_schema_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "annotation_schema", annotation_schema_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // create_review_queue_http_request->name
    if (!create_review_queue_http_request->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", create_review_queue_http_request->name) == NULL) {
    goto fail; //String
    }


    // create_review_queue_http_request->queue_id
    if(create_review_queue_http_request->queue_id) {
    if(cJSON_AddStringToObject(item, "queue_id", create_review_queue_http_request->queue_id) == NULL) {
    goto fail; //String
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

create_review_queue_http_request_t *create_review_queue_http_request_parseFromJSON(cJSON *create_review_queue_http_requestJSON){

    create_review_queue_http_request_t *create_review_queue_http_request_local_var = NULL;

    // define the local variable for create_review_queue_http_request->annotation_schema
    _t *annotation_schema_local_nonprim = NULL;

    // create_review_queue_http_request->annotation_schema
    cJSON *annotation_schema = cJSON_GetObjectItemCaseSensitive(create_review_queue_http_requestJSON, "annotation_schema");
    if (cJSON_IsNull(annotation_schema)) {
        annotation_schema = NULL;
    }
    if (!annotation_schema) {
        goto end;
    }

    
    annotation_schema_local_nonprim = _parseFromJSON(annotation_schema); //custom

    // create_review_queue_http_request->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(create_review_queue_http_requestJSON, "name");
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

    // create_review_queue_http_request->queue_id
    cJSON *queue_id = cJSON_GetObjectItemCaseSensitive(create_review_queue_http_requestJSON, "queue_id");
    if (cJSON_IsNull(queue_id)) {
        queue_id = NULL;
    }
    if (queue_id) { 
    if(!cJSON_IsString(queue_id) && !cJSON_IsNull(queue_id))
    {
    goto end; //String
    }
    }


    create_review_queue_http_request_local_var = create_review_queue_http_request_create_internal (
        annotation_schema_local_nonprim,
        strdup(name->valuestring),
        queue_id && !cJSON_IsNull(queue_id) ? strdup(queue_id->valuestring) : NULL
        );

    return create_review_queue_http_request_local_var;
end:
    if (annotation_schema_local_nonprim) {
        _free(annotation_schema_local_nonprim);
        annotation_schema_local_nonprim = NULL;
    }
    return NULL;

}
