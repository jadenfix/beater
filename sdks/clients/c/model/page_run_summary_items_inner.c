#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "page_run_summary_items_inner.h"



static page_run_summary_items_inner_t *page_run_summary_items_inner_create_internal(
    long duration_ms,
    char *ended_at,
    char *first_span_name,
    list_t *models,
    char *project_id,
    list_t *release_ids,
    int span_count,
    char *started_at,
    beater_api_span_status__e status,
    char *tenant_id,
    money_t *total_cost,
    char *trace_id
    ) {
    page_run_summary_items_inner_t *page_run_summary_items_inner_local_var = malloc(sizeof(page_run_summary_items_inner_t));
    if (!page_run_summary_items_inner_local_var) {
        return NULL;
    }
    page_run_summary_items_inner_local_var->duration_ms = duration_ms;
    page_run_summary_items_inner_local_var->ended_at = ended_at;
    page_run_summary_items_inner_local_var->first_span_name = first_span_name;
    page_run_summary_items_inner_local_var->models = models;
    page_run_summary_items_inner_local_var->project_id = project_id;
    page_run_summary_items_inner_local_var->release_ids = release_ids;
    page_run_summary_items_inner_local_var->span_count = span_count;
    page_run_summary_items_inner_local_var->started_at = started_at;
    page_run_summary_items_inner_local_var->status = status;
    page_run_summary_items_inner_local_var->tenant_id = tenant_id;
    page_run_summary_items_inner_local_var->total_cost = total_cost;
    page_run_summary_items_inner_local_var->trace_id = trace_id;

    page_run_summary_items_inner_local_var->_library_owned = 1;
    return page_run_summary_items_inner_local_var;
}

__attribute__((deprecated)) page_run_summary_items_inner_t *page_run_summary_items_inner_create(
    long duration_ms,
    char *ended_at,
    char *first_span_name,
    list_t *models,
    char *project_id,
    list_t *release_ids,
    int span_count,
    char *started_at,
    beater_api_span_status__e status,
    char *tenant_id,
    money_t *total_cost,
    char *trace_id
    ) {
    return page_run_summary_items_inner_create_internal (
        duration_ms,
        ended_at,
        first_span_name,
        models,
        project_id,
        release_ids,
        span_count,
        started_at,
        status,
        tenant_id,
        total_cost,
        trace_id
        );
}

void page_run_summary_items_inner_free(page_run_summary_items_inner_t *page_run_summary_items_inner) {
    if(NULL == page_run_summary_items_inner){
        return ;
    }
    if(page_run_summary_items_inner->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "page_run_summary_items_inner_free");
        return ;
    }
    listEntry_t *listEntry;
    if (page_run_summary_items_inner->ended_at) {
        free(page_run_summary_items_inner->ended_at);
        page_run_summary_items_inner->ended_at = NULL;
    }
    if (page_run_summary_items_inner->first_span_name) {
        free(page_run_summary_items_inner->first_span_name);
        page_run_summary_items_inner->first_span_name = NULL;
    }
    if (page_run_summary_items_inner->models) {
        list_ForEach(listEntry, page_run_summary_items_inner->models) {
            model_ref_free(listEntry->data);
        }
        list_freeList(page_run_summary_items_inner->models);
        page_run_summary_items_inner->models = NULL;
    }
    if (page_run_summary_items_inner->project_id) {
        free(page_run_summary_items_inner->project_id);
        page_run_summary_items_inner->project_id = NULL;
    }
    if (page_run_summary_items_inner->release_ids) {
        list_ForEach(listEntry, page_run_summary_items_inner->release_ids) {
            free(listEntry->data);
        }
        list_freeList(page_run_summary_items_inner->release_ids);
        page_run_summary_items_inner->release_ids = NULL;
    }
    if (page_run_summary_items_inner->started_at) {
        free(page_run_summary_items_inner->started_at);
        page_run_summary_items_inner->started_at = NULL;
    }
    if (page_run_summary_items_inner->tenant_id) {
        free(page_run_summary_items_inner->tenant_id);
        page_run_summary_items_inner->tenant_id = NULL;
    }
    if (page_run_summary_items_inner->total_cost) {
        money_free(page_run_summary_items_inner->total_cost);
        page_run_summary_items_inner->total_cost = NULL;
    }
    if (page_run_summary_items_inner->trace_id) {
        free(page_run_summary_items_inner->trace_id);
        page_run_summary_items_inner->trace_id = NULL;
    }
    free(page_run_summary_items_inner);
}

