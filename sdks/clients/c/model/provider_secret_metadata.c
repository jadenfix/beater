#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "provider_secret_metadata.h"



static provider_secret_metadata_t *provider_secret_metadata_create_internal(
    int active,
    char *created_at,
    char *display_name,
    char *project_id,
    char *provider,
    char *provider_secret_id,
    char *rotated_at,
    char *tenant_id
    ) {
    provider_secret_metadata_t *provider_secret_metadata_local_var = malloc(sizeof(provider_secret_metadata_t));
    if (!provider_secret_metadata_local_var) {
        return NULL;
    }
    provider_secret_metadata_local_var->active = active;
    provider_secret_metadata_local_var->created_at = created_at;
    provider_secret_metadata_local_var->display_name = display_name;
    provider_secret_metadata_local_var->project_id = project_id;
    provider_secret_metadata_local_var->provider = provider;
    provider_secret_metadata_local_var->provider_secret_id = provider_secret_id;
    provider_secret_metadata_local_var->rotated_at = rotated_at;
    provider_secret_metadata_local_var->tenant_id = tenant_id;

    provider_secret_metadata_local_var->_library_owned = 1;
    return provider_secret_metadata_local_var;
}

__attribute__((deprecated)) provider_secret_metadata_t *provider_secret_metadata_create(
    int active,
    char *created_at,
    char *display_name,
    char *project_id,
    char *provider,
    char *provider_secret_id,
    char *rotated_at,
    char *tenant_id
    ) {
    return provider_secret_metadata_create_internal (
        active,
        created_at,
        display_name,
        project_id,
        provider,
        provider_secret_id,
        rotated_at,
        tenant_id
        );
}

void provider_secret_metadata_free(provider_secret_metadata_t *provider_secret_metadata) {
    if(NULL == provider_secret_metadata){
        return ;
    }
    if(provider_secret_metadata->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "provider_secret_metadata_free");
        return ;
    }
    listEntry_t *listEntry;
    if (provider_secret_metadata->created_at) {
        free(provider_secret_metadata->created_at);
        provider_secret_metadata->created_at = NULL;
    }
    if (provider_secret_metadata->display_name) {
        free(provider_secret_metadata->display_name);
        provider_secret_metadata->display_name = NULL;
    }
    if (provider_secret_metadata->project_id) {
        free(provider_secret_metadata->project_id);
        provider_secret_metadata->project_id = NULL;
    }
    if (provider_secret_metadata->provider) {
        free(provider_secret_metadata->provider);
        provider_secret_metadata->provider = NULL;
    }
    if (provider_secret_metadata->provider_secret_id) {
        free(provider_secret_metadata->provider_secret_id);
        provider_secret_metadata->provider_secret_id = NULL;
    }
    if (provider_secret_metadata->rotated_at) {
        free(provider_secret_metadata->rotated_at);
        provider_secret_metadata->rotated_at = NULL;
    }
    if (provider_secret_metadata->tenant_id) {
        free(provider_secret_metadata->tenant_id);
        provider_secret_metadata->tenant_id = NULL;
    }
    free(provider_secret_metadata);
}

cJSON *provider_secret_metadata_convertToJSON(provider_secret_metadata_t *provider_secret_metadata) {
    cJSON *item = cJSON_CreateObject();

    // provider_secret_metadata->active
    if (!provider_secret_metadata->active) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "active", provider_secret_metadata->active) == NULL) {
    goto fail; //Bool
    }


    // provider_secret_metadata->created_at
    if (!provider_secret_metadata->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", provider_secret_metadata->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // provider_secret_metadata->display_name
    if (!provider_secret_metadata->display_name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "display_name", provider_secret_metadata->display_name) == NULL) {
    goto fail; //String
    }


    // provider_secret_metadata->project_id
    if (!provider_secret_metadata->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", provider_secret_metadata->project_id) == NULL) {
    goto fail; //String
    }


    // provider_secret_metadata->provider
    if (!provider_secret_metadata->provider) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "provider", provider_secret_metadata->provider) == NULL) {
    goto fail; //String
    }


    // provider_secret_metadata->provider_secret_id
    if (!provider_secret_metadata->provider_secret_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "provider_secret_id", provider_secret_metadata->provider_secret_id) == NULL) {
    goto fail; //String
    }


    // provider_secret_metadata->rotated_at
    if(provider_secret_metadata->rotated_at) {
    if(cJSON_AddStringToObject(item, "rotated_at", provider_secret_metadata->rotated_at) == NULL) {
    goto fail; //Date-Time
    }
    }


    // provider_secret_metadata->tenant_id
    if (!provider_secret_metadata->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", provider_secret_metadata->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

provider_secret_metadata_t *provider_secret_metadata_parseFromJSON(cJSON *provider_secret_metadataJSON){

    provider_secret_metadata_t *provider_secret_metadata_local_var = NULL;

    // provider_secret_metadata->active
    cJSON *active = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "active");
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

    // provider_secret_metadata->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "created_at");
    if (cJSON_IsNull(created_at)) {
        created_at = NULL;
    }
    if (!created_at) {
        goto end;
    }

    
    if(!cJSON_IsString(created_at) && !cJSON_IsNull(created_at))
    {
    goto end; //DateTime
    }

    // provider_secret_metadata->display_name
    cJSON *display_name = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "display_name");
    if (cJSON_IsNull(display_name)) {
        display_name = NULL;
    }
    if (!display_name) {
        goto end;
    }

    
    if(!cJSON_IsString(display_name))
    {
    goto end; //String
    }

    // provider_secret_metadata->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "project_id");
    if (cJSON_IsNull(project_id)) {
        project_id = NULL;
    }
    if (!project_id) {
        goto end;
    }

    
    if(!cJSON_IsString(project_id))
    {
    goto end; //String
    }

    // provider_secret_metadata->provider
    cJSON *provider = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "provider");
    if (cJSON_IsNull(provider)) {
        provider = NULL;
    }
    if (!provider) {
        goto end;
    }

    
    if(!cJSON_IsString(provider))
    {
    goto end; //String
    }

    // provider_secret_metadata->provider_secret_id
    cJSON *provider_secret_id = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "provider_secret_id");
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

    // provider_secret_metadata->rotated_at
    cJSON *rotated_at = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "rotated_at");
    if (cJSON_IsNull(rotated_at)) {
        rotated_at = NULL;
    }
    if (rotated_at) { 
    if(!cJSON_IsString(rotated_at) && !cJSON_IsNull(rotated_at))
    {
    goto end; //DateTime
    }
    }

    // provider_secret_metadata->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(provider_secret_metadataJSON, "tenant_id");
    if (cJSON_IsNull(tenant_id)) {
        tenant_id = NULL;
    }
    if (!tenant_id) {
        goto end;
    }

    
    if(!cJSON_IsString(tenant_id))
    {
    goto end; //String
    }


    provider_secret_metadata_local_var = provider_secret_metadata_create_internal (
        active->valueint,
        strdup(created_at->valuestring),
        strdup(display_name->valuestring),
        strdup(project_id->valuestring),
        strdup(provider->valuestring),
        strdup(provider_secret_id->valuestring),
        rotated_at && !cJSON_IsNull(rotated_at) ? strdup(rotated_at->valuestring) : NULL,
        strdup(tenant_id->valuestring)
        );

    return provider_secret_metadata_local_var;
end:
    return NULL;

}
