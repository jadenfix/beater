#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluation_case.h"



static evaluation_case_t *evaluation_case_create_internal(
    any_type_t *input,
    any_type_t *output,
    any_type_t *reference,
    any_type_t *trace
    ) {
    evaluation_case_t *evaluation_case_local_var = malloc(sizeof(evaluation_case_t));
    if (!evaluation_case_local_var) {
        return NULL;
    }
    evaluation_case_local_var->input = input;
    evaluation_case_local_var->output = output;
    evaluation_case_local_var->reference = reference;
    evaluation_case_local_var->trace = trace;

    evaluation_case_local_var->_library_owned = 1;
    return evaluation_case_local_var;
}

__attribute__((deprecated)) evaluation_case_t *evaluation_case_create(
    any_type_t *input,
    any_type_t *output,
    any_type_t *reference,
    any_type_t *trace
    ) {
    return evaluation_case_create_internal (
        input,
        output,
        reference,
        trace
        );
}

void evaluation_case_free(evaluation_case_t *evaluation_case) {
    if(NULL == evaluation_case){
        return ;
    }
    if(evaluation_case->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "evaluation_case_free");
        return ;
    }
    listEntry_t *listEntry;
    if (evaluation_case->input) {
        _free(evaluation_case->input);
        evaluation_case->input = NULL;
    }
    if (evaluation_case->output) {
        _free(evaluation_case->output);
        evaluation_case->output = NULL;
    }
    if (evaluation_case->reference) {
        _free(evaluation_case->reference);
        evaluation_case->reference = NULL;
    }
    if (evaluation_case->trace) {
        _free(evaluation_case->trace);
        evaluation_case->trace = NULL;
    }
    free(evaluation_case);
}

cJSON *evaluation_case_convertToJSON(evaluation_case_t *evaluation_case) {
    cJSON *item = cJSON_CreateObject();

    // evaluation_case->input
    if (!evaluation_case->input) {
        goto fail;
    }
    cJSON *input_local_JSON = _convertToJSON(evaluation_case->input);
    if(input_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "input", input_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // evaluation_case->output
    if (!evaluation_case->output) {
        goto fail;
    }
    cJSON *output_local_JSON = _convertToJSON(evaluation_case->output);
    if(output_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "output", output_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // evaluation_case->reference
    if(evaluation_case->reference) {
    cJSON *reference_local_JSON = _convertToJSON(evaluation_case->reference);
    if(reference_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "reference", reference_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // evaluation_case->trace
    if(evaluation_case->trace) {
    cJSON *trace_local_JSON = _convertToJSON(evaluation_case->trace);
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

evaluation_case_t *evaluation_case_parseFromJSON(cJSON *evaluation_caseJSON){

    evaluation_case_t *evaluation_case_local_var = NULL;

    // define the local variable for evaluation_case->input
    _t *input_local_nonprim = NULL;

    // define the local variable for evaluation_case->output
    _t *output_local_nonprim = NULL;

    // define the local variable for evaluation_case->reference
    _t *reference_local_nonprim = NULL;

    // define the local variable for evaluation_case->trace
    _t *trace_local_nonprim = NULL;

    // evaluation_case->input
    cJSON *input = cJSON_GetObjectItemCaseSensitive(evaluation_caseJSON, "input");
    if (cJSON_IsNull(input)) {
        input = NULL;
    }
    if (!input) {
        goto end;
    }

    
    input_local_nonprim = _parseFromJSON(input); //custom

    // evaluation_case->output
    cJSON *output = cJSON_GetObjectItemCaseSensitive(evaluation_caseJSON, "output");
    if (cJSON_IsNull(output)) {
        output = NULL;
    }
    if (!output) {
        goto end;
    }

    
    output_local_nonprim = _parseFromJSON(output); //custom

    // evaluation_case->reference
    cJSON *reference = cJSON_GetObjectItemCaseSensitive(evaluation_caseJSON, "reference");
    if (cJSON_IsNull(reference)) {
        reference = NULL;
    }
    if (reference) { 
    reference_local_nonprim = _parseFromJSON(reference); //custom
    }

    // evaluation_case->trace
    cJSON *trace = cJSON_GetObjectItemCaseSensitive(evaluation_caseJSON, "trace");
    if (cJSON_IsNull(trace)) {
        trace = NULL;
    }
    if (trace) { 
    trace_local_nonprim = _parseFromJSON(trace); //custom
    }


    evaluation_case_local_var = evaluation_case_create_internal (
        input_local_nonprim,
        output_local_nonprim,
        reference ? reference_local_nonprim : NULL,
        trace ? trace_local_nonprim : NULL
        );

    return evaluation_case_local_var;
end:
    if (input_local_nonprim) {
        _free(input_local_nonprim);
        input_local_nonprim = NULL;
    }
    if (output_local_nonprim) {
        _free(output_local_nonprim);
        output_local_nonprim = NULL;
    }
    if (reference_local_nonprim) {
        _free(reference_local_nonprim);
        reference_local_nonprim = NULL;
    }
    if (trace_local_nonprim) {
        _free(trace_local_nonprim);
        trace_local_nonprim = NULL;
    }
    return NULL;

}
