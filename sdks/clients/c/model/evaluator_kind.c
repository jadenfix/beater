#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluator_kind.h"


char* evaluator_kind_type_ToString(beater_api_evaluator_kind_TYPE_e type) {
    char* typeArray[] =  { "NULL", "exact_match", "regex_match", "json_object", "cost_budget", "latency_budget_ms", "llm_judge" };
    return typeArray[type];
}

beater_api_evaluator_kind_TYPE_e evaluator_kind_type_FromString(char* type){
    int stringToReturn = 0;
    char *typeArray[] =  { "NULL", "exact_match", "regex_match", "json_object", "cost_budget", "latency_budget_ms", "llm_judge" };
    size_t sizeofArray = sizeof(typeArray) / sizeof(typeArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(type, typeArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

static evaluator_kind_t *evaluator_kind_create_internal(
    beater_api_evaluator_kind_TYPE_e type,
    char *pattern,
    long max_micros,
    long max_ms,
    char *model,
    char *rubric
    ) {
    evaluator_kind_t *evaluator_kind_local_var = malloc(sizeof(evaluator_kind_t));
    if (!evaluator_kind_local_var) {
        return NULL;
    }
    evaluator_kind_local_var->type = type;
    evaluator_kind_local_var->pattern = pattern;
    evaluator_kind_local_var->max_micros = max_micros;
    evaluator_kind_local_var->max_ms = max_ms;
    evaluator_kind_local_var->model = model;
    evaluator_kind_local_var->rubric = rubric;

    evaluator_kind_local_var->_library_owned = 1;
    return evaluator_kind_local_var;
}

__attribute__((deprecated)) evaluator_kind_t *evaluator_kind_create(
    beater_api_evaluator_kind_TYPE_e type,
    char *pattern,
    long max_micros,
    long max_ms,
    char *model,
    char *rubric
    ) {
    return evaluator_kind_create_internal (
        type,
        pattern,
        max_micros,
        max_ms,
        model,
        rubric
        );
}

void evaluator_kind_free(evaluator_kind_t *evaluator_kind) {
    if(NULL == evaluator_kind){
        return ;
    }
    if(evaluator_kind->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "evaluator_kind_free");
        return ;
    }
    listEntry_t *listEntry;
    if (evaluator_kind->pattern) {
        free(evaluator_kind->pattern);
        evaluator_kind->pattern = NULL;
    }
    if (evaluator_kind->model) {
        free(evaluator_kind->model);
        evaluator_kind->model = NULL;
    }
    if (evaluator_kind->rubric) {
        free(evaluator_kind->rubric);
        evaluator_kind->rubric = NULL;
    }
    free(evaluator_kind);
}

cJSON *evaluator_kind_convertToJSON(evaluator_kind_t *evaluator_kind) {
    cJSON *item = cJSON_CreateObject();

    // evaluator_kind->type
    if (beater_api_evaluator_kind_TYPE_NULL == evaluator_kind->type) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "type", evaluator_kind_type_ToString(evaluator_kind->type)) == NULL)
    {
    goto fail; //Enum
    }


    // evaluator_kind->pattern
    if (!evaluator_kind->pattern) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "pattern", evaluator_kind->pattern) == NULL) {
    goto fail; //String
    }


    // evaluator_kind->max_micros
    if (!evaluator_kind->max_micros) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "max_micros", evaluator_kind->max_micros) == NULL) {
    goto fail; //Numeric
    }


    // evaluator_kind->max_ms
    if (!evaluator_kind->max_ms) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "max_ms", evaluator_kind->max_ms) == NULL) {
    goto fail; //Numeric
    }


    // evaluator_kind->model
    if (!evaluator_kind->model) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "model", evaluator_kind->model) == NULL) {
    goto fail; //String
    }


    // evaluator_kind->rubric
    if (!evaluator_kind->rubric) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "rubric", evaluator_kind->rubric) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

evaluator_kind_t *evaluator_kind_parseFromJSON(cJSON *evaluator_kindJSON){

    evaluator_kind_t *evaluator_kind_local_var = NULL;

    // evaluator_kind->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(evaluator_kindJSON, "type");
    if (cJSON_IsNull(type)) {
        type = NULL;
    }
    if (!type) {
        goto end;
    }

    beater_api_evaluator_kind_TYPE_e typeVariable;
    
    if(!cJSON_IsString(type))
    {
    goto end; //Enum
    }
    typeVariable = evaluator_kind_type_FromString(type->valuestring);

    // evaluator_kind->pattern
    cJSON *pattern = cJSON_GetObjectItemCaseSensitive(evaluator_kindJSON, "pattern");
    if (cJSON_IsNull(pattern)) {
        pattern = NULL;
    }
    if (!pattern) {
        goto end;
    }

    
    if(!cJSON_IsString(pattern))
    {
    goto end; //String
    }

    // evaluator_kind->max_micros
    cJSON *max_micros = cJSON_GetObjectItemCaseSensitive(evaluator_kindJSON, "max_micros");
    if (cJSON_IsNull(max_micros)) {
        max_micros = NULL;
    }
    if (!max_micros) {
        goto end;
    }

    
    if(!cJSON_IsNumber(max_micros))
    {
    goto end; //Numeric
    }

    // evaluator_kind->max_ms
    cJSON *max_ms = cJSON_GetObjectItemCaseSensitive(evaluator_kindJSON, "max_ms");
    if (cJSON_IsNull(max_ms)) {
        max_ms = NULL;
    }
    if (!max_ms) {
        goto end;
    }

    
    if(!cJSON_IsNumber(max_ms))
    {
    goto end; //Numeric
    }

    // evaluator_kind->model
    cJSON *model = cJSON_GetObjectItemCaseSensitive(evaluator_kindJSON, "model");
    if (cJSON_IsNull(model)) {
        model = NULL;
    }
    if (!model) {
        goto end;
    }

    
    if(!cJSON_IsString(model))
    {
    goto end; //String
    }

    // evaluator_kind->rubric
    cJSON *rubric = cJSON_GetObjectItemCaseSensitive(evaluator_kindJSON, "rubric");
    if (cJSON_IsNull(rubric)) {
        rubric = NULL;
    }
    if (!rubric) {
        goto end;
    }

    
    if(!cJSON_IsString(rubric))
    {
    goto end; //String
    }


    evaluator_kind_local_var = evaluator_kind_create_internal (
        typeVariable,
        strdup(pattern->valuestring),
        max_micros->valuedouble,
        max_ms->valuedouble,
        strdup(model->valuestring),
        strdup(rubric->valuestring)
        );

    return evaluator_kind_local_var;
end:
    return NULL;

}
