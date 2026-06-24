#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "span_io_value.h"


char* span_io_value_kind_ToString(beater_api_span_io_value_KIND_e kind) {
    char* kindArray[] =  { "NULL", "missing" };
    return kindArray[kind];
}

beater_api_span_io_value_KIND_e span_io_value_kind_FromString(char* kind){
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

static span_io_value_t *span_io_value_create_internal(
    beater_api_span_io_value_KIND_e kind,
    any_type_t *value,
    artifact_ref_t *artifact_ref,
    char *reason
    ) {
    span_io_value_t *span_io_value_local_var = malloc(sizeof(span_io_value_t));
    if (!span_io_value_local_var) {
        return NULL;
    }
    span_io_value_local_var->kind = kind;
    span_io_value_local_var->value = value;
    span_io_value_local_var->artifact_ref = artifact_ref;
    span_io_value_local_var->reason = reason;

    span_io_value_local_var->_library_owned = 1;
    return span_io_value_local_var;
}

__attribute__((deprecated)) span_io_value_t *span_io_value_create(
    beater_api_span_io_value_KIND_e kind,
    any_type_t *value,
    artifact_ref_t *artifact_ref,
    char *reason
    ) {
    return span_io_value_create_internal (
        kind,
        value,
        artifact_ref,
        reason
        );
}

void span_io_value_free(span_io_value_t *span_io_value) {
    if(NULL == span_io_value){
        return ;
    }
    if(span_io_value->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "span_io_value_free");
        return ;
    }
    listEntry_t *listEntry;
    if (span_io_value->value) {
        _free(span_io_value->value);
        span_io_value->value = NULL;
    }
    if (span_io_value->artifact_ref) {
        artifact_ref_free(span_io_value->artifact_ref);
        span_io_value->artifact_ref = NULL;
    }
    if (span_io_value->reason) {
        free(span_io_value->reason);
        span_io_value->reason = NULL;
    }
    free(span_io_value);
}

cJSON *span_io_value_convertToJSON(span_io_value_t *span_io_value) {
    cJSON *item = cJSON_CreateObject();

    // span_io_value->kind
    if (beater_api_span_io_value_KIND_NULL == span_io_value->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", span_io_value_kind_ToString(span_io_value->kind)) == NULL)
    {
    goto fail; //Enum
    }


    // span_io_value->value
    if (!span_io_value->value) {
        goto fail;
    }
    cJSON *value_local_JSON = _convertToJSON(span_io_value->value);
    if(value_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "value", value_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // span_io_value->artifact_ref
    if (!span_io_value->artifact_ref) {
        goto fail;
    }
    cJSON *artifact_ref_local_JSON = artifact_ref_convertToJSON(span_io_value->artifact_ref);
    if(artifact_ref_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "artifact_ref", artifact_ref_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // span_io_value->reason
    if (!span_io_value->reason) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "reason", span_io_value->reason) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

span_io_value_t *span_io_value_parseFromJSON(cJSON *span_io_valueJSON){

    span_io_value_t *span_io_value_local_var = NULL;

    // define the local variable for span_io_value->value
    _t *value_local_nonprim = NULL;

    // define the local variable for span_io_value->artifact_ref
    artifact_ref_t *artifact_ref_local_nonprim = NULL;

    // span_io_value->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(span_io_valueJSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    beater_api_span_io_value_KIND_e kindVariable;
    
    if(!cJSON_IsString(kind))
    {
    goto end; //Enum
    }
    kindVariable = span_io_value_kind_FromString(kind->valuestring);

    // span_io_value->value
    cJSON *value = cJSON_GetObjectItemCaseSensitive(span_io_valueJSON, "value");
    if (cJSON_IsNull(value)) {
        value = NULL;
    }
    if (!value) {
        goto end;
    }

    
    value_local_nonprim = _parseFromJSON(value); //custom

    // span_io_value->artifact_ref
    cJSON *artifact_ref = cJSON_GetObjectItemCaseSensitive(span_io_valueJSON, "artifact_ref");
    if (cJSON_IsNull(artifact_ref)) {
        artifact_ref = NULL;
    }
    if (!artifact_ref) {
        goto end;
    }

    
    artifact_ref_local_nonprim = artifact_ref_parseFromJSON(artifact_ref); //nonprimitive

    // span_io_value->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(span_io_valueJSON, "reason");
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


    span_io_value_local_var = span_io_value_create_internal (
        kindVariable,
        value_local_nonprim,
        artifact_ref_local_nonprim,
        strdup(reason->valuestring)
        );

    return span_io_value_local_var;
end:
    if (value_local_nonprim) {
        _free(value_local_nonprim);
        value_local_nonprim = NULL;
    }
    if (artifact_ref_local_nonprim) {
        artifact_ref_free(artifact_ref_local_nonprim);
        artifact_ref_local_nonprim = NULL;
    }
    return NULL;

}
