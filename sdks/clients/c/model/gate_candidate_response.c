#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_candidate_response.h"



static gate_candidate_response_t *gate_candidate_response_create_internal(
    int accepted,
    gate_comparison_response_t *gate,
    overfit_response_t *overfit
    ) {
    gate_candidate_response_t *gate_candidate_response_local_var = malloc(sizeof(gate_candidate_response_t));
    if (!gate_candidate_response_local_var) {
        return NULL;
    }
    gate_candidate_response_local_var->accepted = accepted;
    gate_candidate_response_local_var->gate = gate;
    gate_candidate_response_local_var->overfit = overfit;

    gate_candidate_response_local_var->_library_owned = 1;
    return gate_candidate_response_local_var;
}

__attribute__((deprecated)) gate_candidate_response_t *gate_candidate_response_create(
    int accepted,
    gate_comparison_response_t *gate,
    overfit_response_t *overfit
    ) {
    return gate_candidate_response_create_internal (
        accepted,
        gate,
        overfit
        );
}

void gate_candidate_response_free(gate_candidate_response_t *gate_candidate_response) {
    if(NULL == gate_candidate_response){
        return ;
    }
    if(gate_candidate_response->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_candidate_response_free");
        return ;
    }
    listEntry_t *listEntry;
    if (gate_candidate_response->gate) {
        gate_comparison_response_free(gate_candidate_response->gate);
        gate_candidate_response->gate = NULL;
    }
    if (gate_candidate_response->overfit) {
        overfit_response_free(gate_candidate_response->overfit);
        gate_candidate_response->overfit = NULL;
    }
    free(gate_candidate_response);
}

cJSON *gate_candidate_response_convertToJSON(gate_candidate_response_t *gate_candidate_response) {
    cJSON *item = cJSON_CreateObject();

    // gate_candidate_response->accepted
    if (!gate_candidate_response->accepted) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "accepted", gate_candidate_response->accepted) == NULL) {
    goto fail; //Bool
    }


    // gate_candidate_response->gate
    if (!gate_candidate_response->gate) {
        goto fail;
    }
    cJSON *gate_local_JSON = gate_comparison_response_convertToJSON(gate_candidate_response->gate);
    if(gate_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "gate", gate_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // gate_candidate_response->overfit
    if (!gate_candidate_response->overfit) {
        goto fail;
    }
    cJSON *overfit_local_JSON = overfit_response_convertToJSON(gate_candidate_response->overfit);
    if(overfit_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "overfit", overfit_local_JSON);
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

gate_candidate_response_t *gate_candidate_response_parseFromJSON(cJSON *gate_candidate_responseJSON){

    gate_candidate_response_t *gate_candidate_response_local_var = NULL;

    // define the local variable for gate_candidate_response->gate
    gate_comparison_response_t *gate_local_nonprim = NULL;

    // define the local variable for gate_candidate_response->overfit
    overfit_response_t *overfit_local_nonprim = NULL;

    // gate_candidate_response->accepted
    cJSON *accepted = cJSON_GetObjectItemCaseSensitive(gate_candidate_responseJSON, "accepted");
    if (cJSON_IsNull(accepted)) {
        accepted = NULL;
    }
    if (!accepted) {
        goto end;
    }

    
    if(!cJSON_IsBool(accepted))
    {
    goto end; //Bool
    }

    // gate_candidate_response->gate
    cJSON *gate = cJSON_GetObjectItemCaseSensitive(gate_candidate_responseJSON, "gate");
    if (cJSON_IsNull(gate)) {
        gate = NULL;
    }
    if (!gate) {
        goto end;
    }

    
    gate_local_nonprim = gate_comparison_response_parseFromJSON(gate); //nonprimitive

    // gate_candidate_response->overfit
    cJSON *overfit = cJSON_GetObjectItemCaseSensitive(gate_candidate_responseJSON, "overfit");
    if (cJSON_IsNull(overfit)) {
        overfit = NULL;
    }
    if (!overfit) {
        goto end;
    }

    
    overfit_local_nonprim = overfit_response_parseFromJSON(overfit); //nonprimitive


    gate_candidate_response_local_var = gate_candidate_response_create_internal (
        accepted->valueint,
        gate_local_nonprim,
        overfit_local_nonprim
        );

    return gate_candidate_response_local_var;
end:
    if (gate_local_nonprim) {
        gate_comparison_response_free(gate_local_nonprim);
        gate_local_nonprim = NULL;
    }
    if (overfit_local_nonprim) {
        overfit_response_free(overfit_local_nonprim);
        overfit_local_nonprim = NULL;
    }
    return NULL;

}
