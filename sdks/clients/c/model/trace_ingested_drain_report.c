#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trace_ingested_drain_report.h"



static trace_ingested_drain_report_t *trace_ingested_drain_report_create_internal(
    int completed,
    int consumed,
    int dead_lettered,
    int failed_work,
    int invalid_messages,
    int retried,
    list_t *trace_refs
    ) {
    trace_ingested_drain_report_t *trace_ingested_drain_report_local_var = malloc(sizeof(trace_ingested_drain_report_t));
    if (!trace_ingested_drain_report_local_var) {
        return NULL;
    }
    trace_ingested_drain_report_local_var->completed = completed;
    trace_ingested_drain_report_local_var->consumed = consumed;
    trace_ingested_drain_report_local_var->dead_lettered = dead_lettered;
    trace_ingested_drain_report_local_var->failed_work = failed_work;
    trace_ingested_drain_report_local_var->invalid_messages = invalid_messages;
    trace_ingested_drain_report_local_var->retried = retried;
    trace_ingested_drain_report_local_var->trace_refs = trace_refs;

    trace_ingested_drain_report_local_var->_library_owned = 1;
    return trace_ingested_drain_report_local_var;
}

__attribute__((deprecated)) trace_ingested_drain_report_t *trace_ingested_drain_report_create(
    int completed,
    int consumed,
    int dead_lettered,
    int failed_work,
    int invalid_messages,
    int retried,
    list_t *trace_refs
    ) {
    return trace_ingested_drain_report_create_internal (
        completed,
        consumed,
        dead_lettered,
        failed_work,
        invalid_messages,
        retried,
        trace_refs
        );
}

void trace_ingested_drain_report_free(trace_ingested_drain_report_t *trace_ingested_drain_report) {
    if(NULL == trace_ingested_drain_report){
        return ;
    }
    if(trace_ingested_drain_report->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "trace_ingested_drain_report_free");
        return ;
    }
    listEntry_t *listEntry;
    if (trace_ingested_drain_report->trace_refs) {
        list_ForEach(listEntry, trace_ingested_drain_report->trace_refs) {
            queued_trace_work_free(listEntry->data);
        }
        list_freeList(trace_ingested_drain_report->trace_refs);
        trace_ingested_drain_report->trace_refs = NULL;
    }
    free(trace_ingested_drain_report);
}

