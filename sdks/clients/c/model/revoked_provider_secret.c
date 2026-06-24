#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "revoked_provider_secret.h"



static revoked_provider_secret_t *revoked_provider_secret_create_internal(
    int active,
    char *provider_secret_id,
    char *rotated_at
    ) {
    revoked_provider_secret_t *revoked_provider_secret_local_var = malloc(sizeof(revoked_provider_secret_t));
    if (!revoked_provider_secret_local_var) {
        return NULL;
    }
    revoked_provider_secret_local_var->active = active;
    revoked_provider_secret_local_var->provider_secret_id = provider_secret_id;
    revoked_provider_secret_local_var->rotated_at = rotated_at;

    revoked_provider_secret_local_var->_library_owned = 1;
    return revoked_provider_secret_local_var;
}

__attribute__((deprecated)) revoked_provider_secret_t *revoked_provider_secret_create(
    int active,
    char *provider_secret_id,
    char *rotated_at
    ) {
    return revoked_provider_secret_create_internal (
        active,
        provider_secret_id,
        rotated_at
        );
}

void revoked_provider_secret_free(revoked_provider_secret_t *revoked_provider_secret) {
    if(NULL == revoked_provider_secret){
        return ;
    }
    if(revoked_provider_secret->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "revoked_provider_secret_free");
        return ;
    }
    listEntry_t *listEntry;
    if (revoked_provider_secret->provider_secret_id) {
        free(revoked_provider_secret->provider_secret_id);
        revoked_provider_secret->provider_secret_id = NULL;
    }
    if (revoked_provider_secret->rotated_at) {
        free(revoked_provider_secret->rotated_at);
        revoked_provider_secret->rotated_at = NULL;
    }
    free(revoked_provider_secret);
}

cJSON *revoked_provider_secret_convertToJSON(revoked_provider_secret_t *revoked_provider_secret) {
    cJSON *item = cJSON_CreateObject();

    // revoked_provider_secret->active
    if (!revoked_provider_secret->active) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "active", revoked_provider_secret->active) == NULL) {
    goto fail; //Bool
    }


    // revoked_provider_secret->provider_secret_id
    if (!revoked_provider_secret->provider_secret_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "provider_secret_id", revoked_provider_secret->provider_secret_id) == NULL) {
    goto fail; //String
    }


    // revoked_provider_secret->rotated_at
    if (!revoked_provider_secret->rotated_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "rotated_at", revoked_provider_secret->rotated_at) == NULL) {
    goto fail; //Date-Time
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

revoked_provider_secret_t *revoked_provider_secret_parseFromJSON(cJSON *revoked_provider_secretJSON){

    revoked_provider_secret_t *revoked_provider_secret_local_var = NULL;

    // revoked_provider_secret->active
    cJSON *active = cJSON_GetObjectItemCaseSensitive(revoked_provider_secretJSON, "active");
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

    // revoked_provider_secret->provider_secret_id
    cJSON *provider_secret_id = cJSON_GetObjectItemCaseSensitive(revoked_provider_secretJSON, "provider_secret_id");
    if (cJSON_IsNull(provider_secret_id)) {
        provider_secret_id = NULL;
    }
    if (!provider_secret_id) {
        goto end;
    }

    
    if(!cJSON_IsString(provider_secret_id))
    {
    goto end; //String
    }

    // revoked_provider_secret->rotated_at
    cJSON *rotated_at = cJSON_GetObjectItemCaseSensitive(revoked_provider_secretJSON, "rotated_at");
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


    revoked_provider_secret_local_var = revoked_provider_secret_create_internal (
        active->valueint,
        strdup(provider_secret_id->valuestring),
        strdup(rotated_at->valuestring)
        );

    return revoked_provider_secret_local_var;
end:
    return NULL;

}
