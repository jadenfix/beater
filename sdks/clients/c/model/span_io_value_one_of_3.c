#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "span_io_value_one_of_3.h"


char* span_io_value_one_of_3_kind_ToString(beater_api_span_io_value_one_of_3_KIND_e kind) {
    char* kindArray[] =  { "NULL", "missing" };
    return kindArray[kind];
}

beater_api_span_io_value_one_of_3_KIND_e span_io_value_one_of_3_kind_FromString(char* kind){
    int stringToReturn = 0;
    char *kindArray[] =  { "NULL", "missing" };
    size_t sizeofArray = sizeof(kindArray) / sizeof(kindArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(kind, kindArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

static span_io_value_one_of_3_t *span_io_value_one_of_3_create_internal(
    beater_api_span_io_value_one_of_3_KIND_e kind
    ) {
    span_io_value_one_of_3_t *span_io_value_one_of_3_local_var = malloc(sizeof(span_io_value_one_of_3_t));
    if (!span_io_value_one_of_3_local_var) {
        return NULL;
    }
    span_io_value_one_of_3_local_var->kind = kind;

    span_io_value_one_of_3_local_var->_library_owned = 1;
    return span_io_value_one_of_3_local_var;
}

__attribute__((deprecated)) span_io_value_one_of_3_t *span_io_value_one_of_3_create(
    beater_api_span_io_value_one_of_3_KIND_e kind
    ) {
    return span_io_value_one_of_3_create_internal (
        kind
        );
}

void span_io_value_one_of_3_free(span_io_value_one_of_3_t *span_io_value_one_of_3) {
    if(NULL == span_io_value_one_of_3){
        return ;
    }
    if(span_io_value_one_of_3->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "span_io_value_one_of_3_free");
        return ;
    }
    listEntry_t *listEntry;
    free(span_io_value_one_of_3);
}

cJSON *span_io_value_one_of_3_convertToJSON(span_io_value_one_of_3_t *span_io_value_one_of_3) {
    cJSON *item = cJSON_CreateObject();

    // span_io_value_one_of_3->kind
    if (beater_api_span_io_value_one_of_3_KIND_NULL == span_io_value_one_of_3->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", span_io_value_one_of_3_kind_ToString(span_io_value_one_of_3->kind)) == NULL)
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

span_io_value_one_of_3_t *span_io_value_one_of_3_parseFromJSON(cJSON *span_io_value_one_of_3JSON){

    span_io_value_one_of_3_t *span_io_value_one_of_3_local_var = NULL;

    // span_io_value_one_of_3->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(span_io_value_one_of_3JSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    beater_api_span_io_value_one_of_3_KIND_e kindVariable;
    
    if(!cJSON_IsString(kind))
    {
    goto end; //Enum
    }
    kindVariable = span_io_value_one_of_3_kind_FromString(kind->valuestring);


    span_io_value_one_of_3_local_var = span_io_value_one_of_3_create_internal (
        kindVariable
        );

    return span_io_value_one_of_3_local_var;
end:
    return NULL;

}
