#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tenant_scope.h"



static tenant_scope_t *tenant_scope_create_internal(
    char *environment_id,
    char *project_id,
    char *tenant_id
    ) {
    tenant_scope_t *tenant_scope_local_var = malloc(sizeof(tenant_scope_t));
    if (!tenant_scope_local_var) {
        return NULL;
    }
    tenant_scope_local_var->environment_id = environment_id;
    tenant_scope_local_var->project_id = project_id;
    tenant_scope_local_var->tenant_id = tenant_id;

    tenant_scope_local_var->_library_owned = 1;
    return tenant_scope_local_var;
}

__attribute__((deprecated)) tenant_scope_t *tenant_scope_create(
    char *environment_id,
    char *project_id,
    char *tenant_id
    ) {
    return tenant_scope_create_internal (
        environment_id,
        project_id,
        tenant_id
        );
}

void tenant_scope_free(tenant_scope_t *tenant_scope) {
    if(NULL == tenant_scope){
        return ;
    }
    if(tenant_scope->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "tenant_scope_free");
        return ;
    }
    listEntry_t *listEntry;
    if (tenant_scope->environment_id) {
        free(tenant_scope->environment_id);
        tenant_scope->environment_id = NULL;
    }
    if (tenant_scope->project_id) {
        free(tenant_scope->project_id);
        tenant_scope->project_id = NULL;
    }
    if (tenant_scope->tenant_id) {
        free(tenant_scope->tenant_id);
        tenant_scope->tenant_id = NULL;
    }
    free(tenant_scope);
}

cJSON *tenant_scope_convertToJSON(tenant_scope_t *tenant_scope) {
    cJSON *item = cJSON_CreateObject();

    // tenant_scope->environment_id
    if (!tenant_scope->environment_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "environment_id", tenant_scope->environment_id) == NULL) {
    goto fail; //String
    }


    // tenant_scope->project_id
    if (!tenant_scope->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", tenant_scope->project_id) == NULL) {
    goto fail; //String
    }


    // tenant_scope->tenant_id
    if (!tenant_scope->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", tenant_scope->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

tenant_scope_t *tenant_scope_parseFromJSON(cJSON *tenant_scopeJSON){

    tenant_scope_t *tenant_scope_local_var = NULL;

    // tenant_scope->environment_id
    cJSON *environment_id = cJSON_GetObjectItemCaseSensitive(tenant_scopeJSON, "environment_id");
    if (cJSON_IsNull(environment_id)) {
        environment_id = NULL;
    }
    if (!environment_id) {
        goto end;
    }

    
    if(!cJSON_IsString(environment_id))
    {
    goto end; //String
    }

    // tenant_scope->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(tenant_scopeJSON, "project_id");
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

    // tenant_scope->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(tenant_scopeJSON, "tenant_id");
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


    tenant_scope_local_var = tenant_scope_create_internal (
        strdup(environment_id->valuestring),
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring)
        );

    return tenant_scope_local_var;
end:
    return NULL;

}
