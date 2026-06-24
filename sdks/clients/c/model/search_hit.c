#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "search_hit.h"



static search_hit_t *search_hit_create_internal(
    char *environment_id,
    char *kind,
    char *model,
    char *name,
    char *project_id,
    float score,
    char *span_id,
    char *status,
    char *tenant_id,
    char *tool,
    char *trace_id
    ) {
    search_hit_t *search_hit_local_var = malloc(sizeof(search_hit_t));
    if (!search_hit_local_var) {
        return NULL;
    }
    search_hit_local_var->environment_id = environment_id;
    search_hit_local_var->kind = kind;
    search_hit_local_var->model = model;
    search_hit_local_var->name = name;
    search_hit_local_var->project_id = project_id;
    search_hit_local_var->score = score;
    search_hit_local_var->span_id = span_id;
    search_hit_local_var->status = status;
    search_hit_local_var->tenant_id = tenant_id;
    search_hit_local_var->tool = tool;
    search_hit_local_var->trace_id = trace_id;

    search_hit_local_var->_library_owned = 1;
    return search_hit_local_var;
}

__attribute__((deprecated)) search_hit_t *search_hit_create(
    char *environment_id,
    char *kind,
    char *model,
    char *name,
    char *project_id,
    float score,
    char *span_id,
    char *status,
    char *tenant_id,
    char *tool,
    char *trace_id
    ) {
    return search_hit_create_internal (
        environment_id,
        kind,
        model,
        name,
        project_id,
        score,
        span_id,
        status,
        tenant_id,
        tool,
        trace_id
        );
}

void search_hit_free(search_hit_t *search_hit) {
    if(NULL == search_hit){
        return ;
    }
    if(search_hit->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "search_hit_free");
        return ;
    }
    listEntry_t *listEntry;
    if (search_hit->environment_id) {
        free(search_hit->environment_id);
        search_hit->environment_id = NULL;
    }
    if (search_hit->kind) {
        free(search_hit->kind);
        search_hit->kind = NULL;
    }
    if (search_hit->model) {
        free(search_hit->model);
        search_hit->model = NULL;
    }
    if (search_hit->name) {
        free(search_hit->name);
        search_hit->name = NULL;
    }
    if (search_hit->project_id) {
        free(search_hit->project_id);
        search_hit->project_id = NULL;
    }
    if (search_hit->span_id) {
        free(search_hit->span_id);
        search_hit->span_id = NULL;
    }
    if (search_hit->status) {
        free(search_hit->status);
        search_hit->status = NULL;
    }
    if (search_hit->tenant_id) {
        free(search_hit->tenant_id);
        search_hit->tenant_id = NULL;
    }
    if (search_hit->tool) {
        free(search_hit->tool);
        search_hit->tool = NULL;
    }
    if (search_hit->trace_id) {
        free(search_hit->trace_id);
        search_hit->trace_id = NULL;
    }
    free(search_hit);
}

cJSON *search_hit_convertToJSON(search_hit_t *search_hit) {
    cJSON *item = cJSON_CreateObject();

    // search_hit->environment_id
    if (!search_hit->environment_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "environment_id", search_hit->environment_id) == NULL) {
    goto fail; //String
    }


    // search_hit->kind
    if (!search_hit->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", search_hit->kind) == NULL) {
    goto fail; //String
    }


    // search_hit->model
    if (!search_hit->model) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "model", search_hit->model) == NULL) {
    goto fail; //String
    }


    // search_hit->name
    if (!search_hit->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", search_hit->name) == NULL) {
    goto fail; //String
    }


    // search_hit->project_id
    if (!search_hit->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", search_hit->project_id) == NULL) {
    goto fail; //String
    }


    // search_hit->score
    if (!search_hit->score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "score", search_hit->score) == NULL) {
    goto fail; //Numeric
    }


    // search_hit->span_id
    if (!search_hit->span_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "span_id", search_hit->span_id) == NULL) {
    goto fail; //String
    }


    // search_hit->status
    if (!search_hit->status) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "status", search_hit->status) == NULL) {
    goto fail; //String
    }


    // search_hit->tenant_id
    if (!search_hit->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", search_hit->tenant_id) == NULL) {
    goto fail; //String
    }


    // search_hit->tool
    if (!search_hit->tool) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tool", search_hit->tool) == NULL) {
    goto fail; //String
    }


    // search_hit->trace_id
    if (!search_hit->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", search_hit->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

search_hit_t *search_hit_parseFromJSON(cJSON *search_hitJSON){

    search_hit_t *search_hit_local_var = NULL;

    // search_hit->environment_id
    cJSON *environment_id = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "environment_id");
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

    // search_hit->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    
    if(!cJSON_IsString(kind))
    {
    goto end; //String
    }

    // search_hit->model
    cJSON *model = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "model");
    if (cJSON_IsNull(model)) {
        model = NULL;
    }
    if (!model) {
        goto end;
    }

    
    if(!cJSON_IsString(model))
    {
    goto end; //String
    }

    // search_hit->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "name");
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

    // search_hit->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "project_id");
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

    // search_hit->score
    cJSON *score = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "score");
    if (cJSON_IsNull(score)) {
        score = NULL;
    }
    if (!score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(score))
    {
    goto end; //Numeric
    }

    // search_hit->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "span_id");
    if (cJSON_IsNull(span_id)) {
        span_id = NULL;
    }
    if (!span_id) {
        goto end;
    }

    
    if(!cJSON_IsString(span_id))
    {
    goto end; //String
    }

    // search_hit->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "status");
    if (cJSON_IsNull(status)) {
        status = NULL;
    }
    if (!status) {
        goto end;
    }

    
    if(!cJSON_IsString(status))
    {
    goto end; //String
    }

    // search_hit->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "tenant_id");
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

    // search_hit->tool
    cJSON *tool = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "tool");
    if (cJSON_IsNull(tool)) {
        tool = NULL;
    }
    if (!tool) {
        goto end;
    }

    
    if(!cJSON_IsString(tool))
    {
    goto end; //String
    }

    // search_hit->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(search_hitJSON, "trace_id");
    if (cJSON_IsNull(trace_id)) {
        trace_id = NULL;
    }
    if (!trace_id) {
        goto end;
    }

    
    if(!cJSON_IsString(trace_id))
    {
    goto end; //String
    }


    search_hit_local_var = search_hit_create_internal (
        strdup(environment_id->valuestring),
        strdup(kind->valuestring),
        strdup(model->valuestring),
        strdup(name->valuestring),
        strdup(project_id->valuestring),
        score->valuedouble,
        strdup(span_id->valuestring),
        strdup(status->valuestring),
        strdup(tenant_id->valuestring),
        strdup(tool->valuestring),
        strdup(trace_id->valuestring)
        );

    return search_hit_local_var;
end:
    return NULL;

}
