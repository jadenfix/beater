#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_comparison_response.h"



static gate_comparison_response_t *gate_comparison_response_create_internal(
    double baseline_mean,
    double candidate_mean,
    double ci_high,
    double ci_low,
    beater_api_gate_decision__e decision,
    double delta,
    double p_value,
    int sample_size
    ) {
    gate_comparison_response_t *gate_comparison_response_local_var = malloc(sizeof(gate_comparison_response_t));
    if (!gate_comparison_response_local_var) {
        return NULL;
    }
    gate_comparison_response_local_var->baseline_mean = baseline_mean;
    gate_comparison_response_local_var->candidate_mean = candidate_mean;
    gate_comparison_response_local_var->ci_high = ci_high;
    gate_comparison_response_local_var->ci_low = ci_low;
    gate_comparison_response_local_var->decision = decision;
    gate_comparison_response_local_var->delta = delta;
    gate_comparison_response_local_var->p_value = p_value;
    gate_comparison_response_local_var->sample_size = sample_size;

    gate_comparison_response_local_var->_library_owned = 1;
    return gate_comparison_response_local_var;
}

__attribute__((deprecated)) gate_comparison_response_t *gate_comparison_response_create(
    double baseline_mean,
    double candidate_mean,
    double ci_high,
    double ci_low,
    beater_api_gate_decision__e decision,
    double delta,
    double p_value,
    int sample_size
    ) {
    return gate_comparison_response_create_internal (
        baseline_mean,
        candidate_mean,
        ci_high,
        ci_low,
        decision,
        delta,
        p_value,
        sample_size
        );
}

void gate_comparison_response_free(gate_comparison_response_t *gate_comparison_response) {
    if(NULL == gate_comparison_response){
        return ;
    }
    if(gate_comparison_response->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_comparison_response_free");
        return ;
    }
    listEntry_t *listEntry;
    free(gate_comparison_response);
}

cJSON *gate_comparison_response_convertToJSON(gate_comparison_response_t *gate_comparison_response) {
    cJSON *item = cJSON_CreateObject();

    // gate_comparison_response->baseline_mean
    if (!gate_comparison_response->baseline_mean) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "baseline_mean", gate_comparison_response->baseline_mean) == NULL) {
    goto fail; //Numeric
    }


    // gate_comparison_response->candidate_mean
    if (!gate_comparison_response->candidate_mean) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "candidate_mean", gate_comparison_response->candidate_mean) == NULL) {
    goto fail; //Numeric
    }


    // gate_comparison_response->ci_high
    if (!gate_comparison_response->ci_high) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "ci_high", gate_comparison_response->ci_high) == NULL) {
    goto fail; //Numeric
    }


    // gate_comparison_response->ci_low
    if (!gate_comparison_response->ci_low) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "ci_low", gate_comparison_response->ci_low) == NULL) {
    goto fail; //Numeric
    }


    // gate_comparison_response->decision
    if (beater_api_gate_decision__NULL == gate_comparison_response->decision) {
        goto fail;
    }
    cJSON *decision_local_JSON = gate_decision_convertToJSON(gate_comparison_response->decision);
    if(decision_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "decision", decision_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // gate_comparison_response->delta
    if (!gate_comparison_response->delta) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "delta", gate_comparison_response->delta) == NULL) {
    goto fail; //Numeric
    }


    // gate_comparison_response->p_value
    if (!gate_comparison_response->p_value) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "p_value", gate_comparison_response->p_value) == NULL) {
    goto fail; //Numeric
    }


    // gate_comparison_response->sample_size
    if (!gate_comparison_response->sample_size) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "sample_size", gate_comparison_response->sample_size) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

gate_comparison_response_t *gate_comparison_response_parseFromJSON(cJSON *gate_comparison_responseJSON){

    gate_comparison_response_t *gate_comparison_response_local_var = NULL;

    // define the local variable for gate_comparison_response->decision
    beater_api_gate_decision__e decision_local_nonprim = 0;

    // gate_comparison_response->baseline_mean
    cJSON *baseline_mean = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "baseline_mean");
    if (cJSON_IsNull(baseline_mean)) {
        baseline_mean = NULL;
    }
    if (!baseline_mean) {
        goto end;
    }

    
    if(!cJSON_IsNumber(baseline_mean))
    {
    goto end; //Numeric
    }

    // gate_comparison_response->candidate_mean
    cJSON *candidate_mean = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "candidate_mean");
    if (cJSON_IsNull(candidate_mean)) {
        candidate_mean = NULL;
    }
    if (!candidate_mean) {
        goto end;
    }

    
    if(!cJSON_IsNumber(candidate_mean))
    {
    goto end; //Numeric
    }

    // gate_comparison_response->ci_high
    cJSON *ci_high = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "ci_high");
    if (cJSON_IsNull(ci_high)) {
        ci_high = NULL;
    }
    if (!ci_high) {
        goto end;
    }

    
    if(!cJSON_IsNumber(ci_high))
    {
    goto end; //Numeric
    }

    // gate_comparison_response->ci_low
    cJSON *ci_low = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "ci_low");
    if (cJSON_IsNull(ci_low)) {
        ci_low = NULL;
    }
    if (!ci_low) {
        goto end;
    }

    
    if(!cJSON_IsNumber(ci_low))
    {
    goto end; //Numeric
    }

    // gate_comparison_response->decision
    cJSON *decision = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "decision");
    if (cJSON_IsNull(decision)) {
        decision = NULL;
    }
    if (!decision) {
        goto end;
    }

    
    decision_local_nonprim = gate_decision_parseFromJSON(decision); //custom

    // gate_comparison_response->delta
    cJSON *delta = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "delta");
    if (cJSON_IsNull(delta)) {
        delta = NULL;
    }
    if (!delta) {
        goto end;
    }

    
    if(!cJSON_IsNumber(delta))
    {
    goto end; //Numeric
    }

    // gate_comparison_response->p_value
    cJSON *p_value = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "p_value");
    if (cJSON_IsNull(p_value)) {
        p_value = NULL;
    }
    if (!p_value) {
        goto end;
    }

    
    if(!cJSON_IsNumber(p_value))
    {
    goto end; //Numeric
    }

    // gate_comparison_response->sample_size
    cJSON *sample_size = cJSON_GetObjectItemCaseSensitive(gate_comparison_responseJSON, "sample_size");
    if (cJSON_IsNull(sample_size)) {
        sample_size = NULL;
    }
    if (!sample_size) {
        goto end;
    }

    
    if(!cJSON_IsNumber(sample_size))
    {
    goto end; //Numeric
    }


    gate_comparison_response_local_var = gate_comparison_response_create_internal (
        baseline_mean->valuedouble,
        candidate_mean->valuedouble,
        ci_high->valuedouble,
        ci_low->valuedouble,
        decision_local_nonprim,
        delta->valuedouble,
        p_value->valuedouble,
        sample_size->valuedouble
        );

    return gate_comparison_response_local_var;
end:
    if (decision_local_nonprim) {
        decision_local_nonprim = 0;
    }
    return NULL;

}
