#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_case_score_request.h"



static gate_case_score_request_t *gate_case_score_request_create_internal(
    double baseline_score,
    double candidate_score,
    beater_api_split__e split
    ) {
    gate_case_score_request_t *gate_case_score_request_local_var = malloc(sizeof(gate_case_score_request_t));
    if (!gate_case_score_request_local_var) {
        return NULL;
    }
    gate_case_score_request_local_var->baseline_score = baseline_score;
    gate_case_score_request_local_var->candidate_score = candidate_score;
    gate_case_score_request_local_var->split = split;

    gate_case_score_request_local_var->_library_owned = 1;
    return gate_case_score_request_local_var;
}

__attribute__((deprecated)) gate_case_score_request_t *gate_case_score_request_create(
    double baseline_score,
    double candidate_score,
    beater_api_split__e split
    ) {
    return gate_case_score_request_create_internal (
        baseline_score,
        candidate_score,
        split
        );
}

void gate_case_score_request_free(gate_case_score_request_t *gate_case_score_request) {
    if(NULL == gate_case_score_request){
        return ;
    }
    if(gate_case_score_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_case_score_request_free");
        return ;
    }
    listEntry_t *listEntry;
    free(gate_case_score_request);
}

cJSON *gate_case_score_request_convertToJSON(gate_case_score_request_t *gate_case_score_request) {
    cJSON *item = cJSON_CreateObject();

    // gate_case_score_request->baseline_score
    if (!gate_case_score_request->baseline_score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "baseline_score", gate_case_score_request->baseline_score) == NULL) {
    goto fail; //Numeric
    }


    // gate_case_score_request->candidate_score
    if (!gate_case_score_request->candidate_score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "candidate_score", gate_case_score_request->candidate_score) == NULL) {
    goto fail; //Numeric
    }


    // gate_case_score_request->split
    if (beater_api_split__NULL == gate_case_score_request->split) {
        goto fail;
    }
    cJSON *split_local_JSON = split_convertToJSON(gate_case_score_request->split);
    if(split_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "split", split_local_JSON);
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

gate_case_score_request_t *gate_case_score_request_parseFromJSON(cJSON *gate_case_score_requestJSON){

    gate_case_score_request_t *gate_case_score_request_local_var = NULL;

    // define the local variable for gate_case_score_request->split
    beater_api_split__e split_local_nonprim = 0;

    // gate_case_score_request->baseline_score
    cJSON *baseline_score = cJSON_GetObjectItemCaseSensitive(gate_case_score_requestJSON, "baseline_score");
    if (cJSON_IsNull(baseline_score)) {
        baseline_score = NULL;
    }
    if (!baseline_score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(baseline_score))
    {
    goto end; //Numeric
    }

    // gate_case_score_request->candidate_score
    cJSON *candidate_score = cJSON_GetObjectItemCaseSensitive(gate_case_score_requestJSON, "candidate_score");
    if (cJSON_IsNull(candidate_score)) {
        candidate_score = NULL;
    }
    if (!candidate_score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(candidate_score))
    {
    goto end; //Numeric
    }

    // gate_case_score_request->split
    cJSON *split = cJSON_GetObjectItemCaseSensitive(gate_case_score_requestJSON, "split");
    if (cJSON_IsNull(split)) {
        split = NULL;
    }
    if (!split) {
        goto end;
    }

    
    split_local_nonprim = split_parseFromJSON(split); //custom


    gate_case_score_request_local_var = gate_case_score_request_create_internal (
        baseline_score->valuedouble,
        candidate_score->valuedouble,
        split_local_nonprim
        );

    return gate_case_score_request_local_var;
end:
    if (split_local_nonprim) {
        split_local_nonprim = 0;
    }
    return NULL;

}
