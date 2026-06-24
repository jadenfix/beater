#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "calibration_confusion.h"



static calibration_confusion_t *calibration_confusion_create_internal(
    int human_fail_judge_fail,
    int human_fail_judge_pass,
    int human_pass_judge_fail,
    int human_pass_judge_pass
    ) {
    calibration_confusion_t *calibration_confusion_local_var = malloc(sizeof(calibration_confusion_t));
    if (!calibration_confusion_local_var) {
        return NULL;
    }
    calibration_confusion_local_var->human_fail_judge_fail = human_fail_judge_fail;
    calibration_confusion_local_var->human_fail_judge_pass = human_fail_judge_pass;
    calibration_confusion_local_var->human_pass_judge_fail = human_pass_judge_fail;
    calibration_confusion_local_var->human_pass_judge_pass = human_pass_judge_pass;

    calibration_confusion_local_var->_library_owned = 1;
    return calibration_confusion_local_var;
}

__attribute__((deprecated)) calibration_confusion_t *calibration_confusion_create(
    int human_fail_judge_fail,
    int human_fail_judge_pass,
    int human_pass_judge_fail,
    int human_pass_judge_pass
    ) {
    return calibration_confusion_create_internal (
        human_fail_judge_fail,
        human_fail_judge_pass,
        human_pass_judge_fail,
        human_pass_judge_pass
        );
}

void calibration_confusion_free(calibration_confusion_t *calibration_confusion) {
    if(NULL == calibration_confusion){
        return ;
    }
    if(calibration_confusion->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "calibration_confusion_free");
        return ;
    }
    listEntry_t *listEntry;
    free(calibration_confusion);
}

cJSON *calibration_confusion_convertToJSON(calibration_confusion_t *calibration_confusion) {
    cJSON *item = cJSON_CreateObject();

    // calibration_confusion->human_fail_judge_fail
    if (!calibration_confusion->human_fail_judge_fail) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "human_fail_judge_fail", calibration_confusion->human_fail_judge_fail) == NULL) {
    goto fail; //Numeric
    }


    // calibration_confusion->human_fail_judge_pass
    if (!calibration_confusion->human_fail_judge_pass) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "human_fail_judge_pass", calibration_confusion->human_fail_judge_pass) == NULL) {
    goto fail; //Numeric
    }


    // calibration_confusion->human_pass_judge_fail
    if (!calibration_confusion->human_pass_judge_fail) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "human_pass_judge_fail", calibration_confusion->human_pass_judge_fail) == NULL) {
    goto fail; //Numeric
    }


    // calibration_confusion->human_pass_judge_pass
    if (!calibration_confusion->human_pass_judge_pass) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "human_pass_judge_pass", calibration_confusion->human_pass_judge_pass) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

calibration_confusion_t *calibration_confusion_parseFromJSON(cJSON *calibration_confusionJSON){

    calibration_confusion_t *calibration_confusion_local_var = NULL;

    // calibration_confusion->human_fail_judge_fail
    cJSON *human_fail_judge_fail = cJSON_GetObjectItemCaseSensitive(calibration_confusionJSON, "human_fail_judge_fail");
    if (cJSON_IsNull(human_fail_judge_fail)) {
        human_fail_judge_fail = NULL;
    }
    if (!human_fail_judge_fail) {
        goto end;
    }

    
    if(!cJSON_IsNumber(human_fail_judge_fail))
    {
    goto end; //Numeric
    }

    // calibration_confusion->human_fail_judge_pass
    cJSON *human_fail_judge_pass = cJSON_GetObjectItemCaseSensitive(calibration_confusionJSON, "human_fail_judge_pass");
    if (cJSON_IsNull(human_fail_judge_pass)) {
        human_fail_judge_pass = NULL;
    }
    if (!human_fail_judge_pass) {
        goto end;
    }

    
    if(!cJSON_IsNumber(human_fail_judge_pass))
    {
    goto end; //Numeric
    }

    // calibration_confusion->human_pass_judge_fail
    cJSON *human_pass_judge_fail = cJSON_GetObjectItemCaseSensitive(calibration_confusionJSON, "human_pass_judge_fail");
    if (cJSON_IsNull(human_pass_judge_fail)) {
        human_pass_judge_fail = NULL;
    }
    if (!human_pass_judge_fail) {
        goto end;
    }

    
    if(!cJSON_IsNumber(human_pass_judge_fail))
    {
    goto end; //Numeric
    }

    // calibration_confusion->human_pass_judge_pass
    cJSON *human_pass_judge_pass = cJSON_GetObjectItemCaseSensitive(calibration_confusionJSON, "human_pass_judge_pass");
    if (cJSON_IsNull(human_pass_judge_pass)) {
        human_pass_judge_pass = NULL;
    }
    if (!human_pass_judge_pass) {
        goto end;
    }

    
    if(!cJSON_IsNumber(human_pass_judge_pass))
    {
    goto end; //Numeric
    }


    calibration_confusion_local_var = calibration_confusion_create_internal (
        human_fail_judge_fail->valuedouble,
        human_fail_judge_pass->valuedouble,
        human_pass_judge_fail->valuedouble,
        human_pass_judge_pass->valuedouble
        );

    return calibration_confusion_local_var;
end:
    return NULL;

}
