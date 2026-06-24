#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_provider_secret_http_request.h"



static create_provider_secret_http_request_t *create_provider_secret_http_request_create_internal(
    char *display_name,
    char *provider,
    char *secret_value
    ) {
    create_provider_secret_http_request_t *create_provider_secret_http_request_local_var = malloc(sizeof(create_provider_secret_http_request_t));
    if (!create_provider_secret_http_request_local_var) {
        return NULL;
    }
    create_provider_secret_http_request_local_var->display_name = display_name;
    create_provider_secret_http_request_local_var->provider = provider;
    create_provider_secret_http_request_local_var->secret_value = secret_value;

    create_provider_secret_http_request_local_var->_library_owned = 1;
    return create_provider_secret_http_request_local_var;
}

__attribute__((deprecated)) create_provider_secret_http_request_t *create_provider_secret_http_request_create(
    char *display_name,
    char *provider,
    char *secret_value
    ) {
    return create_provider_secret_http_request_create_internal (
        display_name,
        provider,
        secret_value
        );
}

void create_provider_secret_http_request_free(create_provider_secret_http_request_t *create_provider_secret_http_request) {
    if(NULL == create_provider_secret_http_request){
        return ;
    }
    if(create_provider_secret_http_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "create_provider_secret_http_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (create_provider_secret_http_request->display_name) {
        free(create_provider_secret_http_request->display_name);
        create_provider_secret_http_request->display_name = NULL;
    }
    if (create_provider_secret_http_request->provider) {
        free(create_provider_secret_http_request->provider);
        create_provider_secret_http_request->provider = NULL;
    }
    if (create_provider_secret_http_request->secret_value) {
        free(create_provider_secret_http_request->secret_value);
        create_provider_secret_http_request->secret_value = NULL;
    }
    free(create_provider_secret_http_request);
}

cJSON *create_provider_secret_http_request_convertToJSON(create_provider_secret_http_request_t *create_provider_secret_http_request) {
    cJSON *item = cJSON_CreateObject();

    // create_provider_secret_http_request->display_name
    if (!create_provider_secret_http_request->display_name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "display_name", create_provider_secret_http_request->display_name) == NULL) {
    goto fail; //String
    }


    // create_provider_secret_http_request->provider
    if (!create_provider_secret_http_request->provider) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "provider", create_provider_secret_http_request->provider) == NULL) {
    goto fail; //String
    }


    // create_provider_secret_http_request->secret_value
    if (!create_provider_secret_http_request->secret_value) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "secret_value", create_provider_secret_http_request->secret_value) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

create_provider_secret_http_request_t *create_provider_secret_http_request_parseFromJSON(cJSON *create_provider_secret_http_requestJSON){

    create_provider_secret_http_request_t *create_provider_secret_http_request_local_var = NULL;

    // create_provider_secret_http_request->display_name
    cJSON *display_name = cJSON_GetObjectItemCaseSensitive(create_provider_secret_http_requestJSON, "display_name");
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

    // create_provider_secret_http_request->provider
    cJSON *provider = cJSON_GetObjectItemCaseSensitive(create_provider_secret_http_requestJSON, "provider");
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

    // create_provider_secret_http_request->secret_value
    cJSON *secret_value = cJSON_GetObjectItemCaseSensitive(create_provider_secret_http_requestJSON, "secret_value");
    if (cJSON_IsNull(secret_value)) {
        secret_value = NULL;
    }
    if (!secret_value) {
        goto end;
    }

    
    if(!cJSON_IsString(secret_value))
    {
    goto end; //String
    }


    create_provider_secret_http_request_local_var = create_provider_secret_http_request_create_internal (
        strdup(display_name->valuestring),
        strdup(provider->valuestring),
        strdup(secret_value->valuestring)
        );

    return create_provider_secret_http_request_local_var;
end:
    return NULL;

}
