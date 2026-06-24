#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trace_ingested_reconcile_report.h"



static trace_ingested_reconcile_report_t *trace_ingested_reconcile_report_create_internal(
    int downstream_accepted,
    int downstream_duplicate,
    int downstream_queued,
    char *project_id,
    int span_count,
    char *tenant_id,
    char *trace_id
    ) {
    trace_ingested_reconcile_report_t *trace_ingested_reconcile_report_local_var = malloc(sizeof(trace_ingested_reconcile_report_t));
    if (!trace_ingested_reconcile_report_local_var) {
        return NULL;
    }
    trace_ingested_reconcile_report_local_var->downstream_accepted = downstream_accepted;
    trace_ingested_reconcile_report_local_var->downstream_duplicate = downstream_duplicate;
    trace_ingested_reconcile_report_local_var->downstream_queued = downstream_queued;
    trace_ingested_reconcile_report_local_var->project_id = project_id;
    trace_ingested_reconcile_report_local_var->span_count = span_count;
    trace_ingested_reconcile_report_local_var->tenant_id = tenant_id;
    trace_ingested_reconcile_report_local_var->trace_id = trace_id;

    trace_ingested_reconcile_report_local_var->_library_owned = 1;
    return trace_ingested_reconcile_report_local_var;
}

__attribute__((deprecated)) trace_ingested_reconcile_report_t *trace_ingested_reconcile_report_create(
    int downstream_accepted,
    int downstream_duplicate,
    int downstream_queued,
    char *project_id,
    int span_count,
    char *tenant_id,
    char *trace_id
    ) {
    return trace_ingested_reconcile_report_create_internal (
        downstream_accepted,
        downstream_duplicate,
        downstream_queued,
        project_id,
        span_count,
        tenant_id,
        trace_id
        );
}

void trace_ingested_reconcile_report_free(trace_ingested_reconcile_report_t *trace_ingested_reconcile_report) {
    if(NULL == trace_ingested_reconcile_report){
        return ;
    }
    if(trace_ingested_reconcile_report->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "trace_ingested_reconcile_report_free");
        return ;
    }
    listEntry_t *listEntry;
    if (trace_ingested_reconcile_report->project_id) {
        free(trace_ingested_reconcile_report->project_id);
        trace_ingested_reconcile_report->project_id = NULL;
    }
    if (trace_ingested_reconcile_report->tenant_id) {
        free(trace_ingested_reconcile_report->tenant_id);
        trace_ingested_reconcile_report->tenant_id = NULL;
    }
    if (trace_ingested_reconcile_report->trace_id) {
        free(trace_ingested_reconcile_report->trace_id);
        trace_ingested_reconcile_report->trace_id = NULL;
    }
    free(trace_ingested_reconcile_report);
}

cJSON *trace_ingested_reconcile_report_convertToJSON(trace_ingested_reconcile_report_t *trace_ingested_reconcile_report) {
    cJSON *item = cJSON_CreateObject();

    // trace_ingested_reconcile_report->downstream_accepted
    if (!trace_ingested_reconcile_report->downstream_accepted) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "downstream_accepted", trace_ingested_reconcile_report->downstream_accepted) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_reconcile_report->downstream_duplicate
    if (!trace_ingested_reconcile_report->downstream_duplicate) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "downstream_duplicate", trace_ingested_reconcile_report->downstream_duplicate) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_reconcile_report->downstream_queued
    if (!trace_ingested_reconcile_report->downstream_queued) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "downstream_queued", trace_ingested_reconcile_report->downstream_queued) == NULL) {
    goto fail; //Bool
    }


    // trace_ingested_reconcile_report->project_id
    if (!trace_ingested_reconcile_report->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", trace_ingested_reconcile_report->project_id) == NULL) {
    goto fail; //String
    }


    // trace_ingested_reconcile_report->span_count
    if (!trace_ingested_reconcile_report->span_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "span_count", trace_ingested_reconcile_report->span_count) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_reconcile_report->tenant_id
    if (!trace_ingested_reconcile_report->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", trace_ingested_reconcile_report->tenant_id) == NULL) {
    goto fail; //String
    }


    // trace_ingested_reconcile_report->trace_id
    if (!trace_ingested_reconcile_report->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", trace_ingested_reconcile_report->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

trace_ingested_reconcile_report_t *trace_ingested_reconcile_report_parseFromJSON(cJSON *trace_ingested_reconcile_reportJSON){

    trace_ingested_reconcile_report_t *trace_ingested_reconcile_report_local_var = NULL;

    // trace_ingested_reconcile_report->downstream_accepted
    cJSON *downstream_accepted = cJSON_GetObjectItemCaseSensitive(trace_ingested_reconcile_reportJSON, "downstream_accepted");
    if (cJSON_IsNull(downstream_accepted)) {
        downstream_accepted = NULL;
    }
    if (!downstream_accepted) {
        goto end;
    }

    
    if(!cJSON_IsNumber(downstream_accepted))
    {
    goto end; //Numeric
    }

    // trace_ingested_reconcile_report->downstream_duplicate
    cJSON *downstream_duplicate = cJSON_GetObjectItemCaseSensitive(trace_ingested_reconcile_reportJSON, "downstream_duplicate");
    if (cJSON_IsNull(downstream_duplicate)) {
        downstream_duplicate = NULL;
    }
    if (!downstream_duplicate) {
        goto end;
    }

    
    if(!cJSON_IsNumber(downstream_duplicate))
    {
    goto end; //Numeric
    }

    // trace_ingested_reconcile_report->downstream_queued
    cJSON *downstream_queued = cJSON_GetObjectItemCaseSensitive(trace_ingested_reconcile_reportJSON, "downstream_queued");
    if (cJSON_IsNull(downstream_queued)) {
        downstream_queued = NULL;
    }
    if (!downstream_queued) {
        goto end;
    }

    
    if(!cJSON_IsBool(downstream_queued))
    {
    goto end; //Bool
    }

    // trace_ingested_reconcile_report->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(trace_ingested_reconcile_reportJSON, "project_id");
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

    // trace_ingested_reconcile_report->span_count
    cJSON *span_count = cJSON_GetObjectItemCaseSensitive(trace_ingested_reconcile_reportJSON, "span_count");
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

    // trace_ingested_reconcile_report->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(trace_ingested_reconcile_reportJSON, "tenant_id");
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

    // trace_ingested_reconcile_report->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(trace_ingested_reconcile_reportJSON, "trace_id");
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


    trace_ingested_reconcile_report_local_var = trace_ingested_reconcile_report_create_internal (
        downstream_accepted->valuedouble,
        downstream_duplicate->valuedouble,
        downstream_queued->valueint,
        strdup(project_id->valuestring),
        span_count->valuedouble,
        strdup(tenant_id->valuestring),
        strdup(trace_id->valuestring)
        );

    return trace_ingested_reconcile_report_local_var;
end:
    return NULL;

}
