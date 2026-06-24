#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "run_experiment_request.h"



static run_experiment_request_t *run_experiment_request_create_internal(
    list_t *baseline_outputs,
    char *baseline_release_id,
    list_t *candidate_outputs,
    char *candidate_release_id,
    char *evaluator_id,
    char *evaluator_version_id,
    gate_policy_t *gate_policy,
    evaluator_kind_t *kind
    ) {
    run_experiment_request_t *run_experiment_request_local_var = malloc(sizeof(run_experiment_request_t));
    if (!run_experiment_request_local_var) {
        return NULL;
    }
    run_experiment_request_local_var->baseline_outputs = baseline_outputs;
    run_experiment_request_local_var->baseline_release_id = baseline_release_id;
    run_experiment_request_local_var->candidate_outputs = candidate_outputs;
    run_experiment_request_local_var->candidate_release_id = candidate_release_id;
    run_experiment_request_local_var->evaluator_id = evaluator_id;
    run_experiment_request_local_var->evaluator_version_id = evaluator_version_id;
    run_experiment_request_local_var->gate_policy = gate_policy;
    run_experiment_request_local_var->kind = kind;

    run_experiment_request_local_var->_library_owned = 1;
    return run_experiment_request_local_var;
}

__attribute__((deprecated)) run_experiment_request_t *run_experiment_request_create(
    list_t *baseline_outputs,
    char *baseline_release_id,
    list_t *candidate_outputs,
    char *candidate_release_id,
    char *evaluator_id,
    char *evaluator_version_id,
    gate_policy_t *gate_policy,
    evaluator_kind_t *kind
    ) {
    return run_experiment_request_create_internal (
        baseline_outputs,
        baseline_release_id,
        candidate_outputs,
        candidate_release_id,
        evaluator_id,
        evaluator_version_id,
        gate_policy,
        kind
        );
}

void run_experiment_request_free(run_experiment_request_t *run_experiment_request) {
    if(NULL == run_experiment_request){
        return ;
    }
    if(run_experiment_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "run_experiment_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (run_experiment_request->baseline_outputs) {
        list_ForEach(listEntry, run_experiment_request->baseline_outputs) {
            case_output_override_request_free(listEntry->data);
        }
        list_freeList(run_experiment_request->baseline_outputs);
        run_experiment_request->baseline_outputs = NULL;
    }
    if (run_experiment_request->baseline_release_id) {
        free(run_experiment_request->baseline_release_id);
        run_experiment_request->baseline_release_id = NULL;
    }
    if (run_experiment_request->candidate_outputs) {
        list_ForEach(listEntry, run_experiment_request->candidate_outputs) {
            case_output_override_request_free(listEntry->data);
        }
        list_freeList(run_experiment_request->candidate_outputs);
        run_experiment_request->candidate_outputs = NULL;
    }
    if (run_experiment_request->candidate_release_id) {
        free(run_experiment_request->candidate_release_id);
        run_experiment_request->candidate_release_id = NULL;
    }
    if (run_experiment_request->evaluator_id) {
        free(run_experiment_request->evaluator_id);
        run_experiment_request->evaluator_id = NULL;
    }
    if (run_experiment_request->evaluator_version_id) {
        free(run_experiment_request->evaluator_version_id);
        run_experiment_request->evaluator_version_id = NULL;
    }
    if (run_experiment_request->gate_policy) {
        gate_policy_free(run_experiment_request->gate_policy);
        run_experiment_request->gate_policy = NULL;
    }
    if (run_experiment_request->kind) {
        evaluator_kind_free(run_experiment_request->kind);
        run_experiment_request->kind = NULL;
    }
    free(run_experiment_request);
}

