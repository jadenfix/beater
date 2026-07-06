#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "run_summary.h"



static run_summary_t *run_summary_create_internal(
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
    rollup_estimate_t *total_cost_estimate_micros,
    char *trace_id
    ) {
    run_summary_t *run_summary_local_var = malloc(sizeof(run_summary_t));
    if (!run_summary_local_var) {
        return NULL;
    }
    run_summary_local_var->duration_ms = duration_ms;
    run_summary_local_var->ended_at = ended_at;
    run_summary_local_var->first_span_name = first_span_name;
    run_summary_local_var->models = models;
    run_summary_local_var->project_id = project_id;
    run_summary_local_var->release_ids = release_ids;
    run_summary_local_var->span_count = span_count;
    run_summary_local_var->started_at = started_at;
    run_summary_local_var->status = status;
    run_summary_local_var->tenant_id = tenant_id;
    run_summary_local_var->total_cost = total_cost;
    run_summary_local_var->total_cost_estimate_micros = total_cost_estimate_micros;
    run_summary_local_var->trace_id = trace_id;

    run_summary_local_var->_library_owned = 1;
    return run_summary_local_var;
}

__attribute__((deprecated)) run_summary_t *run_summary_create(
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
    rollup_estimate_t *total_cost_estimate_micros,
    char *trace_id
    ) {
    return run_summary_create_internal (
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
        total_cost_estimate_micros,
        trace_id
        );
}

void run_summary_free(run_summary_t *run_summary) {
    if(NULL == run_summary){
        return ;
    }
    if(run_summary->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "run_summary_free");
        return ;
    }
    listEntry_t *listEntry;
    if (run_summary->ended_at) {
        free(run_summary->ended_at);
        run_summary->ended_at = NULL;
    }
    if (run_summary->first_span_name) {
        free(run_summary->first_span_name);
        run_summary->first_span_name = NULL;
    }
    if (run_summary->models) {
        list_ForEach(listEntry, run_summary->models) {
            model_ref_free(listEntry->data);
        }
        list_freeList(run_summary->models);
        run_summary->models = NULL;
    }
    if (run_summary->project_id) {
        free(run_summary->project_id);
        run_summary->project_id = NULL;
    }
    if (run_summary->release_ids) {
        list_ForEach(listEntry, run_summary->release_ids) {
            free(listEntry->data);
        }
        list_freeList(run_summary->release_ids);
        run_summary->release_ids = NULL;
    }
    if (run_summary->started_at) {
        free(run_summary->started_at);
        run_summary->started_at = NULL;
    }
    if (run_summary->tenant_id) {
        free(run_summary->tenant_id);
        run_summary->tenant_id = NULL;
    }
    if (run_summary->total_cost) {
        money_free(run_summary->total_cost);
        run_summary->total_cost = NULL;
    }
    if (run_summary->total_cost_estimate_micros) {
        rollup_estimate_free(run_summary->total_cost_estimate_micros);
        run_summary->total_cost_estimate_micros = NULL;
    }
    if (run_summary->trace_id) {
        free(run_summary->trace_id);
        run_summary->trace_id = NULL;
    }
    free(run_summary);
}

