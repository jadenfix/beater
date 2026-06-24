#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "run_deterministic_eval_request.h"



static run_deterministic_eval_request_t *run_deterministic_eval_request_create_internal(
    char *agent_release_id,
    char *code_hash,
    char *evaluator_id,
    char *evaluator_version_id,
    evaluator_kind_t *kind,
    char *prompt_version_id,
    char *wasm_hash
    ) {
    run_deterministic_eval_request_t *run_deterministic_eval_request_local_var = malloc(sizeof(run_deterministic_eval_request_t));
    if (!run_deterministic_eval_request_local_var) {
        return NULL;
    }
    run_deterministic_eval_request_local_var->agent_release_id = agent_release_id;
    run_deterministic_eval_request_local_var->code_hash = code_hash;
    run_deterministic_eval_request_local_var->evaluator_id = evaluator_id;
    run_deterministic_eval_request_local_var->evaluator_version_id = evaluator_version_id;
    run_deterministic_eval_request_local_var->kind = kind;
    run_deterministic_eval_request_local_var->prompt_version_id = prompt_version_id;
    run_deterministic_eval_request_local_var->wasm_hash = wasm_hash;

    run_deterministic_eval_request_local_var->_library_owned = 1;
    return run_deterministic_eval_request_local_var;
}

__attribute__((deprecated)) run_deterministic_eval_request_t *run_deterministic_eval_request_create(
    char *agent_release_id,
    char *code_hash,
    char *evaluator_id,
    char *evaluator_version_id,
    evaluator_kind_t *kind,
    char *prompt_version_id,
    char *wasm_hash
    ) {
    return run_deterministic_eval_request_create_internal (
        agent_release_id,
        code_hash,
        evaluator_id,
        evaluator_version_id,
        kind,
        prompt_version_id,
        wasm_hash
        );
}

void run_deterministic_eval_request_free(run_deterministic_eval_request_t *run_deterministic_eval_request) {
    if(NULL == run_deterministic_eval_request){
        return ;
    }
    if(run_deterministic_eval_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "run_deterministic_eval_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (run_deterministic_eval_request->agent_release_id) {
        free(run_deterministic_eval_request->agent_release_id);
        run_deterministic_eval_request->agent_release_id = NULL;
    }
    if (run_deterministic_eval_request->code_hash) {
        free(run_deterministic_eval_request->code_hash);
        run_deterministic_eval_request->code_hash = NULL;
    }
    if (run_deterministic_eval_request->evaluator_id) {
        free(run_deterministic_eval_request->evaluator_id);
        run_deterministic_eval_request->evaluator_id = NULL;
    }
    if (run_deterministic_eval_request->evaluator_version_id) {
        free(run_deterministic_eval_request->evaluator_version_id);
        run_deterministic_eval_request->evaluator_version_id = NULL;
    }
    if (run_deterministic_eval_request->kind) {
        evaluator_kind_free(run_deterministic_eval_request->kind);
        run_deterministic_eval_request->kind = NULL;
    }
    if (run_deterministic_eval_request->prompt_version_id) {
        free(run_deterministic_eval_request->prompt_version_id);
        run_deterministic_eval_request->prompt_version_id = NULL;
    }
    if (run_deterministic_eval_request->wasm_hash) {
        free(run_deterministic_eval_request->wasm_hash);
        run_deterministic_eval_request->wasm_hash = NULL;
    }
    free(run_deterministic_eval_request);
}

