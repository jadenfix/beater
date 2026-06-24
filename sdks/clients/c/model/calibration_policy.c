#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "calibration_policy.h"



static calibration_policy_t *calibration_policy_create_internal(
    double pass_threshold
    ) {
    calibration_policy_t *calibration_policy_local_var = malloc(sizeof(calibration_policy_t));
    if (!calibration_policy_local_var) {
        return NULL;
    }
    calibration_policy_local_var->pass_threshold = pass_threshold;

    calibration_policy_local_var->_library_owned = 1;
    return calibration_policy_local_var;
}

__attribute__((deprecated)) calibration_policy_t *calibration_policy_create(
    double pass_threshold
    ) {
    return calibration_policy_create_internal (
        pass_threshold
        );
}

void calibration_policy_free(calibration_policy_t *calibration_policy) {
    if(NULL == calibration_policy){
        return ;
    }
    if(calibration_policy->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "calibration_policy_free");
        return ;
    }
    listEntry_t *listEntry;
    free(calibration_policy);
}

cJSON *calibration_policy_convertToJSON(calibration_policy_t *calibration_policy) {
    cJSON *item = cJSON_CreateObject();

    // calibration_policy->pass_threshold
    if (!calibration_policy->pass_threshold) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "pass_threshold", calibration_policy->pass_threshold) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

calibration_policy_t *calibration_policy_parseFromJSON(cJSON *calibration_policyJSON){

    calibration_policy_t *calibration_policy_local_var = NULL;

    // calibration_policy->pass_threshold
    cJSON *pass_threshold = cJSON_GetObjectItemCaseSensitive(calibration_policyJSON, "pass_threshold");
    if (cJSON_IsNull(pass_threshold)) {
        pass_threshold = NULL;
    }
    if (!pass_threshold) {
        goto end;
    }

    
    if(!cJSON_IsNumber(pass_threshold))
    {
    goto end; //Numeric
    }


    calibration_policy_local_var = calibration_policy_create_internal (
        pass_threshold->valuedouble
        );

    return calibration_policy_local_var;
end:
    return NULL;

}
