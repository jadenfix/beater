#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_policy.h"



static gate_policy_t *gate_policy_create_internal(
    double alpha,
    int comparison_count,
    double max_regression,
    int min_sample_size
    ) {
    gate_policy_t *gate_policy_local_var = malloc(sizeof(gate_policy_t));
    if (!gate_policy_local_var) {
        return NULL;
    }
    gate_policy_local_var->alpha = alpha;
    gate_policy_local_var->comparison_count = comparison_count;
    gate_policy_local_var->max_regression = max_regression;
    gate_policy_local_var->min_sample_size = min_sample_size;

    gate_policy_local_var->_library_owned = 1;
    return gate_policy_local_var;
}

__attribute__((deprecated)) gate_policy_t *gate_policy_create(
    double alpha,
    int comparison_count,
    double max_regression,
    int min_sample_size
    ) {
    return gate_policy_create_internal (
        alpha,
        comparison_count,
        max_regression,
        min_sample_size
        );
}

void gate_policy_free(gate_policy_t *gate_policy) {
    if(NULL == gate_policy){
        return ;
    }
    if(gate_policy->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_policy_free");
        return ;
    }
    listEntry_t *listEntry;
    free(gate_policy);
}

cJSON *gate_policy_convertToJSON(gate_policy_t *gate_policy) {
    cJSON *item = cJSON_CreateObject();

    // gate_policy->alpha
    if (!gate_policy->alpha) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "alpha", gate_policy->alpha) == NULL) {
    goto fail; //Numeric
    }


    // gate_policy->comparison_count
    if (!gate_policy->comparison_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "comparison_count", gate_policy->comparison_count) == NULL) {
    goto fail; //Numeric
    }


    // gate_policy->max_regression
    if (!gate_policy->max_regression) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "max_regression", gate_policy->max_regression) == NULL) {
    goto fail; //Numeric
    }


    // gate_policy->min_sample_size
    if (!gate_policy->min_sample_size) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "min_sample_size", gate_policy->min_sample_size) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

gate_policy_t *gate_policy_parseFromJSON(cJSON *gate_policyJSON){

    gate_policy_t *gate_policy_local_var = NULL;

    // gate_policy->alpha
    cJSON *alpha = cJSON_GetObjectItemCaseSensitive(gate_policyJSON, "alpha");
    if (cJSON_IsNull(alpha)) {
        alpha = NULL;
    }
    if (!alpha) {
        goto end;
    }

    
    if(!cJSON_IsNumber(alpha))
    {
    goto end; //Numeric
    }

    // gate_policy->comparison_count
    cJSON *comparison_count = cJSON_GetObjectItemCaseSensitive(gate_policyJSON, "comparison_count");
    if (cJSON_IsNull(comparison_count)) {
        comparison_count = NULL;
    }
    if (!comparison_count) {
        goto end;
    }

    
    if(!cJSON_IsNumber(comparison_count))
    {
    goto end; //Numeric
    }

    // gate_policy->max_regression
    cJSON *max_regression = cJSON_GetObjectItemCaseSensitive(gate_policyJSON, "max_regression");
    if (cJSON_IsNull(max_regression)) {
        max_regression = NULL;
    }
    if (!max_regression) {
        goto end;
    }

    
    if(!cJSON_IsNumber(max_regression))
    {
    goto end; //Numeric
    }

    // gate_policy->min_sample_size
    cJSON *min_sample_size = cJSON_GetObjectItemCaseSensitive(gate_policyJSON, "min_sample_size");
    if (cJSON_IsNull(min_sample_size)) {
        min_sample_size = NULL;
    }
    if (!min_sample_size) {
        goto end;
    }

    
    if(!cJSON_IsNumber(min_sample_size))
    {
    goto end; //Numeric
    }


    gate_policy_local_var = gate_policy_create_internal (
        alpha->valuedouble,
        comparison_count->valuedouble,
        max_regression->valuedouble,
        min_sample_size->valuedouble
        );

    return gate_policy_local_var;
end:
    return NULL;

}
