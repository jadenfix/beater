#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "promote_review_annotation_http_request.h"



static promote_review_annotation_http_request_t *promote_review_annotation_http_request_create_internal(
    char *dataset_id,
    any_type_t *reference
    ) {
    promote_review_annotation_http_request_t *promote_review_annotation_http_request_local_var = malloc(sizeof(promote_review_annotation_http_request_t));
    if (!promote_review_annotation_http_request_local_var) {
        return NULL;
    }
    promote_review_annotation_http_request_local_var->dataset_id = dataset_id;
    promote_review_annotation_http_request_local_var->reference = reference;

    promote_review_annotation_http_request_local_var->_library_owned = 1;
    return promote_review_annotation_http_request_local_var;
}

__attribute__((deprecated)) promote_review_annotation_http_request_t *promote_review_annotation_http_request_create(
    char *dataset_id,
    any_type_t *reference
    ) {
    return promote_review_annotation_http_request_create_internal (
        dataset_id,
        reference
        );
}

void promote_review_annotation_http_request_free(promote_review_annotation_http_request_t *promote_review_annotation_http_request) {
    if(NULL == promote_review_annotation_http_request){
        return ;
    }
    if(promote_review_annotation_http_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "promote_review_annotation_http_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (promote_review_annotation_http_request->dataset_id) {
        free(promote_review_annotation_http_request->dataset_id);
        promote_review_annotation_http_request->dataset_id = NULL;
    }
    if (promote_review_annotation_http_request->reference) {
        _free(promote_review_annotation_http_request->reference);
        promote_review_annotation_http_request->reference = NULL;
    }
    free(promote_review_annotation_http_request);
}

cJSON *promote_review_annotation_http_request_convertToJSON(promote_review_annotation_http_request_t *promote_review_annotation_http_request) {
    cJSON *item = cJSON_CreateObject();

    // promote_review_annotation_http_request->dataset_id
    if (!promote_review_annotation_http_request->dataset_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_id", promote_review_annotation_http_request->dataset_id) == NULL) {
    goto fail; //String
    }


    // promote_review_annotation_http_request->reference
    if(promote_review_annotation_http_request->reference) {
    cJSON *reference_local_JSON = _convertToJSON(promote_review_annotation_http_request->reference);
    if(reference_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "reference", reference_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

promote_review_annotation_http_request_t *promote_review_annotation_http_request_parseFromJSON(cJSON *promote_review_annotation_http_requestJSON){

    promote_review_annotation_http_request_t *promote_review_annotation_http_request_local_var = NULL;

    // define the local variable for promote_review_annotation_http_request->reference
    _t *reference_local_nonprim = NULL;

    // promote_review_annotation_http_request->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(promote_review_annotation_http_requestJSON, "dataset_id");
    if (cJSON_IsNull(dataset_id)) {
        dataset_id = NULL;
    }
    if (!dataset_id) {
        goto end;
    }

    
    if(!cJSON_IsString(dataset_id))
    {
    goto end; //String
    }

    // promote_review_annotation_http_request->reference
    cJSON *reference = cJSON_GetObjectItemCaseSensitive(promote_review_annotation_http_requestJSON, "reference");
    if (cJSON_IsNull(reference)) {
        reference = NULL;
    }
    if (reference) { 
    reference_local_nonprim = _parseFromJSON(reference); //custom
    }


    promote_review_annotation_http_request_local_var = promote_review_annotation_http_request_create_internal (
        strdup(dataset_id->valuestring),
        reference ? reference_local_nonprim : NULL
        );

    return promote_review_annotation_http_request_local_var;
end:
    if (reference_local_nonprim) {
        _free(reference_local_nonprim);
        reference_local_nonprim = NULL;
    }
    return NULL;

}
