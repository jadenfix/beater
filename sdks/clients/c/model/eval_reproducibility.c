#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "eval_reproducibility.h"



static eval_reproducibility_t *eval_reproducibility_create_internal(
    char *agent_release_id,
    char *code_hash,
    char *dataset_case_id,
    char *dataset_version_id,
    char *evaluator_version_id,
    list_t *input_artifact_hashes,
    char *judge_model_id,
    any_type_t *judge_parameters,
    char *judge_provider,
    char *judge_rubric_version,
    long judge_seed,
    char *normalizer_version,
    char *prompt_version_id,
    int trace_schema_version,
    char *wasi_abi_version,
    char *wasm_hash
    ) {
    eval_reproducibility_t *eval_reproducibility_local_var = malloc(sizeof(eval_reproducibility_t));
    if (!eval_reproducibility_local_var) {
        return NULL;
    }
    eval_reproducibility_local_var->agent_release_id = agent_release_id;
    eval_reproducibility_local_var->code_hash = code_hash;
    eval_reproducibility_local_var->dataset_case_id = dataset_case_id;
    eval_reproducibility_local_var->dataset_version_id = dataset_version_id;
    eval_reproducibility_local_var->evaluator_version_id = evaluator_version_id;
    eval_reproducibility_local_var->input_artifact_hashes = input_artifact_hashes;
    eval_reproducibility_local_var->judge_model_id = judge_model_id;
    eval_reproducibility_local_var->judge_parameters = judge_parameters;
    eval_reproducibility_local_var->judge_provider = judge_provider;
    eval_reproducibility_local_var->judge_rubric_version = judge_rubric_version;
    eval_reproducibility_local_var->judge_seed = judge_seed;
    eval_reproducibility_local_var->normalizer_version = normalizer_version;
    eval_reproducibility_local_var->prompt_version_id = prompt_version_id;
    eval_reproducibility_local_var->trace_schema_version = trace_schema_version;
    eval_reproducibility_local_var->wasi_abi_version = wasi_abi_version;
    eval_reproducibility_local_var->wasm_hash = wasm_hash;

    eval_reproducibility_local_var->_library_owned = 1;
    return eval_reproducibility_local_var;
}

__attribute__((deprecated)) eval_reproducibility_t *eval_reproducibility_create(
    char *agent_release_id,
    char *code_hash,
    char *dataset_case_id,
    char *dataset_version_id,
    char *evaluator_version_id,
    list_t *input_artifact_hashes,
    char *judge_model_id,
    any_type_t *judge_parameters,
    char *judge_provider,
    char *judge_rubric_version,
    long judge_seed,
    char *normalizer_version,
    char *prompt_version_id,
    int trace_schema_version,
    char *wasi_abi_version,
    char *wasm_hash
    ) {
    return eval_reproducibility_create_internal (
        agent_release_id,
        code_hash,
        dataset_case_id,
        dataset_version_id,
        evaluator_version_id,
        input_artifact_hashes,
        judge_model_id,
        judge_parameters,
        judge_provider,
        judge_rubric_version,
        judge_seed,
        normalizer_version,
        prompt_version_id,
        trace_schema_version,
        wasi_abi_version,
        wasm_hash
        );
}

