#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "span_io_response.h"



static span_io_response_t *span_io_response_create_internal(
    span_io_value_t *input,
    span_io_value_t *output,
    char *span_id,
    char *tenant_id,
    char *trace_id
    ) {
    span_io_response_t *span_io_response_local_var = malloc(sizeof(span_io_response_t));
    if (!span_io_response_local_var) {
        return NULL;
    }
    span_io_response_local_var->input = input;
    span_io_response_local_var->output = output;
    span_io_response_local_var->span_id = span_id;
    span_io_response_local_var->tenant_id = tenant_id;
    span_io_response_local_var->trace_id = trace_id;

    span_io_response_local_var->_library_owned = 1;
    return span_io_response_local_var;
}

__attribute__((deprecated)) span_io_response_t *span_io_response_create(
    span_io_value_t *input,
    span_io_value_t *output,
    char *span_id,
    char *tenant_id,
    char *trace_id
    ) {
    return span_io_response_create_internal (
        input,
        output,
        span_id,
        tenant_id,
        trace_id
        );
}

void span_io_response_free(span_io_response_t *span_io_response) {
    if(NULL == span_io_response){
        return ;
    }
    if(span_io_response->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "span_io_response_free");
        return ;
    }
    listEntry_t *listEntry;
    if (span_io_response->input) {
        span_io_value_free(span_io_response->input);
        span_io_response->input = NULL;
    }
    if (span_io_response->output) {
        span_io_value_free(span_io_response->output);
        span_io_response->output = NULL;
    }
    if (span_io_response->span_id) {
        free(span_io_response->span_id);
        span_io_response->span_id = NULL;
    }
    if (span_io_response->tenant_id) {
        free(span_io_response->tenant_id);
        span_io_response->tenant_id = NULL;
    }
    if (span_io_response->trace_id) {
        free(span_io_response->trace_id);
        span_io_response->trace_id = NULL;
    }
    free(span_io_response);
}

cJSON *span_io_response_convertToJSON(span_io_response_t *span_io_response) {
    cJSON *item = cJSON_CreateObject();

    // span_io_response->input
    if (!span_io_response->input) {
        goto fail;
    }
    cJSON *input_local_JSON = span_io_value_convertToJSON(span_io_response->input);
    if(input_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "input", input_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // span_io_response->output
    if (!span_io_response->output) {
        goto fail;
    }
    cJSON *output_local_JSON = span_io_value_convertToJSON(span_io_response->output);
    if(output_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "output", output_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // span_io_response->span_id
    if (!span_io_response->span_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "span_id", span_io_response->span_id) == NULL) {
    goto fail; //String
    }


    // span_io_response->tenant_id
    if (!span_io_response->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", span_io_response->tenant_id) == NULL) {
    goto fail; //String
    }


    // span_io_response->trace_id
    if (!span_io_response->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", span_io_response->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

span_io_response_t *span_io_response_parseFromJSON(cJSON *span_io_responseJSON){

    span_io_response_t *span_io_response_local_var = NULL;

    // define the local variable for span_io_response->input
    span_io_value_t *input_local_nonprim = NULL;

    // define the local variable for span_io_response->output
    span_io_value_t *output_local_nonprim = NULL;

    // span_io_response->input
    cJSON *input = cJSON_GetObjectItemCaseSensitive(span_io_responseJSON, "input");
    if (cJSON_IsNull(input)) {
        input = NULL;
    }
    if (!input) {
        goto end;
    }

    
    input_local_nonprim = span_io_value_parseFromJSON(input); //nonprimitive

    // span_io_response->output
    cJSON *output = cJSON_GetObjectItemCaseSensitive(span_io_responseJSON, "output");
    if (cJSON_IsNull(output)) {
        output = NULL;
    }
    if (!output) {
        goto end;
    }

    
    output_local_nonprim = span_io_value_parseFromJSON(output); //nonprimitive

    // span_io_response->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(span_io_responseJSON, "span_id");
    if (cJSON_IsNull(span_id)) {
        span_id = NULL;
    }
    if (!span_id) {
        goto end;
    }

    
    if(!cJSON_IsString(span_id))
    {
    goto end; //String
    }

    // span_io_response->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(span_io_responseJSON, "tenant_id");
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

    // span_io_response->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(span_io_responseJSON, "trace_id");
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


    span_io_response_local_var = span_io_response_create_internal (
        input_local_nonprim,
        output_local_nonprim,
        strdup(span_id->valuestring),
        strdup(tenant_id->valuestring),
        strdup(trace_id->valuestring)
        );

    return span_io_response_local_var;
end:
    if (input_local_nonprim) {
        span_io_value_free(input_local_nonprim);
        input_local_nonprim = NULL;
    }
    if (output_local_nonprim) {
        span_io_value_free(output_local_nonprim);
        output_local_nonprim = NULL;
    }
    return NULL;

}
