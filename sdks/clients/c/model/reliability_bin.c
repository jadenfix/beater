#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "reliability_bin.h"



static reliability_bin_t *reliability_bin_create_internal(
    double accuracy,
    int bin_index,
    double calibration_gap,
    double lower_bound,
    double mean_confidence,
    int sample_count,
    double upper_bound
    ) {
    reliability_bin_t *reliability_bin_local_var = malloc(sizeof(reliability_bin_t));
    if (!reliability_bin_local_var) {
        return NULL;
    }
    reliability_bin_local_var->accuracy = accuracy;
    reliability_bin_local_var->bin_index = bin_index;
    reliability_bin_local_var->calibration_gap = calibration_gap;
    reliability_bin_local_var->lower_bound = lower_bound;
    reliability_bin_local_var->mean_confidence = mean_confidence;
    reliability_bin_local_var->sample_count = sample_count;
    reliability_bin_local_var->upper_bound = upper_bound;

    reliability_bin_local_var->_library_owned = 1;
    return reliability_bin_local_var;
}

__attribute__((deprecated)) reliability_bin_t *reliability_bin_create(
    double accuracy,
    int bin_index,
    double calibration_gap,
    double lower_bound,
    double mean_confidence,
    int sample_count,
    double upper_bound
    ) {
    return reliability_bin_create_internal (
        accuracy,
        bin_index,
        calibration_gap,
        lower_bound,
        mean_confidence,
        sample_count,
        upper_bound
        );
}

void reliability_bin_free(reliability_bin_t *reliability_bin) {
    if(NULL == reliability_bin){
        return ;
    }
    if(reliability_bin->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "reliability_bin_free");
        return ;
    }
    listEntry_t *listEntry;
    free(reliability_bin);
}

cJSON *reliability_bin_convertToJSON(reliability_bin_t *reliability_bin) {
    cJSON *item = cJSON_CreateObject();

    // reliability_bin->accuracy
    if(reliability_bin->accuracy) {
    if(cJSON_AddNumberToObject(item, "accuracy", reliability_bin->accuracy) == NULL) {
    goto fail; //Numeric
    }
    }


    // reliability_bin->bin_index
    if (!reliability_bin->bin_index) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "bin_index", reliability_bin->bin_index) == NULL) {
    goto fail; //Numeric
    }


    // reliability_bin->calibration_gap
    if(reliability_bin->calibration_gap) {
    if(cJSON_AddNumberToObject(item, "calibration_gap", reliability_bin->calibration_gap) == NULL) {
    goto fail; //Numeric
    }
    }


    // reliability_bin->lower_bound
    if (!reliability_bin->lower_bound) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "lower_bound", reliability_bin->lower_bound) == NULL) {
    goto fail; //Numeric
    }


    // reliability_bin->mean_confidence
    if(reliability_bin->mean_confidence) {
    if(cJSON_AddNumberToObject(item, "mean_confidence", reliability_bin->mean_confidence) == NULL) {
    goto fail; //Numeric
    }
    }


    // reliability_bin->sample_count
    if (!reliability_bin->sample_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "sample_count", reliability_bin->sample_count) == NULL) {
    goto fail; //Numeric
    }


    // reliability_bin->upper_bound
    if (!reliability_bin->upper_bound) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "upper_bound", reliability_bin->upper_bound) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

reliability_bin_t *reliability_bin_parseFromJSON(cJSON *reliability_binJSON){

    reliability_bin_t *reliability_bin_local_var = NULL;

    // reliability_bin->accuracy
    cJSON *accuracy = cJSON_GetObjectItemCaseSensitive(reliability_binJSON, "accuracy");
    if (cJSON_IsNull(accuracy)) {
        accuracy = NULL;
    }
    if (accuracy) { 
    if(!cJSON_IsNumber(accuracy))
    {
    goto end; //Numeric
    }
    }

    // reliability_bin->bin_index
    cJSON *bin_index = cJSON_GetObjectItemCaseSensitive(reliability_binJSON, "bin_index");
    if (cJSON_IsNull(bin_index)) {
        bin_index = NULL;
    }
    if (!bin_index) {
        goto end;
    }

    
    if(!cJSON_IsNumber(bin_index))
    {
    goto end; //Numeric
    }

    // reliability_bin->calibration_gap
    cJSON *calibration_gap = cJSON_GetObjectItemCaseSensitive(reliability_binJSON, "calibration_gap");
    if (cJSON_IsNull(calibration_gap)) {
        calibration_gap = NULL;
    }
    if (calibration_gap) { 
    if(!cJSON_IsNumber(calibration_gap))
    {
    goto end; //Numeric
    }
    }

    // reliability_bin->lower_bound
    cJSON *lower_bound = cJSON_GetObjectItemCaseSensitive(reliability_binJSON, "lower_bound");
    if (cJSON_IsNull(lower_bound)) {
        lower_bound = NULL;
    }
    if (!lower_bound) {
        goto end;
    }

    
    if(!cJSON_IsNumber(lower_bound))
    {
    goto end; //Numeric
    }

    // reliability_bin->mean_confidence
    cJSON *mean_confidence = cJSON_GetObjectItemCaseSensitive(reliability_binJSON, "mean_confidence");
    if (cJSON_IsNull(mean_confidence)) {
        mean_confidence = NULL;
    }
    if (mean_confidence) { 
    if(!cJSON_IsNumber(mean_confidence))
    {
    goto end; //Numeric
    }
    }

    // reliability_bin->sample_count
    cJSON *sample_count = cJSON_GetObjectItemCaseSensitive(reliability_binJSON, "sample_count");
    if (cJSON_IsNull(sample_count)) {
        sample_count = NULL;
    }
    if (!sample_count) {
        goto end;
    }

    
    if(!cJSON_IsNumber(sample_count))
    {
    goto end; //Numeric
    }

    // reliability_bin->upper_bound
    cJSON *upper_bound = cJSON_GetObjectItemCaseSensitive(reliability_binJSON, "upper_bound");
    if (cJSON_IsNull(upper_bound)) {
        upper_bound = NULL;
    }
    if (!upper_bound) {
        goto end;
    }

    
    if(!cJSON_IsNumber(upper_bound))
    {
    goto end; //Numeric
    }


    reliability_bin_local_var = reliability_bin_create_internal (
        accuracy ? accuracy->valuedouble : 0,
        bin_index->valuedouble,
        calibration_gap ? calibration_gap->valuedouble : 0,
        lower_bound->valuedouble,
        mean_confidence ? mean_confidence->valuedouble : 0,
        sample_count->valuedouble,
        upper_bound->valuedouble
        );

    return reliability_bin_local_var;
end:
    return NULL;

}