void eval_reproducibility_free(eval_reproducibility_t *eval_reproducibility) {
    if(NULL == eval_reproducibility){
        return ;
    }
    if(eval_reproducibility->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "eval_reproducibility_free");
        return ;
    }
    listEntry_t *listEntry;
    if (eval_reproducibility->agent_release_id) {
        free(eval_reproducibility->agent_release_id);
        eval_reproducibility->agent_release_id = NULL;
    }
    if (eval_reproducibility->code_hash) {
        free(eval_reproducibility->code_hash);
        eval_reproducibility->code_hash = NULL;
    }
    if (eval_reproducibility->dataset_case_id) {
        free(eval_reproducibility->dataset_case_id);
        eval_reproducibility->dataset_case_id = NULL;
    }
    if (eval_reproducibility->dataset_version_id) {
        free(eval_reproducibility->dataset_version_id);
        eval_reproducibility->dataset_version_id = NULL;
    }
    if (eval_reproducibility->evaluator_version_id) {
        free(eval_reproducibility->evaluator_version_id);
        eval_reproducibility->evaluator_version_id = NULL;
    }
    if (eval_reproducibility->input_artifact_hashes) {
        list_ForEach(listEntry, eval_reproducibility->input_artifact_hashes) {
            free(listEntry->data);
        }
        list_freeList(eval_reproducibility->input_artifact_hashes);
        eval_reproducibility->input_artifact_hashes = NULL;
    }
    if (eval_reproducibility->judge_model_id) {
        free(eval_reproducibility->judge_model_id);
        eval_reproducibility->judge_model_id = NULL;
    }
    if (eval_reproducibility->judge_parameters) {
        _free(eval_reproducibility->judge_parameters);
        eval_reproducibility->judge_parameters = NULL;
    }
    if (eval_reproducibility->judge_provider) {
        free(eval_reproducibility->judge_provider);
        eval_reproducibility->judge_provider = NULL;
    }
    if (eval_reproducibility->judge_rubric_version) {
        free(eval_reproducibility->judge_rubric_version);
        eval_reproducibility->judge_rubric_version = NULL;
    }
    if (eval_reproducibility->normalizer_version) {
        free(eval_reproducibility->normalizer_version);
        eval_reproducibility->normalizer_version = NULL;
    }
    if (eval_reproducibility->prompt_version_id) {
        free(eval_reproducibility->prompt_version_id);
        eval_reproducibility->prompt_version_id = NULL;
    }
    if (eval_reproducibility->wasi_abi_version) {
        free(eval_reproducibility->wasi_abi_version);
        eval_reproducibility->wasi_abi_version = NULL;
    }
    if (eval_reproducibility->wasm_hash) {
        free(eval_reproducibility->wasm_hash);
        eval_reproducibility->wasm_hash = NULL;
    }
    free(eval_reproducibility);
}

