#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "overfit_response.h"



static overfit_response_t *overfit_response_create_internal(
    double gap,
    double gap_ci_high,
    double gap_ci_low,
    double holdout_lift,
    double optimize_lift,
    int overfit
    ) {
    overfit_response_t *overfit_response_local_var = malloc(sizeof(overfit_response_t));
    if (!overfit_response_local_var) {
        return NULL;
    }
    overfit_response_local_var->gap = gap;
    overfit_response_local_var->gap_ci_high = gap_ci_high;
    overfit_response_local_var->gap_ci_low = gap_ci_low;
    overfit_response_local_var->holdout_lift = holdout_lift;
    overfit_response_local_var->optimize_lift = optimize_lift;
    overfit_response_local_var->overfit = overfit;

    overfit_response_local_var->_library_owned = 1;
    return overfit_response_local_var;
}

__attribute__((deprecated)) overfit_response_t *overfit_response_create(
    double gap,
    double gap_ci_high,
    double gap_ci_low,
    double holdout_lift,
    double optimize_lift,
    int overfit
    ) {
    return overfit_response_create_internal (
        gap,
        gap_ci_high,
        gap_ci_low,
        holdout_lift,
        optimize_lift,
        overfit
        );
}

void overfit_response_free(overfit_response_t *overfit_response) {
    if(NULL == overfit_response){
        return ;
    }
    if(overfit_response->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "overfit_response_free");
        return ;
    }
    listEntry_t *listEntry;
    free(overfit_response);
}

cJSON *overfit_response_convertToJSON(overfit_response_t *overfit_response) {
    cJSON *item = cJSON_CreateObject();

    // overfit_response->gap
    if (!overfit_response->gap) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "gap", overfit_response->gap) == NULL) {
    goto fail; //Numeric
    }


    // overfit_response->gap_ci_high
    if (!overfit_response->gap_ci_high) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "gap_ci_high", overfit_response->gap_ci_high) == NULL) {
    goto fail; //Numeric
    }


    // overfit_response->gap_ci_low
    if (!overfit_response->gap_ci_low) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "gap_ci_low", overfit_response->gap_ci_low) == NULL) {
    goto fail; //Numeric
    }


    // overfit_response->holdout_lift
    if (!overfit_response->holdout_lift) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "holdout_lift", overfit_response->holdout_lift) == NULL) {
    goto fail; //Numeric
    }


    // overfit_response->optimize_lift
    if (!overfit_response->optimize_lift) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "optimize_lift", overfit_response->optimize_lift) == NULL) {
    goto fail; //Numeric
    }


    // overfit_response->overfit
    if (!overfit_response->overfit) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "overfit", overfit_response->overfit) == NULL) {
    goto fail; //Bool
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

overfit_response_t *overfit_response_parseFromJSON(cJSON *overfit_responseJSON){

    overfit_response_t *overfit_response_local_var = NULL;

    // overfit_response->gap
    cJSON *gap = cJSON_GetObjectItemCaseSensitive(overfit_responseJSON, "gap");
    if (cJSON_IsNull(gap)) {
        gap = NULL;
    }
    if (!gap) {
        goto end;
    }

    
    if(!cJSON_IsNumber(gap))
    {
    goto end; //Numeric
    }

    // overfit_response->gap_ci_high
    cJSON *gap_ci_high = cJSON_GetObjectItemCaseSensitive(overfit_responseJSON, "gap_ci_high");
    if (cJSON_IsNull(gap_ci_high)) {
        gap_ci_high = NULL;
    }
    if (!gap_ci_high) {
        goto end;
    }

    
    if(!cJSON_IsNumber(gap_ci_high))
    {
    goto end; //Numeric
    }

    // overfit_response->gap_ci_low
    cJSON *gap_ci_low = cJSON_GetObjectItemCaseSensitive(overfit_responseJSON, "gap_ci_low");
    if (cJSON_IsNull(gap_ci_low)) {
        gap_ci_low = NULL;
    }
    if (!gap_ci_low) {
        goto end;
    }

    
    if(!cJSON_IsNumber(gap_ci_low))
    {
    goto end; //Numeric
    }

    // overfit_response->holdout_lift
    cJSON *holdout_lift = cJSON_GetObjectItemCaseSensitive(overfit_responseJSON, "holdout_lift");
    if (cJSON_IsNull(holdout_lift)) {
        holdout_lift = NULL;
    }
    if (!holdout_lift) {
        goto end;
    }

    
    if(!cJSON_IsNumber(holdout_lift))
    {
    goto end; //Numeric
    }

    // overfit_response->optimize_lift
    cJSON *optimize_lift = cJSON_GetObjectItemCaseSensitive(overfit_responseJSON, "optimize_lift");
    if (cJSON_IsNull(optimize_lift)) {
        optimize_lift = NULL;
    }
    if (!optimize_lift) {
        goto end;
    }

    
    if(!cJSON_IsNumber(optimize_lift))
    {
    goto end; //Numeric
    }

    // overfit_response->overfit
    cJSON *overfit = cJSON_GetObjectItemCaseSensitive(overfit_responseJSON, "overfit");
    if (cJSON_IsNull(overfit)) {
        overfit = NULL;
    }
    if (!overfit) {
        goto end;
    }

    
    if(!cJSON_IsBool(overfit))
    {
    goto end; //Bool
    }


    overfit_response_local_var = overfit_response_create_internal (
        gap->valuedouble,
        gap_ci_high->valuedouble,
        gap_ci_low->valuedouble,
        holdout_lift->valuedouble,
        optimize_lift->valuedouble,
        overfit->valueint
        );

    return overfit_response_local_var;
end:
    return NULL;

}
