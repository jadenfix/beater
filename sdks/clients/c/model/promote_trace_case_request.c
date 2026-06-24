#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "promote_trace_case_request.h"



static promote_trace_case_request_t *promote_trace_case_request_create_internal(
    any_type_t *reference,
    char *span_id,
    char *trace_id
    ) {
    promote_trace_case_request_t *promote_trace_case_request_local_var = malloc(sizeof(promote_trace_case_request_t));
    if (!promote_trace_case_request_local_var) {
        return NULL;
    }
    promote_trace_case_request_local_var->reference = reference;
    promote_trace_case_request_local_var->span_id = span_id;
    promote_trace_case_request_local_var->trace_id = trace_id;

    promote_trace_case_request_local_var->_library_owned = 1;
    return promote_trace_case_request_local_var;
}

__attribute__((deprecated)) promote_trace_case_request_t *promote_trace_case_request_create(
    any_type_t *reference,
    char *span_id,
    char *trace_id
    ) {
    return promote_trace_case_request_create_internal (
        reference,
        span_id,
        trace_id
        );
}

void promote_trace_case_request_free(promote_trace_case_request_t *promote_trace_case_request) {
    if(NULL == promote_trace_case_request){
        return ;
    }
    if(promote_trace_case_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "promote_trace_case_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (promote_trace_case_request->reference) {
        _free(promote_trace_case_request->reference);
        promote_trace_case_request->reference = NULL;
    }
    if (promote_trace_case_request->span_id) {
        free(promote_trace_case_request->span_id);
        promote_trace_case_request->span_id = NULL;
    }
    if (promote_trace_case_request->trace_id) {
        free(promote_trace_case_request->trace_id);
        promote_trace_case_request->trace_id = NULL;
    }
    free(promote_trace_case_request);
}

cJSON *promote_trace_case_request_convertToJSON(promote_trace_case_request_t *promote_trace_case_request) {
    cJSON *item = cJSON_CreateObject();

    // promote_trace_case_request->reference
    if(promote_trace_case_request->reference) {
    cJSON *reference_local_JSON = _convertToJSON(promote_trace_case_request->reference);
    if(reference_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "reference", reference_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // promote_trace_case_request->span_id
    if(promote_trace_case_request->span_id) {
    if(cJSON_AddStringToObject(item, "span_id", promote_trace_case_request->span_id) == NULL) {
    goto fail; //String
    }
    }


    // promote_trace_case_request->trace_id
    if (!promote_trace_case_request->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", promote_trace_case_request->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

promote_trace_case_request_t *promote_trace_case_request_parseFromJSON(cJSON *promote_trace_case_requestJSON){

    promote_trace_case_request_t *promote_trace_case_request_local_var = NULL;

    // define the local variable for promote_trace_case_request->reference
    _t *reference_local_nonprim = NULL;

    // promote_trace_case_request->reference
    cJSON *reference = cJSON_GetObjectItemCaseSensitive(promote_trace_case_requestJSON, "reference");
    if (cJSON_IsNull(reference)) {
        reference = NULL;
    }
    if (reference) { 
    reference_local_nonprim = _parseFromJSON(reference); //custom
    }

    // promote_trace_case_request->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(promote_trace_case_requestJSON, "span_id");
    if (cJSON_IsNull(span_id)) {
        span_id = NULL;
    }
    if (span_id) { 
    if(!cJSON_IsString(span_id) && !cJSON_IsNull(span_id))
    {
    goto end; //String
    }
    }

    // promote_trace_case_request->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(promote_trace_case_requestJSON, "trace_id");
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


    promote_trace_case_request_local_var = promote_trace_case_request_create_internal (
        reference ? reference_local_nonprim : NULL,
        span_id && !cJSON_IsNull(span_id) ? strdup(span_id->valuestring) : NULL,
        strdup(trace_id->valuestring)
        );

    return promote_trace_case_request_local_var;
end:
    if (reference_local_nonprim) {
        _free(reference_local_nonprim);
        reference_local_nonprim = NULL;
    }
    return NULL;

}
