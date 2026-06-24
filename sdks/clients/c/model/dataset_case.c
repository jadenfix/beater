#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dataset_case.h"



static dataset_case_t *dataset_case_create_internal(
    char *case_id,
    char *created_at,
    char *dataset_id,
    any_type_t *input,
    list_t *input_artifact_hashes,
    char *normalizer_version,
    any_type_t *output,
    char *project_id,
    any_type_t *reference,
    char *source_environment_id,
    char *source_span_id,
    char *source_trace_id,
    char *tenant_id,
    any_type_t *trace,
    int trace_schema_version
    ) {
    dataset_case_t *dataset_case_local_var = malloc(sizeof(dataset_case_t));
    if (!dataset_case_local_var) {
        return NULL;
    }
    dataset_case_local_var->case_id = case_id;
    dataset_case_local_var->created_at = created_at;
    dataset_case_local_var->dataset_id = dataset_id;
    dataset_case_local_var->input = input;
    dataset_case_local_var->input_artifact_hashes = input_artifact_hashes;
    dataset_case_local_var->normalizer_version = normalizer_version;
    dataset_case_local_var->output = output;
    dataset_case_local_var->project_id = project_id;
    dataset_case_local_var->reference = reference;
    dataset_case_local_var->source_environment_id = source_environment_id;
    dataset_case_local_var->source_span_id = source_span_id;
    dataset_case_local_var->source_trace_id = source_trace_id;
    dataset_case_local_var->tenant_id = tenant_id;
    dataset_case_local_var->trace = trace;
    dataset_case_local_var->trace_schema_version = trace_schema_version;

    dataset_case_local_var->_library_owned = 1;
    return dataset_case_local_var;
}

__attribute__((deprecated)) dataset_case_t *dataset_case_create(
    char *case_id,
    char *created_at,
    char *dataset_id,
    any_type_t *input,
    list_t *input_artifact_hashes,
    char *normalizer_version,
    any_type_t *output,
    char *project_id,
    any_type_t *reference,
    char *source_environment_id,
    char *source_span_id,
    char *source_trace_id,
    char *tenant_id,
    any_type_t *trace,
    int trace_schema_version
    ) {
    return dataset_case_create_internal (
        case_id,
        created_at,
        dataset_id,
        input,
        input_artifact_hashes,
        normalizer_version,
        output,
        project_id,
        reference,
        source_environment_id,
        source_span_id,
        source_trace_id,
        tenant_id,
        trace,
        trace_schema_version
        );
}

void dataset_case_free(dataset_case_t *dataset_case) {
    if(NULL == dataset_case){
        return ;
    }
    if(dataset_case->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "dataset_case_free");
        return ;
    }
    listEntry_t *listEntry;
    if (dataset_case->case_id) {
        free(dataset_case->case_id);
        dataset_case->case_id = NULL;
    }
    if (dataset_case->created_at) {
        free(dataset_case->created_at);
        dataset_case->created_at = NULL;
    }
    if (dataset_case->dataset_id) {
        free(dataset_case->dataset_id);
        dataset_case->dataset_id = NULL;
    }
    if (dataset_case->input) {
        _free(dataset_case->input);
        dataset_case->input = NULL;
    }
    if (dataset_case->input_artifact_hashes) {
        list_ForEach(listEntry, dataset_case->input_artifact_hashes) {
            free(listEntry->data);
        }
        list_freeList(dataset_case->input_artifact_hashes);
        dataset_case->input_artifact_hashes = NULL;
    }
    if (dataset_case->normalizer_version) {
        free(dataset_case->normalizer_version);
        dataset_case->normalizer_version = NULL;
    }
    if (dataset_case->output) {
        _free(dataset_case->output);
        dataset_case->output = NULL;
    }
    if (dataset_case->project_id) {
        free(dataset_case->project_id);
        dataset_case->project_id = NULL;
    }
    if (dataset_case->reference) {
        _free(dataset_case->reference);
        dataset_case->reference = NULL;
    }
    if (dataset_case->source_environment_id) {
        free(dataset_case->source_environment_id);
        dataset_case->source_environment_id = NULL;
    }
    if (dataset_case->source_span_id) {
        free(dataset_case->source_span_id);
        dataset_case->source_span_id = NULL;
    }
    if (dataset_case->source_trace_id) {
        free(dataset_case->source_trace_id);
        dataset_case->source_trace_id = NULL;
    }
    if (dataset_case->tenant_id) {
        free(dataset_case->tenant_id);
        dataset_case->tenant_id = NULL;
    }
    if (dataset_case->trace) {
        _free(dataset_case->trace);
        dataset_case->trace = NULL;
    }
    free(dataset_case);
}

