#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sampling_decision.h"



static sampling_decision_t *sampling_decision_create_internal(
    beater_api_sampling_reason__e reason,
    int selected,
    int stable_score_per_mille
    ) {
    sampling_decision_t *sampling_decision_local_var = malloc(sizeof(sampling_decision_t));
    if (!sampling_decision_local_var) {
        return NULL;
    }
    sampling_decision_local_var->reason = reason;
    sampling_decision_local_var->selected = selected;
    sampling_decision_local_var->stable_score_per_mille = stable_score_per_mille;

    sampling_decision_local_var->_library_owned = 1;
    return sampling_decision_local_var;
}

__attribute__((deprecated)) sampling_decision_t *sampling_decision_create(
    beater_api_sampling_reason__e reason,
    int selected,
    int stable_score_per_mille
    ) {
    return sampling_decision_create_internal (
        reason,
        selected,
        stable_score_per_mille
        );
}

void sampling_decision_free(sampling_decision_t *sampling_decision) {
    if(NULL == sampling_decision){
        return ;
    }
    if(sampling_decision->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "sampling_decision_free");
        return ;
    }
    listEntry_t *listEntry;
    free(sampling_decision);
}

cJSON *sampling_decision_convertToJSON(sampling_decision_t *sampling_decision) {
    cJSON *item = cJSON_CreateObject();

    // sampling_decision->reason
    if (beater_api_sampling_reason__NULL == sampling_decision->reason) {
        goto fail;
    }
    cJSON *reason_local_JSON = sampling_reason_convertToJSON(sampling_decision->reason);
    if(reason_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "reason", reason_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // sampling_decision->selected
    if (!sampling_decision->selected) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "selected", sampling_decision->selected) == NULL) {
    goto fail; //Bool
    }


    // sampling_decision->stable_score_per_mille
    if (!sampling_decision->stable_score_per_mille) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "stable_score_per_mille", sampling_decision->stable_score_per_mille) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

sampling_decision_t *sampling_decision_parseFromJSON(cJSON *sampling_decisionJSON){

    sampling_decision_t *sampling_decision_local_var = NULL;

    // define the local variable for sampling_decision->reason
    beater_api_sampling_reason__e reason_local_nonprim = 0;

    // sampling_decision->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(sampling_decisionJSON, "reason");
    if (cJSON_IsNull(reason)) {
        reason = NULL;
    }
    if (!reason) {
        goto end;
    }

    
    reason_local_nonprim = sampling_reason_parseFromJSON(reason); //custom

    // sampling_decision->selected
    cJSON *selected = cJSON_GetObjectItemCaseSensitive(sampling_decisionJSON, "selected");
    if (cJSON_IsNull(selected)) {
        selected = NULL;
    }
    if (!selected) {
        goto end;
    }

    
    if(!cJSON_IsBool(selected))
    {
    goto end; //Bool
    }

    // sampling_decision->stable_score_per_mille
    cJSON *stable_score_per_mille = cJSON_GetObjectItemCaseSensitive(sampling_decisionJSON, "stable_score_per_mille");
    if (cJSON_IsNull(stable_score_per_mille)) {
        stable_score_per_mille = NULL;
    }
    if (!stable_score_per_mille) {
        goto end;
    }

    
    if(!cJSON_IsNumber(stable_score_per_mille))
    {
    goto end; //Numeric
    }


    sampling_decision_local_var = sampling_decision_create_internal (
        reason_local_nonprim,
        selected->valueint,
        stable_score_per_mille->valuedouble
        );

    return sampling_decision_local_var;
end:
    if (reason_local_nonprim) {
        reason_local_nonprim = 0;
    }
    return NULL;

}