cJSON *run_deterministic_eval_request_convertToJSON(run_deterministic_eval_request_t *run_deterministic_eval_request) {
    cJSON *item = cJSON_CreateObject();

    // run_deterministic_eval_request->agent_release_id
    if (!run_deterministic_eval_request->agent_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "agent_release_id", run_deterministic_eval_request->agent_release_id) == NULL) {
    goto fail; //String
    }


    // run_deterministic_eval_request->code_hash
    if(run_deterministic_eval_request->code_hash) {
    if(cJSON_AddStringToObject(item, "code_hash", run_deterministic_eval_request->code_hash) == NULL) {
    goto fail; //String
    }
    }


    // run_deterministic_eval_request->evaluator_id
    if (!run_deterministic_eval_request->evaluator_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_id", run_deterministic_eval_request->evaluator_id) == NULL) {
    goto fail; //String
    }


    // run_deterministic_eval_request->evaluator_version_id
    if (!run_deterministic_eval_request->evaluator_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_version_id", run_deterministic_eval_request->evaluator_version_id) == NULL) {
    goto fail; //String
    }


    // run_deterministic_eval_request->kind
    if (!run_deterministic_eval_request->kind) {
        goto fail;
    }
    cJSON *kind_local_JSON = evaluator_kind_convertToJSON(run_deterministic_eval_request->kind);
    if(kind_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "kind", kind_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // run_deterministic_eval_request->prompt_version_id
    if(run_deterministic_eval_request->prompt_version_id) {
    if(cJSON_AddStringToObject(item, "prompt_version_id", run_deterministic_eval_request->prompt_version_id) == NULL) {
    goto fail; //String
    }
    }


    // run_deterministic_eval_request->wasm_hash
    if(run_deterministic_eval_request->wasm_hash) {
    if(cJSON_AddStringToObject(item, "wasm_hash", run_deterministic_eval_request->wasm_hash) == NULL) {
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

run_deterministic_eval_request_t *run_deterministic_eval_request_parseFromJSON(cJSON *run_deterministic_eval_requestJSON){

    run_deterministic_eval_request_t *run_deterministic_eval_request_local_var = NULL;

    // define the local variable for run_deterministic_eval_request->kind
    evaluator_kind_t *kind_local_nonprim = NULL;

    // run_deterministic_eval_request->agent_release_id
    cJSON *agent_release_id = cJSON_GetObjectItemCaseSensitive(run_deterministic_eval_requestJSON, "agent_release_id");
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

    // run_deterministic_eval_request->code_hash
    cJSON *code_hash = cJSON_GetObjectItemCaseSensitive(run_deterministic_eval_requestJSON, "code_hash");
    if (cJSON_IsNull(code_hash)) {
        code_hash = NULL;
    }
    if (code_hash) { 
    if(!cJSON_IsString(code_hash) && !cJSON_IsNull(code_hash))
    {
    goto end; //String
    }
    }

    // run_deterministic_eval_request->evaluator_id
    cJSON *evaluator_id = cJSON_GetObjectItemCaseSensitive(run_deterministic_eval_requestJSON, "evaluator_id");
    if (cJSON_IsNull(evaluator_id)) {
        evaluator_id = NULL;
    }
    if (!evaluator_id) {
        goto end;
    }

    
    if(!cJSON_IsString(evaluator_id))
    {
    goto end; //String
    }

    // run_deterministic_eval_request->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(run_deterministic_eval_requestJSON, "evaluator_version_id");
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

    // run_deterministic_eval_request->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(run_deterministic_eval_requestJSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    
    kind_local_nonprim = evaluator_kind_parseFromJSON(kind); //nonprimitive

    // run_deterministic_eval_request->prompt_version_id
    cJSON *prompt_version_id = cJSON_GetObjectItemCaseSensitive(run_deterministic_eval_requestJSON, "prompt_version_id");
    if (cJSON_IsNull(prompt_version_id)) {
        prompt_version_id = NULL;
    }
    if (prompt_version_id) { 
    if(!cJSON_IsString(prompt_version_id) && !cJSON_IsNull(prompt_version_id))
    {
    goto end; //String
    }
    }

    // run_deterministic_eval_request->wasm_hash
    cJSON *wasm_hash = cJSON_GetObjectItemCaseSensitive(run_deterministic_eval_requestJSON, "wasm_hash");
    if (cJSON_IsNull(wasm_hash)) {
        wasm_hash = NULL;
    }
    if (wasm_hash) { 
    if(!cJSON_IsString(wasm_hash) && !cJSON_IsNull(wasm_hash))
    {
    goto end; //String
    }
    }


    run_deterministic_eval_request_local_var = run_deterministic_eval_request_create_internal (
        strdup(agent_release_id->valuestring),
        code_hash && !cJSON_IsNull(code_hash) ? strdup(code_hash->valuestring) : NULL,
        strdup(evaluator_id->valuestring),
        strdup(evaluator_version_id->valuestring),
        kind_local_nonprim,
        prompt_version_id && !cJSON_IsNull(prompt_version_id) ? strdup(prompt_version_id->valuestring) : NULL,
        wasm_hash && !cJSON_IsNull(wasm_hash) ? strdup(wasm_hash->valuestring) : NULL
        );

    return run_deterministic_eval_request_local_var;
end:
    if (kind_local_nonprim) {
        evaluator_kind_free(kind_local_nonprim);
        kind_local_nonprim = NULL;
    }
    return NULL;

}
