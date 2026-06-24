#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "span_io_value_one_of_2.h"


char* span_io_value_one_of_2_kind_ToString(beater_api_span_io_value_one_of_2_KIND_e kind) {
    char* kindArray[] =  { "NULL", "redacted" };
    return kindArray[kind];
}

beater_api_span_io_value_one_of_2_KIND_e span_io_value_one_of_2_kind_FromString(char* kind){
    int stringToReturn = 0;
    char *kindArray[] =  { "NULL", "redacted" };
    size_t sizeofArray = sizeof(kindArray) / sizeof(kindArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(kind, kindArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

static span_io_value_one_of_2_t *span_io_value_one_of_2_create_internal(
    beater_api_span_io_value_one_of_2_KIND_e kind,
    char *reason
    ) {
    span_io_value_one_of_2_t *span_io_value_one_of_2_local_var = malloc(sizeof(span_io_value_one_of_2_t));
    if (!span_io_value_one_of_2_local_var) {
        return NULL;
    }
    span_io_value_one_of_2_local_var->kind = kind;
    span_io_value_one_of_2_local_var->reason = reason;

    span_io_value_one_of_2_local_var->_library_owned = 1;
    return span_io_value_one_of_2_local_var;
}

__attribute__((deprecated)) span_io_value_one_of_2_t *span_io_value_one_of_2_create(
    beater_api_span_io_value_one_of_2_KIND_e kind,
    char *reason
    ) {
    return span_io_value_one_of_2_create_internal (
        kind,
        reason
        );
}

void span_io_value_one_of_2_free(span_io_value_one_of_2_t *span_io_value_one_of_2) {
    if(NULL == span_io_value_one_of_2){
        return ;
    }
    if(span_io_value_one_of_2->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "span_io_value_one_of_2_free");
        return ;
    }
    listEntry_t *listEntry;
    if (span_io_value_one_of_2->reason) {
        free(span_io_value_one_of_2->reason);
        span_io_value_one_of_2->reason = NULL;
    }
    free(span_io_value_one_of_2);
}

cJSON *span_io_value_one_of_2_convertToJSON(span_io_value_one_of_2_t *span_io_value_one_of_2) {
    cJSON *item = cJSON_CreateObject();

    // span_io_value_one_of_2->kind
    if (beater_api_span_io_value_one_of_2_KIND_NULL == span_io_value_one_of_2->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", span_io_value_one_of_2_kind_ToString(span_io_value_one_of_2->kind)) == NULL)
    {
    goto fail; //Enum
    }


    // span_io_value_one_of_2->reason
    if (!span_io_value_one_of_2->reason) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "reason", span_io_value_one_of_2->reason) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

span_io_value_one_of_2_t *span_io_value_one_of_2_parseFromJSON(cJSON *span_io_value_one_of_2JSON){

    span_io_value_one_of_2_t *span_io_value_one_of_2_local_var = NULL;

    // span_io_value_one_of_2->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(span_io_value_one_of_2JSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    beater_api_span_io_value_one_of_2_KIND_e kindVariable;
    
    if(!cJSON_IsString(kind))
    {
    goto end; //Enum
    }
    kindVariable = span_io_value_one_of_2_kind_FromString(kind->valuestring);

    // span_io_value_one_of_2->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(span_io_value_one_of_2JSON, "reason");
    if (cJSON_IsNull(reason)) {
        reason = NULL;
    }
    if (!reason) {
        goto end;
    }

    
    if(!cJSON_IsString(reason))
    {
    goto end; //String
    }


    span_io_value_one_of_2_local_var = span_io_value_one_of_2_create_internal (
        kindVariable,
        strdup(reason->valuestring)
        );

    return span_io_value_one_of_2_local_var;
end:
    return NULL;

}