cJSON *dataset_case_convertToJSON(dataset_case_t *dataset_case) {
    cJSON *item = cJSON_CreateObject();

    // dataset_case->case_id
    if (!dataset_case->case_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "case_id", dataset_case->case_id) == NULL) {
    goto fail; //String
    }


    // dataset_case->created_at
    if (!dataset_case->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", dataset_case->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // dataset_case->dataset_id
    if (!dataset_case->dataset_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_id", dataset_case->dataset_id) == NULL) {
    goto fail; //String
    }


    // dataset_case->input
    if (!dataset_case->input) {
        goto fail;
    }
    cJSON *input_local_JSON = _convertToJSON(dataset_case->input);
    if(input_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "input", input_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // dataset_case->input_artifact_hashes
    if (!dataset_case->input_artifact_hashes) {
        goto fail;
    }
    cJSON *input_artifact_hashes = cJSON_AddArrayToObject(item, "input_artifact_hashes");
    if(input_artifact_hashes == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *input_artifact_hashesListEntry;
    list_ForEach(input_artifact_hashesListEntry, dataset_case->input_artifact_hashes) {
    if(cJSON_AddStringToObject(input_artifact_hashes, "", input_artifact_hashesListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // dataset_case->normalizer_version
    if (!dataset_case->normalizer_version) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "normalizer_version", dataset_case->normalizer_version) == NULL) {
    goto fail; //String
    }


    // dataset_case->output
    if (!dataset_case->output) {
        goto fail;
    }
    cJSON *output_local_JSON = _convertToJSON(dataset_case->output);
    if(output_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "output", output_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // dataset_case->project_id
    if (!dataset_case->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", dataset_case->project_id) == NULL) {
    goto fail; //String
    }


    // dataset_case->reference
    if(dataset_case->reference) {
    cJSON *reference_local_JSON = _convertToJSON(dataset_case->reference);
    if(reference_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "reference", reference_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // dataset_case->source_environment_id
    if (!dataset_case->source_environment_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "source_environment_id", dataset_case->source_environment_id) == NULL) {
    goto fail; //String
    }


    // dataset_case->source_span_id
    if (!dataset_case->source_span_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "source_span_id", dataset_case->source_span_id) == NULL) {
    goto fail; //String
    }


    // dataset_case->source_trace_id
    if (!dataset_case->source_trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "source_trace_id", dataset_case->source_trace_id) == NULL) {
    goto fail; //String
    }


    // dataset_case->tenant_id
    if (!dataset_case->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", dataset_case->tenant_id) == NULL) {
    goto fail; //String
    }


    // dataset_case->trace
    if (!dataset_case->trace) {
        goto fail;
    }
    cJSON *trace_local_JSON = _convertToJSON(dataset_case->trace);
    if(trace_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "trace", trace_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // dataset_case->trace_schema_version
    if (!dataset_case->trace_schema_version) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "trace_schema_version", dataset_case->trace_schema_version) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

dataset_case_t *dataset_case_parseFromJSON(cJSON *dataset_caseJSON){

    dataset_case_t *dataset_case_local_var = NULL;

    // define the local variable for dataset_case->input
    _t *input_local_nonprim = NULL;

    // define the local list for dataset_case->input_artifact_hashes
    list_t *input_artifact_hashesList = NULL;

    // define the local variable for dataset_case->output
    _t *output_local_nonprim = NULL;

    // define the local variable for dataset_case->reference
    _t *reference_local_nonprim = NULL;

    // define the local variable for dataset_case->trace
    _t *trace_local_nonprim = NULL;

    // dataset_case->case_id
    cJSON *case_id = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "case_id");
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

    // dataset_case->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "created_at");
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

    // dataset_case->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "dataset_id");
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

    // dataset_case->input
    cJSON *input = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "input");
    if (cJSON_IsNull(input)) {
        input = NULL;
    }
    if (!input) {
        goto end;
    }

    
    input_local_nonprim = _parseFromJSON(input); //custom

    // dataset_case->input_artifact_hashes
    cJSON *input_artifact_hashes = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "input_artifact_hashes");
    if (cJSON_IsNull(input_artifact_hashes)) {
        input_artifact_hashes = NULL;
    }
    if (!input_artifact_hashes) {
        goto end;
    }

    
    cJSON *input_artifact_hashes_local = NULL;
    if(!cJSON_IsArray(input_artifact_hashes)) {
        goto end;//primitive container
    }
    input_artifact_hashesList = list_createList();

    cJSON_ArrayForEach(input_artifact_hashes_local, input_artifact_hashes)
    {
        if(!cJSON_IsString(input_artifact_hashes_local))
        {
            goto end;
        }
        list_addElement(input_artifact_hashesList , strdup(input_artifact_hashes_local->valuestring));
    }

    // dataset_case->normalizer_version
    cJSON *normalizer_version = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "normalizer_version");
    if (cJSON_IsNull(normalizer_version)) {
        normalizer_version = NULL;
    }
    if (!normalizer_version) {
        goto end;
    }

    
    if(!cJSON_IsString(normalizer_version))
    {
    goto end; //String
    }

    // dataset_case->output
    cJSON *output = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "output");
    if (cJSON_IsNull(output)) {
        output = NULL;
    }
    if (!output) {
        goto end;
    }

    
    output_local_nonprim = _parseFromJSON(output); //custom

    // dataset_case->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "project_id");
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

    // dataset_case->reference
    cJSON *reference = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "reference");
    if (cJSON_IsNull(reference)) {
        reference = NULL;
    }
    if (reference) { 
    reference_local_nonprim = _parseFromJSON(reference); //custom
    }

    // dataset_case->source_environment_id
    cJSON *source_environment_id = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "source_environment_id");
    if (cJSON_IsNull(source_environment_id)) {
        source_environment_id = NULL;
    }
    if (!source_environment_id) {
        goto end;
    }

    
    if(!cJSON_IsString(source_environment_id))
    {
    goto end; //String
    }

    // dataset_case->source_span_id
    cJSON *source_span_id = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "source_span_id");
    if (cJSON_IsNull(source_span_id)) {
        source_span_id = NULL;
    }
    if (!source_span_id) {
        goto end;
    }

    
    if(!cJSON_IsString(source_span_id))
    {
    goto end; //String
    }

    // dataset_case->source_trace_id
    cJSON *source_trace_id = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "source_trace_id");
    if (cJSON_IsNull(source_trace_id)) {
        source_trace_id = NULL;
    }
    if (!source_trace_id) {
        goto end;
    }

    
    if(!cJSON_IsString(source_trace_id))
    {
    goto end; //String
    }

    // dataset_case->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "tenant_id");
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

    // dataset_case->trace
    cJSON *trace = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "trace");
    if (cJSON_IsNull(trace)) {
        trace = NULL;
    }
    if (!trace) {
        goto end;
    }

    
    trace_local_nonprim = _parseFromJSON(trace); //custom

    // dataset_case->trace_schema_version
    cJSON *trace_schema_version = cJSON_GetObjectItemCaseSensitive(dataset_caseJSON, "trace_schema_version");
    if (cJSON_IsNull(trace_schema_version)) {
        trace_schema_version = NULL;
    }
    if (!trace_schema_version) {
        goto end;
    }

    
    if(!cJSON_IsNumber(trace_schema_version))
    {
    goto end; //Numeric
    }


    dataset_case_local_var = dataset_case_create_internal (
        strdup(case_id->valuestring),
        strdup(created_at->valuestring),
        strdup(dataset_id->valuestring),
        input_local_nonprim,
        input_artifact_hashesList,
        strdup(normalizer_version->valuestring),
        output_local_nonprim,
        strdup(project_id->valuestring),
        reference ? reference_local_nonprim : NULL,
        strdup(source_environment_id->valuestring),
        strdup(source_span_id->valuestring),
        strdup(source_trace_id->valuestring),
        strdup(tenant_id->valuestring),
        trace_local_nonprim,
        trace_schema_version->valuedouble
        );

    return dataset_case_local_var;
end:
    if (input_local_nonprim) {
        _free(input_local_nonprim);
        input_local_nonprim = NULL;
    }
    if (input_artifact_hashesList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, input_artifact_hashesList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(input_artifact_hashesList);
        input_artifact_hashesList = NULL;
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
