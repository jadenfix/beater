#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_candidate_request.h"



static gate_candidate_request_t *gate_candidate_request_create_internal(
    gate_candidate_change_request_t *candidate,
    gate_policy_t *gate_policy,
    double overfit_confidence,
    int overfit_resamples,
    long overfit_seed,
    double overfit_tolerance,
    list_t *scores
    ) {
    gate_candidate_request_t *gate_candidate_request_local_var = malloc(sizeof(gate_candidate_request_t));
    if (!gate_candidate_request_local_var) {
        return NULL;
    }
    gate_candidate_request_local_var->candidate = candidate;
    gate_candidate_request_local_var->gate_policy = gate_policy;
    gate_candidate_request_local_var->overfit_confidence = overfit_confidence;
    gate_candidate_request_local_var->overfit_resamples = overfit_resamples;
    gate_candidate_request_local_var->overfit_seed = overfit_seed;
    gate_candidate_request_local_var->overfit_tolerance = overfit_tolerance;
    gate_candidate_request_local_var->scores = scores;

    gate_candidate_request_local_var->_library_owned = 1;
    return gate_candidate_request_local_var;
}

__attribute__((deprecated)) gate_candidate_request_t *gate_candidate_request_create(
    gate_candidate_change_request_t *candidate,
    gate_policy_t *gate_policy,
    double overfit_confidence,
    int overfit_resamples,
    long overfit_seed,
    double overfit_tolerance,
    list_t *scores
    ) {
    return gate_candidate_request_create_internal (
        candidate,
        gate_policy,
        overfit_confidence,
        overfit_resamples,
        overfit_seed,
        overfit_tolerance,
        scores
        );
}

