#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "write_ack.h"



static write_ack_t *write_ack_create_internal(
    int accepted_raw,
    int accepted_spans,
    int duplicate_raw,
    int duplicate_spans
    ) {
    write_ack_t *write_ack_local_var = malloc(sizeof(write_ack_t));
    if (!write_ack_local_var) {
        return NULL;
    }
    write_ack_local_var->accepted_raw = accepted_raw;
    write_ack_local_var->accepted_spans = accepted_spans;
    write_ack_local_var->duplicate_raw = duplicate_raw;
    write_ack_local_var->duplicate_spans = duplicate_spans;

    write_ack_local_var->_library_owned = 1;
    return write_ack_local_var;
}

__attribute__((deprecated)) write_ack_t *write_ack_create(
    int accepted_raw,
    int accepted_spans,
    int duplicate_raw,
    int duplicate_spans
    ) {
    return write_ack_create_internal (
        accepted_raw,
        accepted_spans,
        duplicate_raw,
        duplicate_spans
        );
}

void write_ack_free(write_ack_t *write_ack) {
    if(NULL == write_ack){
        return ;
    }
    if(write_ack->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "write_ack_free");
        return ;
    }
    listEntry_t *listEntry;
    free(write_ack);
}

cJSON *write_ack_convertToJSON(write_ack_t *write_ack) {
    cJSON *item = cJSON_CreateObject();

    // write_ack->accepted_raw
    if (!write_ack->accepted_raw) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "accepted_raw", write_ack->accepted_raw) == NULL) {
    goto fail; //Numeric
    }


    // write_ack->accepted_spans
    if (!write_ack->accepted_spans) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "accepted_spans", write_ack->accepted_spans) == NULL) {
    goto fail; //Numeric
    }


    // write_ack->duplicate_raw
    if (!write_ack->duplicate_raw) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "duplicate_raw", write_ack->duplicate_raw) == NULL) {
    goto fail; //Numeric
    }


    // write_ack->duplicate_spans
    if (!write_ack->duplicate_spans) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "duplicate_spans", write_ack->duplicate_spans) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

write_ack_t *write_ack_parseFromJSON(cJSON *write_ackJSON){

    write_ack_t *write_ack_local_var = NULL;

    // write_ack->accepted_raw
    cJSON *accepted_raw = cJSON_GetObjectItemCaseSensitive(write_ackJSON, "accepted_raw");
    if (cJSON_IsNull(accepted_raw)) {
        accepted_raw = NULL;
    }
    if (!accepted_raw) {
        goto end;
    }

    
    if(!cJSON_IsNumber(accepted_raw))
    {
    goto end; //Numeric
    }

    // write_ack->accepted_spans
    cJSON *accepted_spans = cJSON_GetObjectItemCaseSensitive(write_ackJSON, "accepted_spans");
    if (cJSON_IsNull(accepted_spans)) {
        accepted_spans = NULL;
    }
    if (!accepted_spans) {
        goto end;
    }

    
    if(!cJSON_IsNumber(accepted_spans))
    {
    goto end; //Numeric
    }

    // write_ack->duplicate_raw
    cJSON *duplicate_raw = cJSON_GetObjectItemCaseSensitive(write_ackJSON, "duplicate_raw");
    if (cJSON_IsNull(duplicate_raw)) {
        duplicate_raw = NULL;
    }
    if (!duplicate_raw) {
        goto end;
    }

    
    if(!cJSON_IsNumber(duplicate_raw))
    {
    goto end; //Numeric
    }

    // write_ack->duplicate_spans
    cJSON *duplicate_spans = cJSON_GetObjectItemCaseSensitive(write_ackJSON, "duplicate_spans");
    if (cJSON_IsNull(duplicate_spans)) {
        duplicate_spans = NULL;
    }
    if (!duplicate_spans) {
        goto end;
    }

    
    if(!cJSON_IsNumber(duplicate_spans))
    {
    goto end; //Numeric
    }


    write_ack_local_var = write_ack_create_internal (
        accepted_raw->valuedouble,
        accepted_spans->valuedouble,
        duplicate_raw->valuedouble,
        duplicate_spans->valuedouble
        );

    return write_ack_local_var;
end:
    return NULL;

}
