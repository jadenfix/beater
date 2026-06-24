#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dataset.h"



static dataset_t *dataset_create_internal(
    char *created_at,
    char *dataset_id,
    char *name,
    char *project_id,
    char *tenant_id
    ) {
    dataset_t *dataset_local_var = malloc(sizeof(dataset_t));
    if (!dataset_local_var) {
        return NULL;
    }
    dataset_local_var->created_at = created_at;
    dataset_local_var->dataset_id = dataset_id;
    dataset_local_var->name = name;
    dataset_local_var->project_id = project_id;
    dataset_local_var->tenant_id = tenant_id;

    dataset_local_var->_library_owned = 1;
    return dataset_local_var;
}

__attribute__((deprecated)) dataset_t *dataset_create(
    char *created_at,
    char *dataset_id,
    char *name,
    char *project_id,
    char *tenant_id
    ) {
    return dataset_create_internal (
        created_at,
        dataset_id,
        name,
        project_id,
        tenant_id
        );
}

void dataset_free(dataset_t *dataset) {
    if(NULL == dataset){
        return ;
    }
    if(dataset->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "dataset_free");
        return ;
    }
    listEntry_t *listEntry;
    if (dataset->created_at) {
        free(dataset->created_at);
        dataset->created_at = NULL;
    }
    if (dataset->dataset_id) {
        free(dataset->dataset_id);
        dataset->dataset_id = NULL;
    }
    if (dataset->name) {
        free(dataset->name);
        dataset->name = NULL;
    }
    if (dataset->project_id) {
        free(dataset->project_id);
        dataset->project_id = NULL;
    }
    if (dataset->tenant_id) {
        free(dataset->tenant_id);
        dataset->tenant_id = NULL;
    }
    free(dataset);
}

cJSON *dataset_convertToJSON(dataset_t *dataset) {
    cJSON *item = cJSON_CreateObject();

    // dataset->created_at
    if (!dataset->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", dataset->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // dataset->dataset_id
    if (!dataset->dataset_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_id", dataset->dataset_id) == NULL) {
    goto fail; //String
    }


    // dataset->name
    if (!dataset->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", dataset->name) == NULL) {
    goto fail; //String
    }


    // dataset->project_id
    if (!dataset->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", dataset->project_id) == NULL) {
    goto fail; //String
    }


    // dataset->tenant_id
    if (!dataset->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", dataset->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

dataset_t *dataset_parseFromJSON(cJSON *datasetJSON){

    dataset_t *dataset_local_var = NULL;

    // dataset->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(datasetJSON, "created_at");
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

    // dataset->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(datasetJSON, "dataset_id");
    if (cJSON_IsNull(dataset_id)) {
        dataset_id = NULL;
    }
    if (!dataset_id) {
        goto end;
    }

    
    if(!cJSON_IsString(dataset_id))
    {
    goto end; //String
    }

    // dataset->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(datasetJSON, "name");
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

    // dataset->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(datasetJSON, "project_id");
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

    // dataset->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(datasetJSON, "tenant_id");
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


    dataset_local_var = dataset_create_internal (
        strdup(created_at->valuestring),
        strdup(dataset_id->valuestring),
        strdup(name->valuestring),
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring)
        );

    return dataset_local_var;
end:
    return NULL;

}