void gate_candidate_request_free(gate_candidate_request_t *gate_candidate_request) {
    if(NULL == gate_candidate_request){
        return ;
    }
    if(gate_candidate_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_candidate_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (gate_candidate_request->candidate) {
        gate_candidate_change_request_free(gate_candidate_request->candidate);
        gate_candidate_request->candidate = NULL;
    }
    if (gate_candidate_request->gate_policy) {
        gate_policy_free(gate_candidate_request->gate_policy);
        gate_candidate_request->gate_policy = NULL;
    }
    if (gate_candidate_request->scores) {
        list_ForEach(listEntry, gate_candidate_request->scores) {
            gate_case_score_request_free(listEntry->data);
        }
        list_freeList(gate_candidate_request->scores);
        gate_candidate_request->scores = NULL;
    }
    free(gate_candidate_request);
}

cJSON *gate_candidate_request_convertToJSON(gate_candidate_request_t *gate_candidate_request) {
    cJSON *item = cJSON_CreateObject();

    // gate_candidate_request->candidate
    if (!gate_candidate_request->candidate) {
        goto fail;
    }
    cJSON *candidate_local_JSON = gate_candidate_change_request_convertToJSON(gate_candidate_request->candidate);
    if(candidate_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "candidate", candidate_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // gate_candidate_request->gate_policy
    if(gate_candidate_request->gate_policy) {
    cJSON *gate_policy_local_JSON = gate_policy_convertToJSON(gate_candidate_request->gate_policy);
    if(gate_policy_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "gate_policy", gate_policy_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // gate_candidate_request->overfit_confidence
    if(gate_candidate_request->overfit_confidence) {
    if(cJSON_AddNumberToObject(item, "overfit_confidence", gate_candidate_request->overfit_confidence) == NULL) {
    goto fail; //Numeric
    }
    }


    // gate_candidate_request->overfit_resamples
    if(gate_candidate_request->overfit_resamples) {
    if(cJSON_AddNumberToObject(item, "overfit_resamples", gate_candidate_request->overfit_resamples) == NULL) {
    goto fail; //Numeric
    }
    }


    // gate_candidate_request->overfit_seed
    if(gate_candidate_request->overfit_seed) {
    if(cJSON_AddNumberToObject(item, "overfit_seed", gate_candidate_request->overfit_seed) == NULL) {
    goto fail; //Numeric
    }
    }


    // gate_candidate_request->overfit_tolerance
    if(gate_candidate_request->overfit_tolerance) {
    if(cJSON_AddNumberToObject(item, "overfit_tolerance", gate_candidate_request->overfit_tolerance) == NULL) {
    goto fail; //Numeric
    }
    }


    // gate_candidate_request->scores
    if (!gate_candidate_request->scores) {
        goto fail;
    }
    cJSON *scores = cJSON_AddArrayToObject(item, "scores");
    if(scores == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *scoresListEntry;
    if (gate_candidate_request->scores) {
    list_ForEach(scoresListEntry, gate_candidate_request->scores) {
    cJSON *itemLocal = gate_case_score_request_convertToJSON(scoresListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(scores, itemLocal);
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

gate_candidate_request_t *gate_candidate_request_parseFromJSON(cJSON *gate_candidate_requestJSON){

    gate_candidate_request_t *gate_candidate_request_local_var = NULL;

    // define the local variable for gate_candidate_request->candidate
    gate_candidate_change_request_t *candidate_local_nonprim = NULL;

    // define the local variable for gate_candidate_request->gate_policy
    gate_policy_t *gate_policy_local_nonprim = NULL;

    // define the local list for gate_candidate_request->scores
    list_t *scoresList = NULL;

    // gate_candidate_request->candidate
    cJSON *candidate = cJSON_GetObjectItemCaseSensitive(gate_candidate_requestJSON, "candidate");
    if (cJSON_IsNull(candidate)) {
        candidate = NULL;
    }
    if (!candidate) {
        goto end;
    }

    
    candidate_local_nonprim = gate_candidate_change_request_parseFromJSON(candidate); //nonprimitive

    // gate_candidate_request->gate_policy
    cJSON *gate_policy = cJSON_GetObjectItemCaseSensitive(gate_candidate_requestJSON, "gate_policy");
    if (cJSON_IsNull(gate_policy)) {
        gate_policy = NULL;
    }
    if (gate_policy) { 
    gate_policy_local_nonprim = gate_policy_parseFromJSON(gate_policy); //nonprimitive
    }

    // gate_candidate_request->overfit_confidence
    cJSON *overfit_confidence = cJSON_GetObjectItemCaseSensitive(gate_candidate_requestJSON, "overfit_confidence");
    if (cJSON_IsNull(overfit_confidence)) {
        overfit_confidence = NULL;
    }
    if (overfit_confidence) { 
    if(!cJSON_IsNumber(overfit_confidence))
    {
    goto end; //Numeric
    }
    }

    // gate_candidate_request->overfit_resamples
    cJSON *overfit_resamples = cJSON_GetObjectItemCaseSensitive(gate_candidate_requestJSON, "overfit_resamples");
    if (cJSON_IsNull(overfit_resamples)) {
        overfit_resamples = NULL;
    }
    if (overfit_resamples) { 
    if(!cJSON_IsNumber(overfit_resamples))
    {
    goto end; //Numeric
    }
    }

    // gate_candidate_request->overfit_seed
    cJSON *overfit_seed = cJSON_GetObjectItemCaseSensitive(gate_candidate_requestJSON, "overfit_seed");
    if (cJSON_IsNull(overfit_seed)) {
        overfit_seed = NULL;
    }
    if (overfit_seed) { 
    if(!cJSON_IsNumber(overfit_seed))
    {
    goto end; //Numeric
    }
    }

    // gate_candidate_request->overfit_tolerance
    cJSON *overfit_tolerance = cJSON_GetObjectItemCaseSensitive(gate_candidate_requestJSON, "overfit_tolerance");
    if (cJSON_IsNull(overfit_tolerance)) {
        overfit_tolerance = NULL;
    }
    if (overfit_tolerance) { 
    if(!cJSON_IsNumber(overfit_tolerance))
    {
    goto end; //Numeric
    }
    }

    // gate_candidate_request->scores
    cJSON *scores = cJSON_GetObjectItemCaseSensitive(gate_candidate_requestJSON, "scores");
    if (cJSON_IsNull(scores)) {
        scores = NULL;
    }
    if (!scores) {
        goto end;
    }

    
    cJSON *scores_local_nonprimitive = NULL;
    if(!cJSON_IsArray(scores)){
        goto end; //nonprimitive container
    }

    scoresList = list_createList();

    cJSON_ArrayForEach(scores_local_nonprimitive,scores )
    {
        if(!cJSON_IsObject(scores_local_nonprimitive)){
            goto end;
        }
        gate_case_score_request_t *scoresItem = gate_case_score_request_parseFromJSON(scores_local_nonprimitive);

        list_addElement(scoresList, scoresItem);
    }


    gate_candidate_request_local_var = gate_candidate_request_create_internal (
        candidate_local_nonprim,
        gate_policy ? gate_policy_local_nonprim : NULL,
        overfit_confidence ? overfit_confidence->valuedouble : 0,
        overfit_resamples ? overfit_resamples->valuedouble : 0,
        overfit_seed ? overfit_seed->valuedouble : 0,
        overfit_tolerance ? overfit_tolerance->valuedouble : 0,
        scoresList
        );

    return gate_candidate_request_local_var;
end:
    if (candidate_local_nonprim) {
        gate_candidate_change_request_free(candidate_local_nonprim);
        candidate_local_nonprim = NULL;
    }
    if (gate_policy_local_nonprim) {
        gate_policy_free(gate_policy_local_nonprim);
        gate_policy_local_nonprim = NULL;
    }
    if (scoresList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, scoresList) {
            gate_case_score_request_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(scoresList);
        scoresList = NULL;
    }
    return NULL;

}
