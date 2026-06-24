#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "online_sampling_policy.h"



static online_sampling_policy_t *online_sampling_policy_create_internal(
    long high_cost_micros_threshold,
    int keep_errors,
    int sample_rate_per_mille,
    long slow_ms_threshold
    ) {
    online_sampling_policy_t *online_sampling_policy_local_var = malloc(sizeof(online_sampling_policy_t));
    if (!online_sampling_policy_local_var) {
        return NULL;
    }
    online_sampling_policy_local_var->high_cost_micros_threshold = high_cost_micros_threshold;
    online_sampling_policy_local_var->keep_errors = keep_errors;
    online_sampling_policy_local_var->sample_rate_per_mille = sample_rate_per_mille;
    online_sampling_policy_local_var->slow_ms_threshold = slow_ms_threshold;

    online_sampling_policy_local_var->_library_owned = 1;
    return online_sampling_policy_local_var;
}

__attribute__((deprecated)) online_sampling_policy_t *online_sampling_policy_create(
    long high_cost_micros_threshold,
    int keep_errors,
    int sample_rate_per_mille,
    long slow_ms_threshold
    ) {
    return online_sampling_policy_create_internal (
        high_cost_micros_threshold,
        keep_errors,
        sample_rate_per_mille,
        slow_ms_threshold
        );
}

void online_sampling_policy_free(online_sampling_policy_t *online_sampling_policy) {
    if(NULL == online_sampling_policy){
        return ;
    }
    if(online_sampling_policy->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "online_sampling_policy_free");
        return ;
    }
    listEntry_t *listEntry;
    free(online_sampling_policy);
}

cJSON *online_sampling_policy_convertToJSON(online_sampling_policy_t *online_sampling_policy) {
    cJSON *item = cJSON_CreateObject();

    // online_sampling_policy->high_cost_micros_threshold
    if(online_sampling_policy->high_cost_micros_threshold) {
    if(cJSON_AddNumberToObject(item, "high_cost_micros_threshold", online_sampling_policy->high_cost_micros_threshold) == NULL) {
    goto fail; //Numeric
    }
    }


    // online_sampling_policy->keep_errors
    if (!online_sampling_policy->keep_errors) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "keep_errors", online_sampling_policy->keep_errors) == NULL) {
    goto fail; //Bool
    }


    // online_sampling_policy->sample_rate_per_mille
    if (!online_sampling_policy->sample_rate_per_mille) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "sample_rate_per_mille", online_sampling_policy->sample_rate_per_mille) == NULL) {
    goto fail; //Numeric
    }


    // online_sampling_policy->slow_ms_threshold
    if(online_sampling_policy->slow_ms_threshold) {
    if(cJSON_AddNumberToObject(item, "slow_ms_threshold", online_sampling_policy->slow_ms_threshold) == NULL) {
    goto fail; //Numeric
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

online_sampling_policy_t *online_sampling_policy_parseFromJSON(cJSON *online_sampling_policyJSON){

    online_sampling_policy_t *online_sampling_policy_local_var = NULL;

    // online_sampling_policy->high_cost_micros_threshold
    cJSON *high_cost_micros_threshold = cJSON_GetObjectItemCaseSensitive(online_sampling_policyJSON, "high_cost_micros_threshold");
    if (cJSON_IsNull(high_cost_micros_threshold)) {
        high_cost_micros_threshold = NULL;
    }
    if (high_cost_micros_threshold) { 
    if(!cJSON_IsNumber(high_cost_micros_threshold))
    {
    goto end; //Numeric
    }
    }

    // online_sampling_policy->keep_errors
    cJSON *keep_errors = cJSON_GetObjectItemCaseSensitive(online_sampling_policyJSON, "keep_errors");
    if (cJSON_IsNull(keep_errors)) {
        keep_errors = NULL;
    }
    if (!keep_errors) {
        goto end;
    }

    
    if(!cJSON_IsBool(keep_errors))
    {
    goto end; //Bool
    }

    // online_sampling_policy->sample_rate_per_mille
    cJSON *sample_rate_per_mille = cJSON_GetObjectItemCaseSensitive(online_sampling_policyJSON, "sample_rate_per_mille");
    if (cJSON_IsNull(sample_rate_per_mille)) {
        sample_rate_per_mille = NULL;
    }
    if (!sample_rate_per_mille) {
        goto end;
    }

    
    if(!cJSON_IsNumber(sample_rate_per_mille))
    {
    goto end; //Numeric
    }

    // online_sampling_policy->slow_ms_threshold
    cJSON *slow_ms_threshold = cJSON_GetObjectItemCaseSensitive(online_sampling_policyJSON, "slow_ms_threshold");
    if (cJSON_IsNull(slow_ms_threshold)) {
        slow_ms_threshold = NULL;
    }
    if (slow_ms_threshold) { 
    if(!cJSON_IsNumber(slow_ms_threshold))
    {
    goto end; //Numeric
    }
    }


    online_sampling_policy_local_var = online_sampling_policy_create_internal (
        high_cost_micros_threshold ? high_cost_micros_threshold->valuedouble : 0,
        keep_errors->valueint,
        sample_rate_per_mille->valuedouble,
        slow_ms_threshold ? slow_ms_threshold->valuedouble : 0
        );

    return online_sampling_policy_local_var;
end:
    return NULL;

}