cJSON *page_run_summary_items_inner_convertToJSON(page_run_summary_items_inner_t *page_run_summary_items_inner) {
    cJSON *item = cJSON_CreateObject();

    // page_run_summary_items_inner->duration_ms
    if(page_run_summary_items_inner->duration_ms) {
    if(cJSON_AddNumberToObject(item, "duration_ms", page_run_summary_items_inner->duration_ms) == NULL) {
    goto fail; //Numeric
    }
    }


    // page_run_summary_items_inner->ended_at
    if(page_run_summary_items_inner->ended_at) {
    if(cJSON_AddStringToObject(item, "ended_at", page_run_summary_items_inner->ended_at) == NULL) {
    goto fail; //Date-Time
    }
    }


    // page_run_summary_items_inner->first_span_name
    if (!page_run_summary_items_inner->first_span_name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "first_span_name", page_run_summary_items_inner->first_span_name) == NULL) {
    goto fail; //String
    }


    // page_run_summary_items_inner->models
    if (!page_run_summary_items_inner->models) {
        goto fail;
    }
    cJSON *models = cJSON_AddArrayToObject(item, "models");
    if(models == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *modelsListEntry;
    if (page_run_summary_items_inner->models) {
    list_ForEach(modelsListEntry, page_run_summary_items_inner->models) {
    cJSON *itemLocal = model_ref_convertToJSON(modelsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(models, itemLocal);
    }
    }


    // page_run_summary_items_inner->project_id
    if (!page_run_summary_items_inner->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", page_run_summary_items_inner->project_id) == NULL) {
    goto fail; //String
    }


    // page_run_summary_items_inner->release_ids
    if (!page_run_summary_items_inner->release_ids) {
        goto fail;
    }
    cJSON *release_ids = cJSON_AddArrayToObject(item, "release_ids");
    if(release_ids == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *release_idsListEntry;
    list_ForEach(release_idsListEntry, page_run_summary_items_inner->release_ids) {
    if(cJSON_AddStringToObject(release_ids, "", release_idsListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // page_run_summary_items_inner->span_count
    if (!page_run_summary_items_inner->span_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "span_count", page_run_summary_items_inner->span_count) == NULL) {
    goto fail; //Numeric
    }


    // page_run_summary_items_inner->started_at
    if (!page_run_summary_items_inner->started_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "started_at", page_run_summary_items_inner->started_at) == NULL) {
    goto fail; //Date-Time
    }


    // page_run_summary_items_inner->status
    if (beater_api_span_status__NULL == page_run_summary_items_inner->status) {
        goto fail;
    }
    cJSON *status_local_JSON = span_status_convertToJSON(page_run_summary_items_inner->status);
    if(status_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "status", status_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // page_run_summary_items_inner->tenant_id
    if (!page_run_summary_items_inner->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", page_run_summary_items_inner->tenant_id) == NULL) {
    goto fail; //String
    }


    // page_run_summary_items_inner->total_cost
    if(page_run_summary_items_inner->total_cost) {
    cJSON *total_cost_local_JSON = money_convertToJSON(page_run_summary_items_inner->total_cost);
    if(total_cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "total_cost", total_cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // page_run_summary_items_inner->trace_id
    if (!page_run_summary_items_inner->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", page_run_summary_items_inner->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

page_run_summary_items_inner_t *page_run_summary_items_inner_parseFromJSON(cJSON *page_run_summary_items_innerJSON){

    page_run_summary_items_inner_t *page_run_summary_items_inner_local_var = NULL;

    // define the local list for page_run_summary_items_inner->models
    list_t *modelsList = NULL;

    // define the local list for page_run_summary_items_inner->release_ids
    list_t *release_idsList = NULL;

    // define the local variable for page_run_summary_items_inner->status
    beater_api_span_status__e status_local_nonprim = 0;

    // define the local variable for page_run_summary_items_inner->total_cost
    money_t *total_cost_local_nonprim = NULL;

    // page_run_summary_items_inner->duration_ms
    cJSON *duration_ms = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "duration_ms");
    if (cJSON_IsNull(duration_ms)) {
        duration_ms = NULL;
    }
    if (duration_ms) { 
    if(!cJSON_IsNumber(duration_ms))
    {
    goto end; //Numeric
    }
    }

    // page_run_summary_items_inner->ended_at
    cJSON *ended_at = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "ended_at");
    if (cJSON_IsNull(ended_at)) {
        ended_at = NULL;
    }
    if (ended_at) { 
    if(!cJSON_IsString(ended_at) && !cJSON_IsNull(ended_at))
    {
    goto end; //DateTime
    }
    }

    // page_run_summary_items_inner->first_span_name
    cJSON *first_span_name = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "first_span_name");
    if (cJSON_IsNull(first_span_name)) {
        first_span_name = NULL;
    }
    if (!first_span_name) {
        goto end;
    }

    
    if(!cJSON_IsString(first_span_name))
    {
    goto end; //String
    }

    // page_run_summary_items_inner->models
    cJSON *models = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "models");
    if (cJSON_IsNull(models)) {
        models = NULL;
    }
    if (!models) {
        goto end;
    }

    
    cJSON *models_local_nonprimitive = NULL;
    if(!cJSON_IsArray(models)){
        goto end; //nonprimitive container
    }

    modelsList = list_createList();

    cJSON_ArrayForEach(models_local_nonprimitive,models )
    {
        if(!cJSON_IsObject(models_local_nonprimitive)){
            goto end;
        }
        model_ref_t *modelsItem = model_ref_parseFromJSON(models_local_nonprimitive);

        list_addElement(modelsList, modelsItem);
    }

    // page_run_summary_items_inner->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "project_id");
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

    // page_run_summary_items_inner->release_ids
    cJSON *release_ids = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "release_ids");
    if (cJSON_IsNull(release_ids)) {
        release_ids = NULL;
    }
    if (!release_ids) {
        goto end;
    }

    
    cJSON *release_ids_local = NULL;
    if(!cJSON_IsArray(release_ids)) {
        goto end;//primitive container
    }
    release_idsList = list_createList();

    cJSON_ArrayForEach(release_ids_local, release_ids)
    {
        if(!cJSON_IsString(release_ids_local))
        {
            goto end;
        }
        list_addElement(release_idsList , strdup(release_ids_local->valuestring));
    }

    // page_run_summary_items_inner->span_count
    cJSON *span_count = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "span_count");
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

    // page_run_summary_items_inner->started_at
    cJSON *started_at = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "started_at");
    if (cJSON_IsNull(started_at)) {
        started_at = NULL;
    }
    if (!started_at) {
        goto end;
    }

    
    if(!cJSON_IsString(started_at) && !cJSON_IsNull(started_at))
    {
    goto end; //DateTime
    }

    // page_run_summary_items_inner->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "status");
    if (cJSON_IsNull(status)) {
        status = NULL;
    }
    if (!status) {
        goto end;
    }

    
    status_local_nonprim = span_status_parseFromJSON(status); //custom

    // page_run_summary_items_inner->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "tenant_id");
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

    // page_run_summary_items_inner->total_cost
    cJSON *total_cost = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "total_cost");
    if (cJSON_IsNull(total_cost)) {
        total_cost = NULL;
    }
    if (total_cost) { 
    total_cost_local_nonprim = money_parseFromJSON(total_cost); //nonprimitive
    }

    // page_run_summary_items_inner->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(page_run_summary_items_innerJSON, "trace_id");
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


    page_run_summary_items_inner_local_var = page_run_summary_items_inner_create_internal (
        duration_ms ? duration_ms->valuedouble : 0,
        ended_at && !cJSON_IsNull(ended_at) ? strdup(ended_at->valuestring) : NULL,
        strdup(first_span_name->valuestring),
        modelsList,
        strdup(project_id->valuestring),
        release_idsList,
        span_count->valuedouble,
        strdup(started_at->valuestring),
        status_local_nonprim,
        strdup(tenant_id->valuestring),
        total_cost ? total_cost_local_nonprim : NULL,
        strdup(trace_id->valuestring)
        );

    return page_run_summary_items_inner_local_var;
end:
    if (modelsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, modelsList) {
            model_ref_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(modelsList);
        modelsList = NULL;
    }
    if (release_idsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, release_idsList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(release_idsList);
        release_idsList = NULL;
    }
    if (status_local_nonprim) {
        status_local_nonprim = 0;
    }
    if (total_cost_local_nonprim) {
        money_free(total_cost_local_nonprim);
        total_cost_local_nonprim = NULL;
    }
    return NULL;

}
