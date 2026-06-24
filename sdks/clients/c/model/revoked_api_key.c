#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "revoked_api_key.h"



static revoked_api_key_t *revoked_api_key_create_internal(
    int active,
    char *api_key_id,
    char *rotated_at
    ) {
    revoked_api_key_t *revoked_api_key_local_var = malloc(sizeof(revoked_api_key_t));
    if (!revoked_api_key_local_var) {
        return NULL;
    }
    revoked_api_key_local_var->active = active;
    revoked_api_key_local_var->api_key_id = api_key_id;
    revoked_api_key_local_var->rotated_at = rotated_at;

    revoked_api_key_local_var->_library_owned = 1;
    return revoked_api_key_local_var;
}

__attribute__((deprecated)) revoked_api_key_t *revoked_api_key_create(
    int active,
    char *api_key_id,
    char *rotated_at
    ) {
    return revoked_api_key_create_internal (
        active,
        api_key_id,
        rotated_at
        );
}

void revoked_api_key_free(revoked_api_key_t *revoked_api_key) {
    if(NULL == revoked_api_key){
        return ;
    }
    if(revoked_api_key->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "revoked_api_key_free");
        return ;
    }
    listEntry_t *listEntry;
    if (revoked_api_key->api_key_id) {
        free(revoked_api_key->api_key_id);
        revoked_api_key->api_key_id = NULL;
    }
    if (revoked_api_key->rotated_at) {
        free(revoked_api_key->rotated_at);
        revoked_api_key->rotated_at = NULL;
    }
    free(revoked_api_key);
}

cJSON *revoked_api_key_convertToJSON(revoked_api_key_t *revoked_api_key) {
    cJSON *item = cJSON_CreateObject();

    // revoked_api_key->active
    if (!revoked_api_key->active) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "active", revoked_api_key->active) == NULL) {
    goto fail; //Bool
    }


    // revoked_api_key->api_key_id
    if (!revoked_api_key->api_key_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "api_key_id", revoked_api_key->api_key_id) == NULL) {
    goto fail; //String
    }


    // revoked_api_key->rotated_at
    if (!revoked_api_key->rotated_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "rotated_at", revoked_api_key->rotated_at) == NULL) {
    goto fail; //Date-Time
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

revoked_api_key_t *revoked_api_key_parseFromJSON(cJSON *revoked_api_keyJSON){

    revoked_api_key_t *revoked_api_key_local_var = NULL;

    // revoked_api_key->active
    cJSON *active = cJSON_GetObjectItemCaseSensitive(revoked_api_keyJSON, "active");
    if (cJSON_IsNull(active)) {
        active = NULL;
    }
    if (!active) {
        goto end;
    }

    
    if(!cJSON_IsBool(active))
    {
    goto end; //Bool
    }

    // revoked_api_key->api_key_id
    cJSON *api_key_id = cJSON_GetObjectItemCaseSensitive(revoked_api_keyJSON, "api_key_id");
    if (cJSON_IsNull(api_key_id)) {
        api_key_id = NULL;
    }
    if (!api_key_id) {
        goto end;
    }

    
    if(!cJSON_IsString(api_key_id))
    {
    goto end; //String
    }

    // revoked_api_key->rotated_at
    cJSON *rotated_at = cJSON_GetObjectItemCaseSensitive(revoked_api_keyJSON, "rotated_at");
    if (cJSON_IsNull(rotated_at)) {
        rotated_at = NULL;
    }
    if (!rotated_at) {
        goto end;
    }

    
    if(!cJSON_IsString(rotated_at) && !cJSON_IsNull(rotated_at))
    {
    goto end; //DateTime
    }


    revoked_api_key_local_var = revoked_api_key_create_internal (
        active->valueint,
        strdup(api_key_id->valuestring),
        strdup(rotated_at->valuestring)
        );

    return revoked_api_key_local_var;
end:
    return NULL;

}
