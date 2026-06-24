#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "auth_context.h"



static auth_context_t *auth_context_create_internal(
    char *api_key_id,
    list_t *scopes
    ) {
    auth_context_t *auth_context_local_var = malloc(sizeof(auth_context_t));
    if (!auth_context_local_var) {
        return NULL;
    }
    auth_context_local_var->api_key_id = api_key_id;
    auth_context_local_var->scopes = scopes;

    auth_context_local_var->_library_owned = 1;
    return auth_context_local_var;
}

__attribute__((deprecated)) auth_context_t *auth_context_create(
    char *api_key_id,
    list_t *scopes
    ) {
    return auth_context_create_internal (
        api_key_id,
        scopes
        );
}

void auth_context_free(auth_context_t *auth_context) {
    if(NULL == auth_context){
        return ;
    }
    if(auth_context->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "auth_context_free");
        return ;
    }
    listEntry_t *listEntry;
    if (auth_context->api_key_id) {
        free(auth_context->api_key_id);
        auth_context->api_key_id = NULL;
    }
    if (auth_context->scopes) {
        list_ForEach(listEntry, auth_context->scopes) {
            free(listEntry->data);
        }
        list_freeList(auth_context->scopes);
        auth_context->scopes = NULL;
    }
    free(auth_context);
}

cJSON *auth_context_convertToJSON(auth_context_t *auth_context) {
    cJSON *item = cJSON_CreateObject();

    // auth_context->api_key_id
    if(auth_context->api_key_id) {
    if(cJSON_AddStringToObject(item, "api_key_id", auth_context->api_key_id) == NULL) {
    goto fail; //String
    }
    }


    // auth_context->scopes
    if (!auth_context->scopes) {
        goto fail;
    }
    cJSON *scopes = cJSON_AddArrayToObject(item, "scopes");
    if(scopes == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *scopesListEntry;
    list_ForEach(scopesListEntry, auth_context->scopes) {
    if(cJSON_AddStringToObject(scopes, "", scopesListEntry->data) == NULL)
    {
        goto fail;
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

auth_context_t *auth_context_parseFromJSON(cJSON *auth_contextJSON){

    auth_context_t *auth_context_local_var = NULL;

    // define the local list for auth_context->scopes
    list_t *scopesList = NULL;

    // auth_context->api_key_id
    cJSON *api_key_id = cJSON_GetObjectItemCaseSensitive(auth_contextJSON, "api_key_id");
    if (cJSON_IsNull(api_key_id)) {
        api_key_id = NULL;
    }
    if (api_key_id) { 
    if(!cJSON_IsString(api_key_id) && !cJSON_IsNull(api_key_id))
    {
    goto end; //String
    }
    }

    // auth_context->scopes
    cJSON *scopes = cJSON_GetObjectItemCaseSensitive(auth_contextJSON, "scopes");
    if (cJSON_IsNull(scopes)) {
        scopes = NULL;
    }
    if (!scopes) {
        goto end;
    }

    
    cJSON *scopes_local = NULL;
    if(!cJSON_IsArray(scopes)) {
        goto end;//primitive container
    }
    scopesList = list_createList();

    cJSON_ArrayForEach(scopes_local, scopes)
    {
        if(!cJSON_IsString(scopes_local))
        {
            goto end;
        }
        list_addElement(scopesList , strdup(scopes_local->valuestring));
    }


    auth_context_local_var = auth_context_create_internal (
        api_key_id && !cJSON_IsNull(api_key_id) ? strdup(api_key_id->valuestring) : NULL,
        scopesList
        );

    return auth_context_local_var;
end:
    if (scopesList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, scopesList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(scopesList);
        scopesList = NULL;
    }
    return NULL;

}
