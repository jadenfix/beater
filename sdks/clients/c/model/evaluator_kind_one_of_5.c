#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluator_kind_one_of_5.h"


char* evaluator_kind_one_of_5_type_ToString(beater_api_evaluator_kind_one_of_5_TYPE_e type) {
    char* typeArray[] =  { "NULL", "llm_judge" };
    return typeArray[type];
}

beater_api_evaluator_kind_one_of_5_TYPE_e evaluator_kind_one_of_5_type_FromString(char* type){
    int stringToReturn = 0;
    char *typeArray[] =  { "NULL", "llm_judge" };
    size_t sizeofArray = sizeof(typeArray) / sizeof(typeArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(type, typeArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

static evaluator_kind_one_of_5_t *evaluator_kind_one_of_5_create_internal(
    char *model,
    char *rubric,
    beater_api_evaluator_kind_one_of_5_TYPE_e type
    ) {
    evaluator_kind_one_of_5_t *evaluator_kind_one_of_5_local_var = malloc(sizeof(evaluator_kind_one_of_5_t));
    if (!evaluator_kind_one_of_5_local_var) {
        return NULL;
    }
    evaluator_kind_one_of_5_local_var->model = model;
    evaluator_kind_one_of_5_local_var->rubric = rubric;
    evaluator_kind_one_of_5_local_var->type = type;

    evaluator_kind_one_of_5_local_var->_library_owned = 1;
    return evaluator_kind_one_of_5_local_var;
}

__attribute__((deprecated)) evaluator_kind_one_of_5_t *evaluator_kind_one_of_5_create(
    char *model,
    char *rubric,
    beater_api_evaluator_kind_one_of_5_TYPE_e type
    ) {
    return evaluator_kind_one_of_5_create_internal (
        model,
        rubric,
        type
        );
}

void evaluator_kind_one_of_5_free(evaluator_kind_one_of_5_t *evaluator_kind_one_of_5) {
    if(NULL == evaluator_kind_one_of_5){
        return ;
    }
    if(evaluator_kind_one_of_5->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "evaluator_kind_one_of_5_free");
        return ;
    }
    listEntry_t *listEntry;
    if (evaluator_kind_one_of_5->model) {
        free(evaluator_kind_one_of_5->model);
        evaluator_kind_one_of_5->model = NULL;
    }
    if (evaluator_kind_one_of_5->rubric) {
        free(evaluator_kind_one_of_5->rubric);
        evaluator_kind_one_of_5->rubric = NULL;
    }
    free(evaluator_kind_one_of_5);
}

cJSON *evaluator_kind_one_of_5_convertToJSON(evaluator_kind_one_of_5_t *evaluator_kind_one_of_5) {
    cJSON *item = cJSON_CreateObject();

    // evaluator_kind_one_of_5->model
    if (!evaluator_kind_one_of_5->model) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "model", evaluator_kind_one_of_5->model) == NULL) {
    goto fail; //String
    }


    // evaluator_kind_one_of_5->rubric
    if (!evaluator_kind_one_of_5->rubric) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "rubric", evaluator_kind_one_of_5->rubric) == NULL) {
    goto fail; //String
    }


    // evaluator_kind_one_of_5->type
    if (beater_api_evaluator_kind_one_of_5_TYPE_NULL == evaluator_kind_one_of_5->type) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "type", evaluator_kind_one_of_5_type_ToString(evaluator_kind_one_of_5->type)) == NULL)
    {
    goto fail; //Enum
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

evaluator_kind_one_of_5_t *evaluator_kind_one_of_5_parseFromJSON(cJSON *evaluator_kind_one_of_5JSON){

    evaluator_kind_one_of_5_t *evaluator_kind_one_of_5_local_var = NULL;

    // evaluator_kind_one_of_5->model
    cJSON *model = cJSON_GetObjectItemCaseSensitive(evaluator_kind_one_of_5JSON, "model");
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

    // evaluator_kind_one_of_5->rubric
    cJSON *rubric = cJSON_GetObjectItemCaseSensitive(evaluator_kind_one_of_5JSON, "rubric");
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

    // evaluator_kind_one_of_5->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(evaluator_kind_one_of_5JSON, "type");
    if (cJSON_IsNull(type)) {
        type = NULL;
    }
    if (!type) {
        goto end;
    }

    beater_api_evaluator_kind_one_of_5_TYPE_e typeVariable;
    
    if(!cJSON_IsString(type))
    {
    goto end; //Enum
    }
    typeVariable = evaluator_kind_one_of_5_type_FromString(type->valuestring);


    evaluator_kind_one_of_5_local_var = evaluator_kind_one_of_5_create_internal (
        strdup(model->valuestring),
        strdup(rubric->valuestring),
        typeVariable
        );

    return evaluator_kind_one_of_5_local_var;
end:
    return NULL;

}