cJSON *run_experiment_request_convertToJSON(run_experiment_request_t *run_experiment_request) {
    cJSON *item = cJSON_CreateObject();

    // run_experiment_request->baseline_outputs
    if (!run_experiment_request->baseline_outputs) {
        goto fail;
    }
    cJSON *baseline_outputs = cJSON_AddArrayToObject(item, "baseline_outputs");
    if(baseline_outputs == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *baseline_outputsListEntry;
    if (run_experiment_request->baseline_outputs) {
    list_ForEach(baseline_outputsListEntry, run_experiment_request->baseline_outputs) {
    cJSON *itemLocal = case_output_override_request_convertToJSON(baseline_outputsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(baseline_outputs, itemLocal);
    }
    }


    // run_experiment_request->baseline_release_id
    if (!run_experiment_request->baseline_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "baseline_release_id", run_experiment_request->baseline_release_id) == NULL) {
    goto fail; //String
    }


    // run_experiment_request->candidate_outputs
    if (!run_experiment_request->candidate_outputs) {
        goto fail;
    }
    cJSON *candidate_outputs = cJSON_AddArrayToObject(item, "candidate_outputs");
    if(candidate_outputs == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *candidate_outputsListEntry;
    if (run_experiment_request->candidate_outputs) {
    list_ForEach(candidate_outputsListEntry, run_experiment_request->candidate_outputs) {
    cJSON *itemLocal = case_output_override_request_convertToJSON(candidate_outputsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(candidate_outputs, itemLocal);
    }
    }


    // run_experiment_request->candidate_release_id
    if (!run_experiment_request->candidate_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "candidate_release_id", run_experiment_request->candidate_release_id) == NULL) {
    goto fail; //String
    }


    // run_experiment_request->evaluator_id
    if (!run_experiment_request->evaluator_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_id", run_experiment_request->evaluator_id) == NULL) {
    goto fail; //String
    }


    // run_experiment_request->evaluator_version_id
    if (!run_experiment_request->evaluator_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_version_id", run_experiment_request->evaluator_version_id) == NULL) {
    goto fail; //String
    }


    // run_experiment_request->gate_policy
    if(run_experiment_request->gate_policy) {
    cJSON *gate_policy_local_JSON = gate_policy_convertToJSON(run_experiment_request->gate_policy);
    if(gate_policy_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "gate_policy", gate_policy_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // run_experiment_request->kind
    if (!run_experiment_request->kind) {
        goto fail;
    }
    cJSON *kind_local_JSON = evaluator_kind_convertToJSON(run_experiment_request->kind);
    if(kind_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "kind", kind_local_JSON);
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

run_experiment_request_t *run_experiment_request_parseFromJSON(cJSON *run_experiment_requestJSON){

    run_experiment_request_t *run_experiment_request_local_var = NULL;

    // define the local list for run_experiment_request->baseline_outputs
    list_t *baseline_outputsList = NULL;

    // define the local list for run_experiment_request->candidate_outputs
    list_t *candidate_outputsList = NULL;

    // define the local variable for run_experiment_request->gate_policy
    gate_policy_t *gate_policy_local_nonprim = NULL;

    // define the local variable for run_experiment_request->kind
    evaluator_kind_t *kind_local_nonprim = NULL;

    // run_experiment_request->baseline_outputs
    cJSON *baseline_outputs = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "baseline_outputs");
    if (cJSON_IsNull(baseline_outputs)) {
        baseline_outputs = NULL;
    }
    if (!baseline_outputs) {
        goto end;
    }

    
    cJSON *baseline_outputs_local_nonprimitive = NULL;
    if(!cJSON_IsArray(baseline_outputs)){
        goto end; //nonprimitive container
    }

    baseline_outputsList = list_createList();

    cJSON_ArrayForEach(baseline_outputs_local_nonprimitive,baseline_outputs )
    {
        if(!cJSON_IsObject(baseline_outputs_local_nonprimitive)){
            goto end;
        }
        case_output_override_request_t *baseline_outputsItem = case_output_override_request_parseFromJSON(baseline_outputs_local_nonprimitive);

        list_addElement(baseline_outputsList, baseline_outputsItem);
    }

    // run_experiment_request->baseline_release_id
    cJSON *baseline_release_id = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "baseline_release_id");
    if (cJSON_IsNull(baseline_release_id)) {
        baseline_release_id = NULL;
    }
    if (!baseline_release_id) {
        goto end;
    }

    
    if(!cJSON_IsString(baseline_release_id))
    {
    goto end; //String
    }

    // run_experiment_request->candidate_outputs
    cJSON *candidate_outputs = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "candidate_outputs");
    if (cJSON_IsNull(candidate_outputs)) {
        candidate_outputs = NULL;
    }
    if (!candidate_outputs) {
        goto end;
    }

    
    cJSON *candidate_outputs_local_nonprimitive = NULL;
    if(!cJSON_IsArray(candidate_outputs)){
        goto end; //nonprimitive container
    }

    candidate_outputsList = list_createList();

    cJSON_ArrayForEach(candidate_outputs_local_nonprimitive,candidate_outputs )
    {
        if(!cJSON_IsObject(candidate_outputs_local_nonprimitive)){
            goto end;
        }
        case_output_override_request_t *candidate_outputsItem = case_output_override_request_parseFromJSON(candidate_outputs_local_nonprimitive);

        list_addElement(candidate_outputsList, candidate_outputsItem);
    }

    // run_experiment_request->candidate_release_id
    cJSON *candidate_release_id = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "candidate_release_id");
    if (cJSON_IsNull(candidate_release_id)) {
        candidate_release_id = NULL;
    }
    if (!candidate_release_id) {
        goto end;
    }

    
    if(!cJSON_IsString(candidate_release_id))
    {
    goto end; //String
    }

    // run_experiment_request->evaluator_id
    cJSON *evaluator_id = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "evaluator_id");
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

    // run_experiment_request->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "evaluator_version_id");
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

    // run_experiment_request->gate_policy
    cJSON *gate_policy = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "gate_policy");
    if (cJSON_IsNull(gate_policy)) {
        gate_policy = NULL;
    }
    if (gate_policy) { 
    gate_policy_local_nonprim = gate_policy_parseFromJSON(gate_policy); //nonprimitive
    }

    // run_experiment_request->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(run_experiment_requestJSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    
    kind_local_nonprim = evaluator_kind_parseFromJSON(kind); //nonprimitive


    run_experiment_request_local_var = run_experiment_request_create_internal (
        baseline_outputsList,
        strdup(baseline_release_id->valuestring),
        candidate_outputsList,
        strdup(candidate_release_id->valuestring),
        strdup(evaluator_id->valuestring),
        strdup(evaluator_version_id->valuestring),
        gate_policy ? gate_policy_local_nonprim : NULL,
        kind_local_nonprim
        );

    return run_experiment_request_local_var;
end:
    if (baseline_outputsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, baseline_outputsList) {
            case_output_override_request_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(baseline_outputsList);
        baseline_outputsList = NULL;
    }
    if (candidate_outputsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, candidate_outputsList) {
            case_output_override_request_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(candidate_outputsList);
        candidate_outputsList = NULL;
    }
    if (gate_policy_local_nonprim) {
        gate_policy_free(gate_policy_local_nonprim);
        gate_policy_local_nonprim = NULL;
    }
    if (kind_local_nonprim) {
        evaluator_kind_free(kind_local_nonprim);
        kind_local_nonprim = NULL;
    }
    return NULL;

}
