#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "archive_manifest.h"



static archive_manifest_t *archive_manifest_create_internal(
    char *created_at,
    char *path,
    char *project_id,
    int span_count,
    char *tenant_id
    ) {
    archive_manifest_t *archive_manifest_local_var = malloc(sizeof(archive_manifest_t));
    if (!archive_manifest_local_var) {
        return NULL;
    }
    archive_manifest_local_var->created_at = created_at;
    archive_manifest_local_var->path = path;
    archive_manifest_local_var->project_id = project_id;
    archive_manifest_local_var->span_count = span_count;
    archive_manifest_local_var->tenant_id = tenant_id;

    archive_manifest_local_var->_library_owned = 1;
    return archive_manifest_local_var;
}

__attribute__((deprecated)) archive_manifest_t *archive_manifest_create(
    char *created_at,
    char *path,
    char *project_id,
    int span_count,
    char *tenant_id
    ) {
    return archive_manifest_create_internal (
        created_at,
        path,
        project_id,
        span_count,
        tenant_id
        );
}

void archive_manifest_free(archive_manifest_t *archive_manifest) {
    if(NULL == archive_manifest){
        return ;
    }
    if(archive_manifest->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "archive_manifest_free");
        return ;
    }
    listEntry_t *listEntry;
    if (archive_manifest->created_at) {
        free(archive_manifest->created_at);
        archive_manifest->created_at = NULL;
    }
    if (archive_manifest->path) {
        free(archive_manifest->path);
        archive_manifest->path = NULL;
    }
    if (archive_manifest->project_id) {
        free(archive_manifest->project_id);
        archive_manifest->project_id = NULL;
    }
    if (archive_manifest->tenant_id) {
        free(archive_manifest->tenant_id);
        archive_manifest->tenant_id = NULL;
    }
    free(archive_manifest);
}

cJSON *archive_manifest_convertToJSON(archive_manifest_t *archive_manifest) {
    cJSON *item = cJSON_CreateObject();

    // archive_manifest->created_at
    if (!archive_manifest->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", archive_manifest->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // archive_manifest->path
    if (!archive_manifest->path) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "path", archive_manifest->path) == NULL) {
    goto fail; //String
    }


    // archive_manifest->project_id
    if (!archive_manifest->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", archive_manifest->project_id) == NULL) {
    goto fail; //String
    }


    // archive_manifest->span_count
    if (!archive_manifest->span_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "span_count", archive_manifest->span_count) == NULL) {
    goto fail; //Numeric
    }


    // archive_manifest->tenant_id
    if (!archive_manifest->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", archive_manifest->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

archive_manifest_t *archive_manifest_parseFromJSON(cJSON *archive_manifestJSON){

    archive_manifest_t *archive_manifest_local_var = NULL;

    // archive_manifest->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(archive_manifestJSON, "created_at");
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

    // archive_manifest->path
    cJSON *path = cJSON_GetObjectItemCaseSensitive(archive_manifestJSON, "path");
    if (cJSON_IsNull(path)) {
        path = NULL;
    }
    if (!path) {
        goto end;
    }

    
    if(!cJSON_IsString(path))
    {
    goto end; //String
    }

    // archive_manifest->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(archive_manifestJSON, "project_id");
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

    // archive_manifest->span_count
    cJSON *span_count = cJSON_GetObjectItemCaseSensitive(archive_manifestJSON, "span_count");
    if (cJSON_IsNull(span_count)) {
        span_count = NULL;
    }
    if (!span_count) {
        goto end;
    }

    
    if(!cJSON_IsNumber(span_count))
    {
    goto end; //Numeric
    }

    // archive_manifest->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(archive_manifestJSON, "tenant_id");
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


    archive_manifest_local_var = archive_manifest_create_internal (
        strdup(created_at->valuestring),
        strdup(path->valuestring),
        strdup(project_id->valuestring),
        span_count->valuedouble,
        strdup(tenant_id->valuestring)
        );

    return archive_manifest_local_var;
end:
    return NULL;

}