cJSON *trace_ingested_drain_report_convertToJSON(trace_ingested_drain_report_t *trace_ingested_drain_report) {
    cJSON *item = cJSON_CreateObject();

    // trace_ingested_drain_report->completed
    if (!trace_ingested_drain_report->completed) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "completed", trace_ingested_drain_report->completed) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_drain_report->consumed
    if (!trace_ingested_drain_report->consumed) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "consumed", trace_ingested_drain_report->consumed) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_drain_report->dead_lettered
    if (!trace_ingested_drain_report->dead_lettered) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "dead_lettered", trace_ingested_drain_report->dead_lettered) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_drain_report->failed_work
    if (!trace_ingested_drain_report->failed_work) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "failed_work", trace_ingested_drain_report->failed_work) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_drain_report->invalid_messages
    if (!trace_ingested_drain_report->invalid_messages) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "invalid_messages", trace_ingested_drain_report->invalid_messages) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_drain_report->retried
    if (!trace_ingested_drain_report->retried) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "retried", trace_ingested_drain_report->retried) == NULL) {
    goto fail; //Numeric
    }


    // trace_ingested_drain_report->trace_refs
    if (!trace_ingested_drain_report->trace_refs) {
        goto fail;
    }
    cJSON *trace_refs = cJSON_AddArrayToObject(item, "trace_refs");
    if(trace_refs == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *trace_refsListEntry;
    if (trace_ingested_drain_report->trace_refs) {
    list_ForEach(trace_refsListEntry, trace_ingested_drain_report->trace_refs) {
    cJSON *itemLocal = queued_trace_work_convertToJSON(trace_refsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(trace_refs, itemLocal);
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

trace_ingested_drain_report_t *trace_ingested_drain_report_parseFromJSON(cJSON *trace_ingested_drain_reportJSON){

    trace_ingested_drain_report_t *trace_ingested_drain_report_local_var = NULL;

    // define the local list for trace_ingested_drain_report->trace_refs
    list_t *trace_refsList = NULL;

    // trace_ingested_drain_report->completed
    cJSON *completed = cJSON_GetObjectItemCaseSensitive(trace_ingested_drain_reportJSON, "completed");
    if (cJSON_IsNull(completed)) {
        completed = NULL;
    }
    if (!completed) {
        goto end;
    }

    
    if(!cJSON_IsNumber(completed))
    {
    goto end; //Numeric
    }

    // trace_ingested_drain_report->consumed
    cJSON *consumed = cJSON_GetObjectItemCaseSensitive(trace_ingested_drain_reportJSON, "consumed");
    if (cJSON_IsNull(consumed)) {
        consumed = NULL;
    }
    if (!consumed) {
        goto end;
    }

    
    if(!cJSON_IsNumber(consumed))
    {
    goto end; //Numeric
    }

    // trace_ingested_drain_report->dead_lettered
    cJSON *dead_lettered = cJSON_GetObjectItemCaseSensitive(trace_ingested_drain_reportJSON, "dead_lettered");
    if (cJSON_IsNull(dead_lettered)) {
        dead_lettered = NULL;
    }
    if (!dead_lettered) {
        goto end;
    }

    
    if(!cJSON_IsNumber(dead_lettered))
    {
    goto end; //Numeric
    }

    // trace_ingested_drain_report->failed_work
    cJSON *failed_work = cJSON_GetObjectItemCaseSensitive(trace_ingested_drain_reportJSON, "failed_work");
    if (cJSON_IsNull(failed_work)) {
        failed_work = NULL;
    }
    if (!failed_work) {
        goto end;
    }

    
    if(!cJSON_IsNumber(failed_work))
    {
    goto end; //Numeric
    }

    // trace_ingested_drain_report->invalid_messages
    cJSON *invalid_messages = cJSON_GetObjectItemCaseSensitive(trace_ingested_drain_reportJSON, "invalid_messages");
    if (cJSON_IsNull(invalid_messages)) {
        invalid_messages = NULL;
    }
    if (!invalid_messages) {
        goto end;
    }

    
    if(!cJSON_IsNumber(invalid_messages))
    {
    goto end; //Numeric
    }

    // trace_ingested_drain_report->retried
    cJSON *retried = cJSON_GetObjectItemCaseSensitive(trace_ingested_drain_reportJSON, "retried");
    if (cJSON_IsNull(retried)) {
        retried = NULL;
    }
    if (!retried) {
        goto end;
    }

    
    if(!cJSON_IsNumber(retried))
    {
    goto end; //Numeric
    }

    // trace_ingested_drain_report->trace_refs
    cJSON *trace_refs = cJSON_GetObjectItemCaseSensitive(trace_ingested_drain_reportJSON, "trace_refs");
    if (cJSON_IsNull(trace_refs)) {
        trace_refs = NULL;
    }
    if (!trace_refs) {
        goto end;
    }

    
    cJSON *trace_refs_local_nonprimitive = NULL;
    if(!cJSON_IsArray(trace_refs)){
        goto end; //nonprimitive container
    }

    trace_refsList = list_createList();

    cJSON_ArrayForEach(trace_refs_local_nonprimitive,trace_refs )
    {
        if(!cJSON_IsObject(trace_refs_local_nonprimitive)){
            goto end;
        }
        queued_trace_work_t *trace_refsItem = queued_trace_work_parseFromJSON(trace_refs_local_nonprimitive);

        list_addElement(trace_refsList, trace_refsItem);
    }


    trace_ingested_drain_report_local_var = trace_ingested_drain_report_create_internal (
        completed->valuedouble,
        consumed->valuedouble,
        dead_lettered->valuedouble,
        failed_work->valuedouble,
        invalid_messages->valuedouble,
        retried->valuedouble,
        trace_refsList
        );

    return trace_ingested_drain_report_local_var;
end:
    if (trace_refsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, trace_refsList) {
            queued_trace_work_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(trace_refsList);
        trace_refsList = NULL;
    }
    return NULL;

}
