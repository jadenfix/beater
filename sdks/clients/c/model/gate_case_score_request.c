#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_case_score_request.h"



static gate_case_score_request_t *gate_case_score_request_create_internal(
    double baseline_score,
    double candidate_score,
    char *split
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
    char *split
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
    if (gate_case_score_request->split) {
        free(gate_case_score_request->split);
        gate_case_score_request->split = NULL;
    }
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
    if (!gate_case_score_request->split) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "split", gate_case_score_request->split) == NULL) {
    goto fail; //String
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

    
    if(!cJSON_IsString(split))
    {
    goto end; //String
    }


    gate_case_score_request_local_var = gate_case_score_request_create_internal (
        baseline_score->valuedouble,
        candidate_score->valuedouble,
        strdup(split->valuestring)
        );

    return gate_case_score_request_local_var;
end:
    return NULL;

}
