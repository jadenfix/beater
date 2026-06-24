#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "span_io_value_one_of_1.h"


char* span_io_value_one_of_1_kind_ToString(beater_api_span_io_value_one_of_1_KIND_e kind) {
    char* kindArray[] =  { "NULL", "artifact" };
    return kindArray[kind];
}

beater_api_span_io_value_one_of_1_KIND_e span_io_value_one_of_1_kind_FromString(char* kind){
    int stringToReturn = 0;
    char *kindArray[] =  { "NULL", "artifact" };
    size_t sizeofArray = sizeof(kindArray) / sizeof(kindArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(kind, kindArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

static span_io_value_one_of_1_t *span_io_value_one_of_1_create_internal(
    artifact_ref_t *artifact_ref,
    beater_api_span_io_value_one_of_1_KIND_e kind
    ) {
    span_io_value_one_of_1_t *span_io_value_one_of_1_local_var = malloc(sizeof(span_io_value_one_of_1_t));
    if (!span_io_value_one_of_1_local_var) {
        return NULL;
    }
    span_io_value_one_of_1_local_var->artifact_ref = artifact_ref;
    span_io_value_one_of_1_local_var->kind = kind;

    span_io_value_one_of_1_local_var->_library_owned = 1;
    return span_io_value_one_of_1_local_var;
}

__attribute__((deprecated)) span_io_value_one_of_1_t *span_io_value_one_of_1_create(
    artifact_ref_t *artifact_ref,
    beater_api_span_io_value_one_of_1_KIND_e kind
    ) {
    return span_io_value_one_of_1_create_internal (
        artifact_ref,
        kind
        );
}

void span_io_value_one_of_1_free(span_io_value_one_of_1_t *span_io_value_one_of_1) {
    if(NULL == span_io_value_one_of_1){
        return ;
    }
    if(span_io_value_one_of_1->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "span_io_value_one_of_1_free");
        return ;
    }
    listEntry_t *listEntry;
    if (span_io_value_one_of_1->artifact_ref) {
        artifact_ref_free(span_io_value_one_of_1->artifact_ref);
        span_io_value_one_of_1->artifact_ref = NULL;
    }
    free(span_io_value_one_of_1);
}

cJSON *span_io_value_one_of_1_convertToJSON(span_io_value_one_of_1_t *span_io_value_one_of_1) {
    cJSON *item = cJSON_CreateObject();

    // span_io_value_one_of_1->artifact_ref
    if (!span_io_value_one_of_1->artifact_ref) {
        goto fail;
    }
    cJSON *artifact_ref_local_JSON = artifact_ref_convertToJSON(span_io_value_one_of_1->artifact_ref);
    if(artifact_ref_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "artifact_ref", artifact_ref_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // span_io_value_one_of_1->kind
    if (beater_api_span_io_value_one_of_1_KIND_NULL == span_io_value_one_of_1->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", span_io_value_one_of_1_kind_ToString(span_io_value_one_of_1->kind)) == NULL)
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

span_io_value_one_of_1_t *span_io_value_one_of_1_parseFromJSON(cJSON *span_io_value_one_of_1JSON){

    span_io_value_one_of_1_t *span_io_value_one_of_1_local_var = NULL;

    // define the local variable for span_io_value_one_of_1->artifact_ref
    artifact_ref_t *artifact_ref_local_nonprim = NULL;

    // span_io_value_one_of_1->artifact_ref
    cJSON *artifact_ref = cJSON_GetObjectItemCaseSensitive(span_io_value_one_of_1JSON, "artifact_ref");
    if (cJSON_IsNull(artifact_ref)) {
        artifact_ref = NULL;
    }
    if (!artifact_ref) {
        goto end;
    }

    
    artifact_ref_local_nonprim = artifact_ref_parseFromJSON(artifact_ref); //nonprimitive

    // span_io_value_one_of_1->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(span_io_value_one_of_1JSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    beater_api_span_io_value_one_of_1_KIND_e kindVariable;
    
    if(!cJSON_IsString(kind))
    {
    goto end; //Enum
    }
    kindVariable = span_io_value_one_of_1_kind_FromString(kind->valuestring);


    span_io_value_one_of_1_local_var = span_io_value_one_of_1_create_internal (
        artifact_ref_local_nonprim,
        kindVariable
        );

    return span_io_value_one_of_1_local_var;
end:
    if (artifact_ref_local_nonprim) {
        artifact_ref_free(artifact_ref_local_nonprim);
        artifact_ref_local_nonprim = NULL;
    }
    return NULL;

}