cJSON *eval_reproducibility_convertToJSON(eval_reproducibility_t *eval_reproducibility) {
    cJSON *item = cJSON_CreateObject();

    // eval_reproducibility->agent_release_id
    if (!eval_reproducibility->agent_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "agent_release_id", eval_reproducibility->agent_release_id) == NULL) {
    goto fail; //String
    }


    // eval_reproducibility->code_hash
    if(eval_reproducibility->code_hash) {
    if(cJSON_AddStringToObject(item, "code_hash", eval_reproducibility->code_hash) == NULL) {
    goto fail; //String
    }
    }


    // eval_reproducibility->dataset_case_id
    if (!eval_reproducibility->dataset_case_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_case_id", eval_reproducibility->dataset_case_id) == NULL) {
    goto fail; //String
    }


    // eval_reproducibility->dataset_version_id
    if (!eval_reproducibility->dataset_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_version_id", eval_reproducibility->dataset_version_id) == NULL) {
    goto fail; //String
    }


    // eval_reproducibility->evaluator_version_id
    if (!eval_reproducibility->evaluator_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_version_id", eval_reproducibility->evaluator_version_id) == NULL) {
    goto fail; //String
    }


    // eval_reproducibility->input_artifact_hashes
    if (!eval_reproducibility->input_artifact_hashes) {
        goto fail;
    }
    cJSON *input_artifact_hashes = cJSON_AddArrayToObject(item, "input_artifact_hashes");
    if(input_artifact_hashes == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *input_artifact_hashesListEntry;
    list_ForEach(input_artifact_hashesListEntry, eval_reproducibility->input_artifact_hashes) {
    if(cJSON_AddStringToObject(input_artifact_hashes, "", input_artifact_hashesListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // eval_reproducibility->judge_model_id
    if(eval_reproducibility->judge_model_id) {
    if(cJSON_AddStringToObject(item, "judge_model_id", eval_reproducibility->judge_model_id) == NULL) {
    goto fail; //String
    }
    }


    // eval_reproducibility->judge_parameters
    if (!eval_reproducibility->judge_parameters) {
        goto fail;
    }
    cJSON *judge_parameters_local_JSON = _convertToJSON(eval_reproducibility->judge_parameters);
    if(judge_parameters_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "judge_parameters", judge_parameters_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // eval_reproducibility->judge_provider
    if(eval_reproducibility->judge_provider) {
    if(cJSON_AddStringToObject(item, "judge_provider", eval_reproducibility->judge_provider) == NULL) {
    goto fail; //String
    }
    }


    // eval_reproducibility->judge_rubric_version
    if(eval_reproducibility->judge_rubric_version) {
    if(cJSON_AddStringToObject(item, "judge_rubric_version", eval_reproducibility->judge_rubric_version) == NULL) {
    goto fail; //String
    }
    }


    // eval_reproducibility->judge_seed
    if(eval_reproducibility->judge_seed) {
    if(cJSON_AddNumberToObject(item, "judge_seed", eval_reproducibility->judge_seed) == NULL) {
    goto fail; //Numeric
    }
    }


    // eval_reproducibility->normalizer_version
    if (!eval_reproducibility->normalizer_version) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "normalizer_version", eval_reproducibility->normalizer_version) == NULL) {
    goto fail; //String
    }


    // eval_reproducibility->prompt_version_id
    if(eval_reproducibility->prompt_version_id) {
    if(cJSON_AddStringToObject(item, "prompt_version_id", eval_reproducibility->prompt_version_id) == NULL) {
    goto fail; //String
    }
    }


    // eval_reproducibility->trace_schema_version
    if (!eval_reproducibility->trace_schema_version) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "trace_schema_version", eval_reproducibility->trace_schema_version) == NULL) {
    goto fail; //Numeric
    }


    // eval_reproducibility->wasi_abi_version
    if(eval_reproducibility->wasi_abi_version) {
    if(cJSON_AddStringToObject(item, "wasi_abi_version", eval_reproducibility->wasi_abi_version) == NULL) {
    goto fail; //String
    }
    }


    // eval_reproducibility->wasm_hash
    if(eval_reproducibility->wasm_hash) {
    if(cJSON_AddStringToObject(item, "wasm_hash", eval_reproducibility->wasm_hash) == NULL) {
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

eval_reproducibility_t *eval_reproducibility_parseFromJSON(cJSON *eval_reproducibilityJSON){

    eval_reproducibility_t *eval_reproducibility_local_var = NULL;

    // define the local list for eval_reproducibility->input_artifact_hashes
    list_t *input_artifact_hashesList = NULL;

    // define the local variable for eval_reproducibility->judge_parameters
    _t *judge_parameters_local_nonprim = NULL;

    // eval_reproducibility->agent_release_id
    cJSON *agent_release_id = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "agent_release_id");
    if (cJSON_IsNull(agent_release_id)) {
        agent_release_id = NULL;
    }
    if (!agent_release_id) {
        goto end;
    }

    
    if(!cJSON_IsString(agent_release_id))
    {
    goto end; //String
    }

    // eval_reproducibility->code_hash
    cJSON *code_hash = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "code_hash");
    if (cJSON_IsNull(code_hash)) {
        code_hash = NULL;
    }
    if (code_hash) { 
    if(!cJSON_IsString(code_hash) && !cJSON_IsNull(code_hash))
    {
    goto end; //String
    }
    }

    // eval_reproducibility->dataset_case_id
    cJSON *dataset_case_id = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "dataset_case_id");
    if (cJSON_IsNull(dataset_case_id)) {
        dataset_case_id = NULL;
    }
    if (!dataset_case_id) {
        goto end;
    }

    
    if(!cJSON_IsString(dataset_case_id))
    {
    goto end; //String
    }

    // eval_reproducibility->dataset_version_id
    cJSON *dataset_version_id = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "dataset_version_id");
    if (cJSON_IsNull(dataset_version_id)) {
        dataset_version_id = NULL;
    }
    if (!dataset_version_id) {
        goto end;
    }

    
    if(!cJSON_IsString(dataset_version_id))
    {
    goto end; //String
    }

    // eval_reproducibility->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "evaluator_version_id");
    if (cJSON_IsNull(evaluator_version_id)) {
        evaluator_version_id = NULL;
    }
    if (!evaluator_version_id) {
        goto end;
    }

    
    if(!cJSON_IsString(evaluator_version_id))
    {
    goto end; //String
    }

    // eval_reproducibility->input_artifact_hashes
    cJSON *input_artifact_hashes = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "input_artifact_hashes");
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

    // eval_reproducibility->judge_model_id
    cJSON *judge_model_id = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "judge_model_id");
    if (cJSON_IsNull(judge_model_id)) {
        judge_model_id = NULL;
    }
    if (judge_model_id) { 
    if(!cJSON_IsString(judge_model_id) && !cJSON_IsNull(judge_model_id))
    {
    goto end; //String
    }
    }

    // eval_reproducibility->judge_parameters
    cJSON *judge_parameters = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "judge_parameters");
    if (cJSON_IsNull(judge_parameters)) {
        judge_parameters = NULL;
    }
    if (!judge_parameters) {
        goto end;
    }

    
    judge_parameters_local_nonprim = _parseFromJSON(judge_parameters); //custom

    // eval_reproducibility->judge_provider
    cJSON *judge_provider = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "judge_provider");
    if (cJSON_IsNull(judge_provider)) {
        judge_provider = NULL;
    }
    if (judge_provider) { 
    if(!cJSON_IsString(judge_provider) && !cJSON_IsNull(judge_provider))
    {
    goto end; //String
    }
    }

    // eval_reproducibility->judge_rubric_version
    cJSON *judge_rubric_version = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "judge_rubric_version");
    if (cJSON_IsNull(judge_rubric_version)) {
        judge_rubric_version = NULL;
    }
    if (judge_rubric_version) { 
    if(!cJSON_IsString(judge_rubric_version) && !cJSON_IsNull(judge_rubric_version))
    {
    goto end; //String
    }
    }

    // eval_reproducibility->judge_seed
    cJSON *judge_seed = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "judge_seed");
    if (cJSON_IsNull(judge_seed)) {
        judge_seed = NULL;
    }
    if (judge_seed) { 
    if(!cJSON_IsNumber(judge_seed))
    {
    goto end; //Numeric
    }
    }

    // eval_reproducibility->normalizer_version
    cJSON *normalizer_version = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "normalizer_version");
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

    // eval_reproducibility->prompt_version_id
    cJSON *prompt_version_id = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "prompt_version_id");
    if (cJSON_IsNull(prompt_version_id)) {
        prompt_version_id = NULL;
    }
    if (prompt_version_id) { 
    if(!cJSON_IsString(prompt_version_id) && !cJSON_IsNull(prompt_version_id))
    {
    goto end; //String
    }
    }

    // eval_reproducibility->trace_schema_version
    cJSON *trace_schema_version = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "trace_schema_version");
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

    // eval_reproducibility->wasi_abi_version
    cJSON *wasi_abi_version = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "wasi_abi_version");
    if (cJSON_IsNull(wasi_abi_version)) {
        wasi_abi_version = NULL;
    }
    if (wasi_abi_version) { 
    if(!cJSON_IsString(wasi_abi_version) && !cJSON_IsNull(wasi_abi_version))
    {
    goto end; //String
    }
    }

    // eval_reproducibility->wasm_hash
    cJSON *wasm_hash = cJSON_GetObjectItemCaseSensitive(eval_reproducibilityJSON, "wasm_hash");
    if (cJSON_IsNull(wasm_hash)) {
        wasm_hash = NULL;
    }
    if (wasm_hash) { 
    if(!cJSON_IsString(wasm_hash) && !cJSON_IsNull(wasm_hash))
    {
    goto end; //String
    }
    }


    eval_reproducibility_local_var = eval_reproducibility_create_internal (
        strdup(agent_release_id->valuestring),
        code_hash && !cJSON_IsNull(code_hash) ? strdup(code_hash->valuestring) : NULL,
        strdup(dataset_case_id->valuestring),
        strdup(dataset_version_id->valuestring),
        strdup(evaluator_version_id->valuestring),
        input_artifact_hashesList,
        judge_model_id && !cJSON_IsNull(judge_model_id) ? strdup(judge_model_id->valuestring) : NULL,
        judge_parameters_local_nonprim,
        judge_provider && !cJSON_IsNull(judge_provider) ? strdup(judge_provider->valuestring) : NULL,
        judge_rubric_version && !cJSON_IsNull(judge_rubric_version) ? strdup(judge_rubric_version->valuestring) : NULL,
        judge_seed ? judge_seed->valuedouble : 0,
        strdup(normalizer_version->valuestring),
        prompt_version_id && !cJSON_IsNull(prompt_version_id) ? strdup(prompt_version_id->valuestring) : NULL,
        trace_schema_version->valuedouble,
        wasi_abi_version && !cJSON_IsNull(wasi_abi_version) ? strdup(wasi_abi_version->valuestring) : NULL,
        wasm_hash && !cJSON_IsNull(wasm_hash) ? strdup(wasm_hash->valuestring) : NULL
        );

    return eval_reproducibility_local_var;
end:
    if (input_artifact_hashesList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, input_artifact_hashesList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(input_artifact_hashesList);
        input_artifact_hashesList = NULL;
    }
    if (judge_parameters_local_nonprim) {
        _free(judge_parameters_local_nonprim);
        judge_parameters_local_nonprim = NULL;
    }
    return NULL;

}
