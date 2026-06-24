#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dead_letter.h"



static dead_letter_t *dead_letter_create_internal(
    char *failed_at,
    bus_message_t *message,
    char *reason
    ) {
    dead_letter_t *dead_letter_local_var = malloc(sizeof(dead_letter_t));
    if (!dead_letter_local_var) {
        return NULL;
    }
    dead_letter_local_var->failed_at = failed_at;
    dead_letter_local_var->message = message;
    dead_letter_local_var->reason = reason;

    dead_letter_local_var->_library_owned = 1;
    return dead_letter_local_var;
}

__attribute__((deprecated)) dead_letter_t *dead_letter_create(
    char *failed_at,
    bus_message_t *message,
    char *reason
    ) {
    return dead_letter_create_internal (
        failed_at,
        message,
        reason
        );
}

void dead_letter_free(dead_letter_t *dead_letter) {
    if(NULL == dead_letter){
        return ;
    }
    if(dead_letter->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "dead_letter_free");
        return ;
    }
    listEntry_t *listEntry;
    if (dead_letter->failed_at) {
        free(dead_letter->failed_at);
        dead_letter->failed_at = NULL;
    }
    if (dead_letter->message) {
        bus_message_free(dead_letter->message);
        dead_letter->message = NULL;
    }
    if (dead_letter->reason) {
        free(dead_letter->reason);
        dead_letter->reason = NULL;
    }
    free(dead_letter);
}

cJSON *dead_letter_convertToJSON(dead_letter_t *dead_letter) {
    cJSON *item = cJSON_CreateObject();

    // dead_letter->failed_at
    if (!dead_letter->failed_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "failed_at", dead_letter->failed_at) == NULL) {
    goto fail; //Date-Time
    }


    // dead_letter->message
    if (!dead_letter->message) {
        goto fail;
    }
    cJSON *message_local_JSON = bus_message_convertToJSON(dead_letter->message);
    if(message_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "message", message_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // dead_letter->reason
    if (!dead_letter->reason) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "reason", dead_letter->reason) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

dead_letter_t *dead_letter_parseFromJSON(cJSON *dead_letterJSON){

    dead_letter_t *dead_letter_local_var = NULL;

    // define the local variable for dead_letter->message
    bus_message_t *message_local_nonprim = NULL;

    // dead_letter->failed_at
    cJSON *failed_at = cJSON_GetObjectItemCaseSensitive(dead_letterJSON, "failed_at");
    if (cJSON_IsNull(failed_at)) {
        failed_at = NULL;
    }
    if (!failed_at) {
        goto end;
    }

    
    if(!cJSON_IsString(failed_at) && !cJSON_IsNull(failed_at))
    {
    goto end; //DateTime
    }

    // dead_letter->message
    cJSON *message = cJSON_GetObjectItemCaseSensitive(dead_letterJSON, "message");
    if (cJSON_IsNull(message)) {
        message = NULL;
    }
    if (!message) {
        goto end;
    }

    
    message_local_nonprim = bus_message_parseFromJSON(message); //nonprimitive

    // dead_letter->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(dead_letterJSON, "reason");
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


    dead_letter_local_var = dead_letter_create_internal (
        strdup(failed_at->valuestring),
        message_local_nonprim,
        strdup(reason->valuestring)
        );

    return dead_letter_local_var;
end:
    if (message_local_nonprim) {
        bus_message_free(message_local_nonprim);
        message_local_nonprim = NULL;
    }
    return NULL;

}
