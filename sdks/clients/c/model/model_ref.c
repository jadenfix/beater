#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "model_ref.h"



static model_ref_t *model_ref_create_internal(
    char *name,
    char *provider
    ) {
    model_ref_t *model_ref_local_var = malloc(sizeof(model_ref_t));
    if (!model_ref_local_var) {
        return NULL;
    }
    model_ref_local_var->name = name;
    model_ref_local_var->provider = provider;

    model_ref_local_var->_library_owned = 1;
    return model_ref_local_var;
}

__attribute__((deprecated)) model_ref_t *model_ref_create(
    char *name,
    char *provider
    ) {
    return model_ref_create_internal (
        name,
        provider
        );
}

void model_ref_free(model_ref_t *model_ref) {
    if(NULL == model_ref){
        return ;
    }
    if(model_ref->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "model_ref_free");
        return ;
    }
    listEntry_t *listEntry;
    if (model_ref->name) {
        free(model_ref->name);
        model_ref->name = NULL;
    }
    if (model_ref->provider) {
        free(model_ref->provider);
        model_ref->provider = NULL;
    }
    free(model_ref);
}

cJSON *model_ref_convertToJSON(model_ref_t *model_ref) {
    cJSON *item = cJSON_CreateObject();

    // model_ref->name
    if (!model_ref->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", model_ref->name) == NULL) {
    goto fail; //String
    }


    // model_ref->provider
    if (!model_ref->provider) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "provider", model_ref->provider) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

model_ref_t *model_ref_parseFromJSON(cJSON *model_refJSON){

    model_ref_t *model_ref_local_var = NULL;

    // model_ref->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(model_refJSON, "name");
    if (cJSON_IsNull(name)) {
        name = NULL;
    }
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }

    // model_ref->provider
    cJSON *provider = cJSON_GetObjectItemCaseSensitive(model_refJSON, "provider");
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


    model_ref_local_var = model_ref_create_internal (
        strdup(name->valuestring),
        strdup(provider->valuestring)
        );

    return model_ref_local_var;
end:
    return NULL;

}
