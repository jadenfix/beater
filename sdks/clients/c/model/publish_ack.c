#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "publish_ack.h"



static publish_ack_t *publish_ack_create_internal(
    int accepted,
    int duplicate
    ) {
    publish_ack_t *publish_ack_local_var = malloc(sizeof(publish_ack_t));
    if (!publish_ack_local_var) {
        return NULL;
    }
    publish_ack_local_var->accepted = accepted;
    publish_ack_local_var->duplicate = duplicate;

    publish_ack_local_var->_library_owned = 1;
    return publish_ack_local_var;
}

__attribute__((deprecated)) publish_ack_t *publish_ack_create(
    int accepted,
    int duplicate
    ) {
    return publish_ack_create_internal (
        accepted,
        duplicate
        );
}

void publish_ack_free(publish_ack_t *publish_ack) {
    if(NULL == publish_ack){
        return ;
    }
    if(publish_ack->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "publish_ack_free");
        return ;
    }
    listEntry_t *listEntry;
    free(publish_ack);
}

cJSON *publish_ack_convertToJSON(publish_ack_t *publish_ack) {
    cJSON *item = cJSON_CreateObject();

    // publish_ack->accepted
    if (!publish_ack->accepted) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "accepted", publish_ack->accepted) == NULL) {
    goto fail; //Bool
    }


    // publish_ack->duplicate
    if (!publish_ack->duplicate) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "duplicate", publish_ack->duplicate) == NULL) {
    goto fail; //Bool
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

publish_ack_t *publish_ack_parseFromJSON(cJSON *publish_ackJSON){

    publish_ack_t *publish_ack_local_var = NULL;

    // publish_ack->accepted
    cJSON *accepted = cJSON_GetObjectItemCaseSensitive(publish_ackJSON, "accepted");
    if (cJSON_IsNull(accepted)) {
        accepted = NULL;
    }
    if (!accepted) {
        goto end;
    }

    
    if(!cJSON_IsBool(accepted))
    {
    goto end; //Bool
    }

    // publish_ack->duplicate
    cJSON *duplicate = cJSON_GetObjectItemCaseSensitive(publish_ackJSON, "duplicate");
    if (cJSON_IsNull(duplicate)) {
        duplicate = NULL;
    }
    if (!duplicate) {
        goto end;
    }

    
    if(!cJSON_IsBool(duplicate))
    {
    goto end; //Bool
    }


    publish_ack_local_var = publish_ack_create_internal (
        accepted->valueint,
        duplicate->valueint
        );

    return publish_ack_local_var;
end:
    return NULL;

}
