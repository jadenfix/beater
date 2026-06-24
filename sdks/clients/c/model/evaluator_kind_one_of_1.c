#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluator_kind_one_of_1.h"


char* evaluator_kind_one_of_1_type_ToString(beater_api_evaluator_kind_one_of_1_TYPE_e type) {
    char* typeArray[] =  { "NULL", "regex_match" };
    return typeArray[type];
}

beater_api_evaluator_kind_one_of_1_TYPE_e evaluator_kind_one_of_1_type_FromString(char* type){
    int stringToReturn = 0;
    char *typeArray[] =  { "NULL", "regex_match" };
    size_t sizeofArray = sizeof(typeArray) / sizeof(typeArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(type, typeArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

static evaluator_kind_one_of_1_t *evaluator_kind_one_of_1_create_internal(
    char *pattern,
    beater_api_evaluator_kind_one_of_1_TYPE_e type
    ) {
    evaluator_kind_one_of_1_t *evaluator_kind_one_of_1_local_var = malloc(sizeof(evaluator_kind_one_of_1_t));
    if (!evaluator_kind_one_of_1_local_var) {
        return NULL;
    }
    evaluator_kind_one_of_1_local_var->pattern = pattern;
    evaluator_kind_one_of_1_local_var->type = type;

    evaluator_kind_one_of_1_local_var->_library_owned = 1;
    return evaluator_kind_one_of_1_local_var;
}

__attribute__((deprecated)) evaluator_kind_one_of_1_t *evaluator_kind_one_of_1_create(
    char *pattern,
    beater_api_evaluator_kind_one_of_1_TYPE_e type
    ) {
    return evaluator_kind_one_of_1_create_internal (
        pattern,
        type
        );
}

void evaluator_kind_one_of_1_free(evaluator_kind_one_of_1_t *evaluator_kind_one_of_1) {
    if(NULL == evaluator_kind_one_of_1){
        return ;
    }
    if(evaluator_kind_one_of_1->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "evaluator_kind_one_of_1_free");
        return ;
    }
    listEntry_t *listEntry;
    if (evaluator_kind_one_of_1->pattern) {
        free(evaluator_kind_one_of_1->pattern);
        evaluator_kind_one_of_1->pattern = NULL;
    }
    free(evaluator_kind_one_of_1);
}

cJSON *evaluator_kind_one_of_1_convertToJSON(evaluator_kind_one_of_1_t *evaluator_kind_one_of_1) {
    cJSON *item = cJSON_CreateObject();

    // evaluator_kind_one_of_1->pattern
    if (!evaluator_kind_one_of_1->pattern) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "pattern", evaluator_kind_one_of_1->pattern) == NULL) {
    goto fail; //String
    }


    // evaluator_kind_one_of_1->type
    if (beater_api_evaluator_kind_one_of_1_TYPE_NULL == evaluator_kind_one_of_1->type) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "type", evaluator_kind_one_of_1_type_ToString(evaluator_kind_one_of_1->type)) == NULL)
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

evaluator_kind_one_of_1_t *evaluator_kind_one_of_1_parseFromJSON(cJSON *evaluator_kind_one_of_1JSON){

    evaluator_kind_one_of_1_t *evaluator_kind_one_of_1_local_var = NULL;

    // evaluator_kind_one_of_1->pattern
    cJSON *pattern = cJSON_GetObjectItemCaseSensitive(evaluator_kind_one_of_1JSON, "pattern");
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

    // evaluator_kind_one_of_1->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(evaluator_kind_one_of_1JSON, "type");
    if (cJSON_IsNull(type)) {
        type = NULL;
    }
    if (!type) {
        goto end;
    }

    beater_api_evaluator_kind_one_of_1_TYPE_e typeVariable;
    
    if(!cJSON_IsString(type))
    {
    goto end; //Enum
    }
    typeVariable = evaluator_kind_one_of_1_type_FromString(type->valuestring);


    evaluator_kind_one_of_1_local_var = evaluator_kind_one_of_1_create_internal (
        strdup(pattern->valuestring),
        typeVariable
        );

    return evaluator_kind_one_of_1_local_var;
end:
    return NULL;

}