cJSON *run_summary_convertToJSON(run_summary_t *run_summary) {
    cJSON *item = cJSON_CreateObject();

    // run_summary->duration_ms
    if(run_summary->duration_ms) {
    if(cJSON_AddNumberToObject(item, "duration_ms", run_summary->duration_ms) == NULL) {
    goto fail; //Numeric
    }
    }


    // run_summary->ended_at
    if(run_summary->ended_at) {
    if(cJSON_AddStringToObject(item, "ended_at", run_summary->ended_at) == NULL) {
    goto fail; //Date-Time
    }
    }


    // run_summary->first_span_name
    if (!run_summary->first_span_name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "first_span_name", run_summary->first_span_name) == NULL) {
    goto fail; //String
    }


    // run_summary->models
    if (!run_summary->models) {
        goto fail;
    }
    cJSON *models = cJSON_AddArrayToObject(item, "models");
    if(models == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *modelsListEntry;
    if (run_summary->models) {
    list_ForEach(modelsListEntry, run_summary->models) {
    cJSON *itemLocal = model_ref_convertToJSON(modelsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(models, itemLocal);
    }
    }


    // run_summary->project_id
    if (!run_summary->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", run_summary->project_id) == NULL) {
    goto fail; //String
    }


    // run_summary->release_ids
    if (!run_summary->release_ids) {
        goto fail;
    }
    cJSON *release_ids = cJSON_AddArrayToObject(item, "release_ids");
    if(release_ids == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *release_idsListEntry;
    list_ForEach(release_idsListEntry, run_summary->release_ids) {
    if(cJSON_AddStringToObject(release_ids, "", release_idsListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // run_summary->span_count
    if (!run_summary->span_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "span_count", run_summary->span_count) == NULL) {
    goto fail; //Numeric
    }


    // run_summary->started_at
    if (!run_summary->started_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "started_at", run_summary->started_at) == NULL) {
    goto fail; //Date-Time
    }


    // run_summary->status
    if (beater_api_span_status__NULL == run_summary->status) {
        goto fail;
    }
    cJSON *status_local_JSON = span_status_convertToJSON(run_summary->status);
    if(status_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "status", status_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // run_summary->tenant_id
    if (!run_summary->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", run_summary->tenant_id) == NULL) {
    goto fail; //String
    }


    // run_summary->total_cost
    if(run_summary->total_cost) {
    cJSON *total_cost_local_JSON = money_convertToJSON(run_summary->total_cost);
    if(total_cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "total_cost", total_cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // run_summary->total_cost_estimate_micros
    if(run_summary->total_cost_estimate_micros) {
    cJSON *total_cost_estimate_micros_local_JSON = rollup_estimate_convertToJSON(run_summary->total_cost_estimate_micros);
    if(total_cost_estimate_micros_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "total_cost_estimate_micros", total_cost_estimate_micros_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // run_summary->trace_id
    if (!run_summary->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", run_summary->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

run_summary_t *run_summary_parseFromJSON(cJSON *run_summaryJSON){

    run_summary_t *run_summary_local_var = NULL;

    // define the local list for run_summary->models
    list_t *modelsList = NULL;

    // define the local list for run_summary->release_ids
    list_t *release_idsList = NULL;

    // define the local variable for run_summary->status
    beater_api_span_status__e status_local_nonprim = 0;

    // define the local variable for run_summary->total_cost
    money_t *total_cost_local_nonprim = NULL;

    // define the local variable for run_summary->total_cost_estimate_micros
    rollup_estimate_t *total_cost_estimate_micros_local_nonprim = NULL;

    // run_summary->duration_ms
    cJSON *duration_ms = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "duration_ms");
    if (cJSON_IsNull(duration_ms)) {
        duration_ms = NULL;
    }
    if (duration_ms) {
    if(!cJSON_IsNumber(duration_ms))
    {
    goto end; //Numeric
    }
    }

    // run_summary->ended_at
    cJSON *ended_at = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "ended_at");
    if (cJSON_IsNull(ended_at)) {
        ended_at = NULL;
    }
    if (ended_at) {
    if(!cJSON_IsString(ended_at) && !cJSON_IsNull(ended_at))
    {
    goto end; //DateTime
    }
    }

    // run_summary->first_span_name
    cJSON *first_span_name = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "first_span_name");
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

    // run_summary->models
    cJSON *models = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "models");
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

    // run_summary->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "project_id");
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

    // run_summary->release_ids
    cJSON *release_ids = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "release_ids");
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

    // run_summary->span_count
    cJSON *span_count = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "span_count");
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

    // run_summary->started_at
    cJSON *started_at = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "started_at");
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

    // run_summary->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "status");
    if (cJSON_IsNull(status)) {
        status = NULL;
    }
    if (!status) {
        goto end;
    }


    status_local_nonprim = span_status_parseFromJSON(status); //custom

    // run_summary->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "tenant_id");
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

    // run_summary->total_cost
    cJSON *total_cost = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "total_cost");
    if (cJSON_IsNull(total_cost)) {
        total_cost = NULL;
    }
    if (total_cost) {
    total_cost_local_nonprim = money_parseFromJSON(total_cost); //nonprimitive
    }

    // run_summary->total_cost_estimate_micros
    cJSON *total_cost_estimate_micros = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "total_cost_estimate_micros");
    if (cJSON_IsNull(total_cost_estimate_micros)) {
        total_cost_estimate_micros = NULL;
    }
    if (total_cost_estimate_micros) {
    total_cost_estimate_micros_local_nonprim = rollup_estimate_parseFromJSON(total_cost_estimate_micros); //nonprimitive
    }

    // run_summary->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(run_summaryJSON, "trace_id");
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


    run_summary_local_var = run_summary_create_internal (
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
        total_cost_estimate_micros ? total_cost_estimate_micros_local_nonprim : NULL,
        strdup(trace_id->valuestring)
        );

    return run_summary_local_var;
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
    if (total_cost_estimate_micros_local_nonprim) {
        rollup_estimate_free(total_cost_estimate_micros_local_nonprim);
        total_cost_estimate_micros_local_nonprim = NULL;
    }
    return NULL;

}
