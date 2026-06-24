#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "case_output_override_request.h"



static case_output_override_request_t *case_output_override_request_create_internal(
    char *case_id,
    any_type_t *output,
    any_type_t *trace
    ) {
    case_output_override_request_t *case_output_override_request_local_var = malloc(sizeof(case_output_override_request_t));
    if (!case_output_override_request_local_var) {
        return NULL;
    }
    case_output_override_request_local_var->case_id = case_id;
    case_output_override_request_local_var->output = output;
    case_output_override_request_local_var->trace = trace;

    case_output_override_request_local_var->_library_owned = 1;
    return case_output_override_request_local_var;
}

__attribute__((deprecated)) case_output_override_request_t *case_output_override_request_create(
    char *case_id,
    any_type_t *output,
    any_type_t *trace
    ) {
    return case_output_override_request_create_internal (
        case_id,
        output,
        trace
        );
}

void case_output_override_request_free(case_output_override_request_t *case_output_override_request) {
    if(NULL == case_output_override_request){
        return ;
    }
    if(case_output_override_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "case_output_override_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (case_output_override_request->case_id) {
        free(case_output_override_request->case_id);
        case_output_override_request->case_id = NULL;
    }
    if (case_output_override_request->output) {
        _free(case_output_override_request->output);
        case_output_override_request->output = NULL;
    }
    if (case_output_override_request->trace) {
        _free(case_output_override_request->trace);
        case_output_override_request->trace = NULL;
    }
    free(case_output_override_request);
}

cJSON *case_output_override_request_convertToJSON(case_output_override_request_t *case_output_override_request) {
    cJSON *item = cJSON_CreateObject();

    // case_output_override_request->case_id
    if (!case_output_override_request->case_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "case_id", case_output_override_request->case_id) == NULL) {
    goto fail; //String
    }


    // case_output_override_request->output
    if (!case_output_override_request->output) {
        goto fail;
    }
    cJSON *output_local_JSON = _convertToJSON(case_output_override_request->output);
    if(output_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "output", output_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // case_output_override_request->trace
    if(case_output_override_request->trace) {
    cJSON *trace_local_JSON = _convertToJSON(case_output_override_request->trace);
    if(trace_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "trace", trace_local_JSON);
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

case_output_override_request_t *case_output_override_request_parseFromJSON(cJSON *case_output_override_requestJSON){

    case_output_override_request_t *case_output_override_request_local_var = NULL;

    // define the local variable for case_output_override_request->output
    _t *output_local_nonprim = NULL;

    // define the local variable for case_output_override_request->trace
    _t *trace_local_nonprim = NULL;

    // case_output_override_request->case_id
    cJSON *case_id = cJSON_GetObjectItemCaseSensitive(case_output_override_requestJSON, "case_id");
    if (cJSON_IsNull(case_id)) {
        case_id = NULL;
    }
    if (!case_id) {
        goto end;
    }

    
    if(!cJSON_IsString(case_id))
    {
    goto end; //String
    }

    // case_output_override_request->output
    cJSON *output = cJSON_GetObjectItemCaseSensitive(case_output_override_requestJSON, "output");
    if (cJSON_IsNull(output)) {
        output = NULL;
    }
    if (!output) {
        goto end;
    }

    
    output_local_nonprim = _parseFromJSON(output); //custom

    // case_output_override_request->trace
    cJSON *trace = cJSON_GetObjectItemCaseSensitive(case_output_override_requestJSON, "trace");
    if (cJSON_IsNull(trace)) {
        trace = NULL;
    }
    if (trace) { 
    trace_local_nonprim = _parseFromJSON(trace); //custom
    }


    case_output_override_request_local_var = case_output_override_request_create_internal (
        strdup(case_id->valuestring),
        output_local_nonprim,
        trace ? trace_local_nonprim : NULL
        );

    return case_output_override_request_local_var;
end:
    if (output_local_nonprim) {
        _free(output_local_nonprim);
        output_local_nonprim = NULL;
    }
    if (trace_local_nonprim) {
        _free(trace_local_nonprim);
        trace_local_nonprim = NULL;
    }
    return NULL;

}
