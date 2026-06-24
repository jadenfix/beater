#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "span_io_value_one_of.h"


char* span_io_value_one_of_kind_ToString(beater_api_span_io_value_one_of_KIND_e kind) {
    char* kindArray[] =  { "NULL", "inline" };
    return kindArray[kind];
}

beater_api_span_io_value_one_of_KIND_e span_io_value_one_of_kind_FromString(char* kind){
    int stringToReturn = 0;
    char *kindArray[] =  { "NULL", "inline" };
    size_t sizeofArray = sizeof(kindArray) / sizeof(kindArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(kind, kindArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

static span_io_value_one_of_t *span_io_value_one_of_create_internal(
    beater_api_span_io_value_one_of_KIND_e kind,
    any_type_t *value
    ) {
    span_io_value_one_of_t *span_io_value_one_of_local_var = malloc(sizeof(span_io_value_one_of_t));
    if (!span_io_value_one_of_local_var) {
        return NULL;
    }
    span_io_value_one_of_local_var->kind = kind;
    span_io_value_one_of_local_var->value = value;

    span_io_value_one_of_local_var->_library_owned = 1;
    return span_io_value_one_of_local_var;
}

__attribute__((deprecated)) span_io_value_one_of_t *span_io_value_one_of_create(
    beater_api_span_io_value_one_of_KIND_e kind,
    any_type_t *value
    ) {
    return span_io_value_one_of_create_internal (
        kind,
        value
        );
}

void span_io_value_one_of_free(span_io_value_one_of_t *span_io_value_one_of) {
    if(NULL == span_io_value_one_of){
        return ;
    }
    if(span_io_value_one_of->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "span_io_value_one_of_free");
        return ;
    }
    listEntry_t *listEntry;
    if (span_io_value_one_of->value) {
        _free(span_io_value_one_of->value);
        span_io_value_one_of->value = NULL;
    }
    free(span_io_value_one_of);
}

cJSON *span_io_value_one_of_convertToJSON(span_io_value_one_of_t *span_io_value_one_of) {
    cJSON *item = cJSON_CreateObject();

    // span_io_value_one_of->kind
    if (beater_api_span_io_value_one_of_KIND_NULL == span_io_value_one_of->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", span_io_value_one_of_kind_ToString(span_io_value_one_of->kind)) == NULL)
    {
    goto fail; //Enum
    }


    // span_io_value_one_of->value
    if (!span_io_value_one_of->value) {
        goto fail;
    }
    cJSON *value_local_JSON = _convertToJSON(span_io_value_one_of->value);
    if(value_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "value", value_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

span_io_value_one_of_t *span_io_value_one_of_parseFromJSON(cJSON *span_io_value_one_ofJSON){

    span_io_value_one_of_t *span_io_value_one_of_local_var = NULL;

    // define the local variable for span_io_value_one_of->value
    _t *value_local_nonprim = NULL;

    // span_io_value_one_of->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(span_io_value_one_ofJSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    beater_api_span_io_value_one_of_KIND_e kindVariable;
    
    if(!cJSON_IsString(kind))
    {
    goto end; //Enum
    }
    kindVariable = span_io_value_one_of_kind_FromString(kind->valuestring);

    // span_io_value_one_of->value
    cJSON *value = cJSON_GetObjectItemCaseSensitive(span_io_value_one_ofJSON, "value");
    if (cJSON_IsNull(value)) {
        value = NULL;
    }
    if (!value) {
        goto end;
    }

    
    value_local_nonprim = _parseFromJSON(value); //custom


    span_io_value_one_of_local_var = span_io_value_one_of_create_internal (
        kindVariable,
        value_local_nonprim
        );

    return span_io_value_one_of_local_var;
end:
    if (value_local_nonprim) {
        _free(value_local_nonprim);
        value_local_nonprim = NULL;
    }
    return NULL;

}
