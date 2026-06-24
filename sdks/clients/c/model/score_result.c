#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "score_result.h"



static score_result_t *score_result_create_internal(
    any_type_t *evidence,
    char *label,
    double score
    ) {
    score_result_t *score_result_local_var = malloc(sizeof(score_result_t));
    if (!score_result_local_var) {
        return NULL;
    }
    score_result_local_var->evidence = evidence;
    score_result_local_var->label = label;
    score_result_local_var->score = score;

    score_result_local_var->_library_owned = 1;
    return score_result_local_var;
}

__attribute__((deprecated)) score_result_t *score_result_create(
    any_type_t *evidence,
    char *label,
    double score
    ) {
    return score_result_create_internal (
        evidence,
        label,
        score
        );
}

void score_result_free(score_result_t *score_result) {
    if(NULL == score_result){
        return ;
    }
    if(score_result->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "score_result_free");
        return ;
    }
    listEntry_t *listEntry;
    if (score_result->evidence) {
        _free(score_result->evidence);
        score_result->evidence = NULL;
    }
    if (score_result->label) {
        free(score_result->label);
        score_result->label = NULL;
    }
    free(score_result);
}

cJSON *score_result_convertToJSON(score_result_t *score_result) {
    cJSON *item = cJSON_CreateObject();

    // score_result->evidence
    if (!score_result->evidence) {
        goto fail;
    }
    cJSON *evidence_local_JSON = _convertToJSON(score_result->evidence);
    if(evidence_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "evidence", evidence_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // score_result->label
    if(score_result->label) {
    if(cJSON_AddStringToObject(item, "label", score_result->label) == NULL) {
    goto fail; //String
    }
    }


    // score_result->score
    if (!score_result->score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "score", score_result->score) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

score_result_t *score_result_parseFromJSON(cJSON *score_resultJSON){

    score_result_t *score_result_local_var = NULL;

    // define the local variable for score_result->evidence
    _t *evidence_local_nonprim = NULL;

    // score_result->evidence
    cJSON *evidence = cJSON_GetObjectItemCaseSensitive(score_resultJSON, "evidence");
    if (cJSON_IsNull(evidence)) {
        evidence = NULL;
    }
    if (!evidence) {
        goto end;
    }

    
    evidence_local_nonprim = _parseFromJSON(evidence); //custom

    // score_result->label
    cJSON *label = cJSON_GetObjectItemCaseSensitive(score_resultJSON, "label");
    if (cJSON_IsNull(label)) {
        label = NULL;
    }
    if (label) { 
    if(!cJSON_IsString(label) && !cJSON_IsNull(label))
    {
    goto end; //String
    }
    }

    // score_result->score
    cJSON *score = cJSON_GetObjectItemCaseSensitive(score_resultJSON, "score");
    if (cJSON_IsNull(score)) {
        score = NULL;
    }
    if (!score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(score))
    {
    goto end; //Numeric
    }


    score_result_local_var = score_result_create_internal (
        evidence_local_nonprim,
        label && !cJSON_IsNull(label) ? strdup(label->valuestring) : NULL,
        score->valuedouble
        );

    return score_result_local_var;
end:
    if (evidence_local_nonprim) {
        _free(evidence_local_nonprim);
        evidence_local_nonprim = NULL;
    }
    return NULL;

}
