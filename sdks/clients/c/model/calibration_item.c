#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "calibration_item.h"



static calibration_item_t *calibration_item_create_internal(
    int agreed,
    char *dataset_case_id,
    any_type_t *evidence,
    beater_api_calibration_label__e human_label,
    beater_api_calibration_label__e judge_label,
    char *judge_result_label,
    double judge_score
    ) {
    calibration_item_t *calibration_item_local_var = malloc(sizeof(calibration_item_t));
    if (!calibration_item_local_var) {
        return NULL;
    }
    calibration_item_local_var->agreed = agreed;
    calibration_item_local_var->dataset_case_id = dataset_case_id;
    calibration_item_local_var->evidence = evidence;
    calibration_item_local_var->human_label = human_label;
    calibration_item_local_var->judge_label = judge_label;
    calibration_item_local_var->judge_result_label = judge_result_label;
    calibration_item_local_var->judge_score = judge_score;

    calibration_item_local_var->_library_owned = 1;
    return calibration_item_local_var;
}

__attribute__((deprecated)) calibration_item_t *calibration_item_create(
    int agreed,
    char *dataset_case_id,
    any_type_t *evidence,
    beater_api_calibration_label__e human_label,
    beater_api_calibration_label__e judge_label,
    char *judge_result_label,
    double judge_score
    ) {
    return calibration_item_create_internal (
        agreed,
        dataset_case_id,
        evidence,
        human_label,
        judge_label,
        judge_result_label,
        judge_score
        );
}

void calibration_item_free(calibration_item_t *calibration_item) {
    if(NULL == calibration_item){
        return ;
    }
    if(calibration_item->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "calibration_item_free");
        return ;
    }
    listEntry_t *listEntry;
    if (calibration_item->dataset_case_id) {
        free(calibration_item->dataset_case_id);
        calibration_item->dataset_case_id = NULL;
    }
    if (calibration_item->evidence) {
        _free(calibration_item->evidence);
        calibration_item->evidence = NULL;
    }
    if (calibration_item->judge_result_label) {
        free(calibration_item->judge_result_label);
        calibration_item->judge_result_label = NULL;
    }
    free(calibration_item);
}

cJSON *calibration_item_convertToJSON(calibration_item_t *calibration_item) {
    cJSON *item = cJSON_CreateObject();

    // calibration_item->agreed
    if (!calibration_item->agreed) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "agreed", calibration_item->agreed) == NULL) {
    goto fail; //Bool
    }


    // calibration_item->dataset_case_id
    if (!calibration_item->dataset_case_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_case_id", calibration_item->dataset_case_id) == NULL) {
    goto fail; //String
    }


    // calibration_item->evidence
    if (!calibration_item->evidence) {
        goto fail;
    }
    cJSON *evidence_local_JSON = _convertToJSON(calibration_item->evidence);
    if(evidence_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "evidence", evidence_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // calibration_item->human_label
    if (beater_api_calibration_label__NULL == calibration_item->human_label) {
        goto fail;
    }
    cJSON *human_label_local_JSON = calibration_label_convertToJSON(calibration_item->human_label);
    if(human_label_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "human_label", human_label_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // calibration_item->judge_label
    if (beater_api_calibration_label__NULL == calibration_item->judge_label) {
        goto fail;
    }
    cJSON *judge_label_local_JSON = calibration_label_convertToJSON(calibration_item->judge_label);
    if(judge_label_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "judge_label", judge_label_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // calibration_item->judge_result_label
    if(calibration_item->judge_result_label) {
    if(cJSON_AddStringToObject(item, "judge_result_label", calibration_item->judge_result_label) == NULL) {
    goto fail; //String
    }
    }


    // calibration_item->judge_score
    if (!calibration_item->judge_score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "judge_score", calibration_item->judge_score) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

calibration_item_t *calibration_item_parseFromJSON(cJSON *calibration_itemJSON){

    calibration_item_t *calibration_item_local_var = NULL;

    // define the local variable for calibration_item->evidence
    _t *evidence_local_nonprim = NULL;

    // define the local variable for calibration_item->human_label
    beater_api_calibration_label__e human_label_local_nonprim = 0;

    // define the local variable for calibration_item->judge_label
    beater_api_calibration_label__e judge_label_local_nonprim = 0;

    // calibration_item->agreed
    cJSON *agreed = cJSON_GetObjectItemCaseSensitive(calibration_itemJSON, "agreed");
    if (cJSON_IsNull(agreed)) {
        agreed = NULL;
    }
    if (!agreed) {
        goto end;
    }

    
    if(!cJSON_IsBool(agreed))
    {
    goto end; //Bool
    }

    // calibration_item->dataset_case_id
    cJSON *dataset_case_id = cJSON_GetObjectItemCaseSensitive(calibration_itemJSON, "dataset_case_id");
    if (cJSON_IsNull(dataset_case_id)) {
        dataset_case_id = NULL;
    }
    if (!dataset_case_id) {
        goto end;
    }

    
    if(!cJSON_IsString(dataset_case_id))
    {
    goto end; //String
    }

    // calibration_item->evidence
    cJSON *evidence = cJSON_GetObjectItemCaseSensitive(calibration_itemJSON, "evidence");
    if (cJSON_IsNull(evidence)) {
        evidence = NULL;
    }
    if (!evidence) {
        goto end;
    }

    
    evidence_local_nonprim = _parseFromJSON(evidence); //custom

    // calibration_item->human_label
    cJSON *human_label = cJSON_GetObjectItemCaseSensitive(calibration_itemJSON, "human_label");
    if (cJSON_IsNull(human_label)) {
        human_label = NULL;
    }
    if (!human_label) {
        goto end;
    }

    
    human_label_local_nonprim = calibration_label_parseFromJSON(human_label); //custom

    // calibration_item->judge_label
    cJSON *judge_label = cJSON_GetObjectItemCaseSensitive(calibration_itemJSON, "judge_label");
    if (cJSON_IsNull(judge_label)) {
        judge_label = NULL;
    }
    if (!judge_label) {
        goto end;
    }

    
    judge_label_local_nonprim = calibration_label_parseFromJSON(judge_label); //custom

    // calibration_item->judge_result_label
    cJSON *judge_result_label = cJSON_GetObjectItemCaseSensitive(calibration_itemJSON, "judge_result_label");
    if (cJSON_IsNull(judge_result_label)) {
        judge_result_label = NULL;
    }
    if (judge_result_label) { 
    if(!cJSON_IsString(judge_result_label) && !cJSON_IsNull(judge_result_label))
    {
    goto end; //String
    }
    }

    // calibration_item->judge_score
    cJSON *judge_score = cJSON_GetObjectItemCaseSensitive(calibration_itemJSON, "judge_score");
    if (cJSON_IsNull(judge_score)) {
        judge_score = NULL;
    }
    if (!judge_score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(judge_score))
    {
    goto end; //Numeric
    }


    calibration_item_local_var = calibration_item_create_internal (
        agreed->valueint,
        strdup(dataset_case_id->valuestring),
        evidence_local_nonprim,
        human_label_local_nonprim,
        judge_label_local_nonprim,
        judge_result_label && !cJSON_IsNull(judge_result_label) ? strdup(judge_result_label->valuestring) : NULL,
        judge_score->valuedouble
        );

    return calibration_item_local_var;
end:
    if (evidence_local_nonprim) {
        _free(evidence_local_nonprim);
        evidence_local_nonprim = NULL;
    }
    if (human_label_local_nonprim) {
        human_label_local_nonprim = 0;
    }
    if (judge_label_local_nonprim) {
        judge_label_local_nonprim = 0;
    }
    return NULL;

}
