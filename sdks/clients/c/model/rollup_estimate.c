#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rollup_estimate.h"



static rollup_estimate_t *rollup_estimate_create_internal(
    double value,
    beater_api_rollup_weighting__e weighting
    ) {
    rollup_estimate_t *rollup_estimate_local_var = malloc(sizeof(rollup_estimate_t));
    if (!rollup_estimate_local_var) {
        return NULL;
    }
    rollup_estimate_local_var->value = value;
    rollup_estimate_local_var->weighting = weighting;

    rollup_estimate_local_var->_library_owned = 1;
    return rollup_estimate_local_var;
}

__attribute__((deprecated)) rollup_estimate_t *rollup_estimate_create(
    double value,
    beater_api_rollup_weighting__e weighting
    ) {
    return rollup_estimate_create_internal (
        value,
        weighting
        );
}

void rollup_estimate_free(rollup_estimate_t *rollup_estimate) {
    if(NULL == rollup_estimate){
        return ;
    }
    if(rollup_estimate->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "rollup_estimate_free");
        return ;
    }
    listEntry_t *listEntry;
    free(rollup_estimate);
}

cJSON *rollup_estimate_convertToJSON(rollup_estimate_t *rollup_estimate) {
    cJSON *item = cJSON_CreateObject();

    // rollup_estimate->value
    if (!rollup_estimate->value) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "value", rollup_estimate->value) == NULL) {
    goto fail; //Numeric
    }


    // rollup_estimate->weighting
    if (beater_api_rollup_weighting__NULL == rollup_estimate->weighting) {
        goto fail;
    }
    cJSON *weighting_local_JSON = rollup_weighting_convertToJSON(rollup_estimate->weighting);
    if(weighting_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "weighting", weighting_local_JSON);
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

rollup_estimate_t *rollup_estimate_parseFromJSON(cJSON *rollup_estimateJSON){

    rollup_estimate_t *rollup_estimate_local_var = NULL;

    // define the local variable for rollup_estimate->weighting
    beater_api_rollup_weighting__e weighting_local_nonprim = 0;

    // rollup_estimate->value
    cJSON *value = cJSON_GetObjectItemCaseSensitive(rollup_estimateJSON, "value");
    if (cJSON_IsNull(value)) {
        value = NULL;
    }
    if (!value) {
        goto end;
    }

    
    if(!cJSON_IsNumber(value))
    {
    goto end; //Numeric
    }

    // rollup_estimate->weighting
    cJSON *weighting = cJSON_GetObjectItemCaseSensitive(rollup_estimateJSON, "weighting");
    if (cJSON_IsNull(weighting)) {
        weighting = NULL;
    }
    if (!weighting) {
        goto end;
    }

    
    weighting_local_nonprim = rollup_weighting_parseFromJSON(weighting); //custom


    rollup_estimate_local_var = rollup_estimate_create_internal (
        value->valuedouble,
        weighting_local_nonprim
        );

    return rollup_estimate_local_var;
end:
    if (weighting_local_nonprim) {
        weighting_local_nonprim = 0;
    }
    return NULL;

}
