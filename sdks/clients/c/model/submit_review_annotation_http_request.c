#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "submit_review_annotation_http_request.h"



static submit_review_annotation_http_request_t *submit_review_annotation_http_request_create_internal(
    char *annotation_id,
    any_type_t *payload,
    char *reviewer_id,
    beater_api_review_verdict__e verdict
    ) {
    submit_review_annotation_http_request_t *submit_review_annotation_http_request_local_var = malloc(sizeof(submit_review_annotation_http_request_t));
    if (!submit_review_annotation_http_request_local_var) {
        return NULL;
    }
    submit_review_annotation_http_request_local_var->annotation_id = annotation_id;
    submit_review_annotation_http_request_local_var->payload = payload;
    submit_review_annotation_http_request_local_var->reviewer_id = reviewer_id;
    submit_review_annotation_http_request_local_var->verdict = verdict;

    submit_review_annotation_http_request_local_var->_library_owned = 1;
    return submit_review_annotation_http_request_local_var;
}

__attribute__((deprecated)) submit_review_annotation_http_request_t *submit_review_annotation_http_request_create(
    char *annotation_id,
    any_type_t *payload,
    char *reviewer_id,
    beater_api_review_verdict__e verdict
    ) {
    return submit_review_annotation_http_request_create_internal (
        annotation_id,
        payload,
        reviewer_id,
        verdict
        );
}

void submit_review_annotation_http_request_free(submit_review_annotation_http_request_t *submit_review_annotation_http_request) {
    if(NULL == submit_review_annotation_http_request){
        return ;
    }
    if(submit_review_annotation_http_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "submit_review_annotation_http_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (submit_review_annotation_http_request->annotation_id) {
        free(submit_review_annotation_http_request->annotation_id);
        submit_review_annotation_http_request->annotation_id = NULL;
    }
    if (submit_review_annotation_http_request->payload) {
        _free(submit_review_annotation_http_request->payload);
        submit_review_annotation_http_request->payload = NULL;
    }
    if (submit_review_annotation_http_request->reviewer_id) {
        free(submit_review_annotation_http_request->reviewer_id);
        submit_review_annotation_http_request->reviewer_id = NULL;
    }
    free(submit_review_annotation_http_request);
}

cJSON *submit_review_annotation_http_request_convertToJSON(submit_review_annotation_http_request_t *submit_review_annotation_http_request) {
    cJSON *item = cJSON_CreateObject();

    // submit_review_annotation_http_request->annotation_id
    if(submit_review_annotation_http_request->annotation_id) {
    if(cJSON_AddStringToObject(item, "annotation_id", submit_review_annotation_http_request->annotation_id) == NULL) {
    goto fail; //String
    }
    }


    // submit_review_annotation_http_request->payload
    if (!submit_review_annotation_http_request->payload) {
        goto fail;
    }
    cJSON *payload_local_JSON = _convertToJSON(submit_review_annotation_http_request->payload);
    if(payload_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "payload", payload_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // submit_review_annotation_http_request->reviewer_id
    if (!submit_review_annotation_http_request->reviewer_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "reviewer_id", submit_review_annotation_http_request->reviewer_id) == NULL) {
    goto fail; //String
    }


    // submit_review_annotation_http_request->verdict
    if (beater_api_review_verdict__NULL == submit_review_annotation_http_request->verdict) {
        goto fail;
    }
    cJSON *verdict_local_JSON = review_verdict_convertToJSON(submit_review_annotation_http_request->verdict);
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

submit_review_annotation_http_request_t *submit_review_annotation_http_request_parseFromJSON(cJSON *submit_review_annotation_http_requestJSON){

    submit_review_annotation_http_request_t *submit_review_annotation_http_request_local_var = NULL;

    // define the local variable for submit_review_annotation_http_request->payload
    _t *payload_local_nonprim = NULL;

    // define the local variable for submit_review_annotation_http_request->verdict
    beater_api_review_verdict__e verdict_local_nonprim = 0;

    // submit_review_annotation_http_request->annotation_id
    cJSON *annotation_id = cJSON_GetObjectItemCaseSensitive(submit_review_annotation_http_requestJSON, "annotation_id");
    if (cJSON_IsNull(annotation_id)) {
        annotation_id = NULL;
    }
    if (annotation_id) { 
    if(!cJSON_IsString(annotation_id) && !cJSON_IsNull(annotation_id))
    {
    goto end; //String
    }
    }

    // submit_review_annotation_http_request->payload
    cJSON *payload = cJSON_GetObjectItemCaseSensitive(submit_review_annotation_http_requestJSON, "payload");
    if (cJSON_IsNull(payload)) {
        payload = NULL;
    }
    if (!payload) {
        goto end;
    }

    
    payload_local_nonprim = _parseFromJSON(payload); //custom

    // submit_review_annotation_http_request->reviewer_id
    cJSON *reviewer_id = cJSON_GetObjectItemCaseSensitive(submit_review_annotation_http_requestJSON, "reviewer_id");
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

    // submit_review_annotation_http_request->verdict
    cJSON *verdict = cJSON_GetObjectItemCaseSensitive(submit_review_annotation_http_requestJSON, "verdict");
    if (cJSON_IsNull(verdict)) {
        verdict = NULL;
    }
    if (!verdict) {
        goto end;
    }

    
    verdict_local_nonprim = review_verdict_parseFromJSON(verdict); //custom


    submit_review_annotation_http_request_local_var = submit_review_annotation_http_request_create_internal (
        annotation_id && !cJSON_IsNull(annotation_id) ? strdup(annotation_id->valuestring) : NULL,
        payload_local_nonprim,
        strdup(reviewer_id->valuestring),
        verdict_local_nonprim
        );

    return submit_review_annotation_http_request_local_var;
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
