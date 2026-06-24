#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trace_write_drain_report.h"



static trace_write_drain_report_t *trace_write_drain_report_create_internal(
    int consumed,
    int dead_lettered,
    int downstream_published,
    int duplicate_raw,
    int duplicate_spans,
    int failed_downstream_publishes,
    int failed_writes,
    int invalid_messages,
    int retried,
    list_t *trace_ids,
    list_t *trace_refs,
    int written_raw,
    int written_spans
    ) {
    trace_write_drain_report_t *trace_write_drain_report_local_var = malloc(sizeof(trace_write_drain_report_t));
    if (!trace_write_drain_report_local_var) {
        return NULL;
    }
    trace_write_drain_report_local_var->consumed = consumed;
    trace_write_drain_report_local_var->dead_lettered = dead_lettered;
    trace_write_drain_report_local_var->downstream_published = downstream_published;
    trace_write_drain_report_local_var->duplicate_raw = duplicate_raw;
    trace_write_drain_report_local_var->duplicate_spans = duplicate_spans;
    trace_write_drain_report_local_var->failed_downstream_publishes = failed_downstream_publishes;
    trace_write_drain_report_local_var->failed_writes = failed_writes;
    trace_write_drain_report_local_var->invalid_messages = invalid_messages;
    trace_write_drain_report_local_var->retried = retried;
    trace_write_drain_report_local_var->trace_ids = trace_ids;
    trace_write_drain_report_local_var->trace_refs = trace_refs;
    trace_write_drain_report_local_var->written_raw = written_raw;
    trace_write_drain_report_local_var->written_spans = written_spans;

    trace_write_drain_report_local_var->_library_owned = 1;
    return trace_write_drain_report_local_var;
}

__attribute__((deprecated)) trace_write_drain_report_t *trace_write_drain_report_create(
    int consumed,
    int dead_lettered,
    int downstream_published,
    int duplicate_raw,
    int duplicate_spans,
    int failed_downstream_publishes,
    int failed_writes,
    int invalid_messages,
    int retried,
    list_t *trace_ids,
    list_t *trace_refs,
    int written_raw,
    int written_spans
    ) {
    return trace_write_drain_report_create_internal (
        consumed,
        dead_lettered,
        downstream_published,
        duplicate_raw,
        duplicate_spans,
        failed_downstream_publishes,
        failed_writes,
        invalid_messages,
        retried,
        trace_ids,
        trace_refs,
        written_raw,
        written_spans
        );
}

void trace_write_drain_report_free(trace_write_drain_report_t *trace_write_drain_report) {
    if(NULL == trace_write_drain_report){
        return ;
    }
    if(trace_write_drain_report->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "trace_write_drain_report_free");
        return ;
    }
    listEntry_t *listEntry;
    if (trace_write_drain_report->trace_ids) {
        list_ForEach(listEntry, trace_write_drain_report->trace_ids) {
            free(listEntry->data);
        }
        list_freeList(trace_write_drain_report->trace_ids);
        trace_write_drain_report->trace_ids = NULL;
    }
    if (trace_write_drain_report->trace_refs) {
        list_ForEach(listEntry, trace_write_drain_report->trace_refs) {
            queued_trace_work_free(listEntry->data);
        }
        list_freeList(trace_write_drain_report->trace_refs);
        trace_write_drain_report->trace_refs = NULL;
    }
    free(trace_write_drain_report);
}

cJSON *trace_write_drain_report_convertToJSON(trace_write_drain_report_t *trace_write_drain_report) {
    cJSON *item = cJSON_CreateObject();

    // trace_write_drain_report->consumed
    if (!trace_write_drain_report->consumed) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "consumed", trace_write_drain_report->consumed) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->dead_lettered
    if (!trace_write_drain_report->dead_lettered) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "dead_lettered", trace_write_drain_report->dead_lettered) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->downstream_published
    if (!trace_write_drain_report->downstream_published) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "downstream_published", trace_write_drain_report->downstream_published) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->duplicate_raw
    if (!trace_write_drain_report->duplicate_raw) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "duplicate_raw", trace_write_drain_report->duplicate_raw) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->duplicate_spans
    if (!trace_write_drain_report->duplicate_spans) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "duplicate_spans", trace_write_drain_report->duplicate_spans) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->failed_downstream_publishes
    if (!trace_write_drain_report->failed_downstream_publishes) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "failed_downstream_publishes", trace_write_drain_report->failed_downstream_publishes) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->failed_writes
    if (!trace_write_drain_report->failed_writes) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "failed_writes", trace_write_drain_report->failed_writes) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->invalid_messages
    if (!trace_write_drain_report->invalid_messages) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "invalid_messages", trace_write_drain_report->invalid_messages) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->retried
    if (!trace_write_drain_report->retried) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "retried", trace_write_drain_report->retried) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->trace_ids
    if (!trace_write_drain_report->trace_ids) {
        goto fail;
    }
    cJSON *trace_ids = cJSON_AddArrayToObject(item, "trace_ids");
    if(trace_ids == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *trace_idsListEntry;
    list_ForEach(trace_idsListEntry, trace_write_drain_report->trace_ids) {
    if(cJSON_AddStringToObject(trace_ids, "", trace_idsListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // trace_write_drain_report->trace_refs
    if (!trace_write_drain_report->trace_refs) {
        goto fail;
    }
    cJSON *trace_refs = cJSON_AddArrayToObject(item, "trace_refs");
    if(trace_refs == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *trace_refsListEntry;
    if (trace_write_drain_report->trace_refs) {
    list_ForEach(trace_refsListEntry, trace_write_drain_report->trace_refs) {
    cJSON *itemLocal = queued_trace_work_convertToJSON(trace_refsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(trace_refs, itemLocal);
    }
    }


    // trace_write_drain_report->written_raw
    if (!trace_write_drain_report->written_raw) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "written_raw", trace_write_drain_report->written_raw) == NULL) {
    goto fail; //Numeric
    }


    // trace_write_drain_report->written_spans
    if (!trace_write_drain_report->written_spans) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "written_spans", trace_write_drain_report->written_spans) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

trace_write_drain_report_t *trace_write_drain_report_parseFromJSON(cJSON *trace_write_drain_reportJSON){

    trace_write_drain_report_t *trace_write_drain_report_local_var = NULL;

    // define the local list for trace_write_drain_report->trace_ids
    list_t *trace_idsList = NULL;

    // define the local list for trace_write_drain_report->trace_refs
    list_t *trace_refsList = NULL;

    // trace_write_drain_report->consumed
    cJSON *consumed = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "consumed");
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

    // trace_write_drain_report->dead_lettered
    cJSON *dead_lettered = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "dead_lettered");
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

    // trace_write_drain_report->downstream_published
    cJSON *downstream_published = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "downstream_published");
    if (cJSON_IsNull(downstream_published)) {
        downstream_published = NULL;
    }
    if (!downstream_published) {
        goto end;
    }

    
    if(!cJSON_IsNumber(downstream_published))
    {
    goto end; //Numeric
    }

    // trace_write_drain_report->duplicate_raw
    cJSON *duplicate_raw = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "duplicate_raw");
    if (cJSON_IsNull(duplicate_raw)) {
        duplicate_raw = NULL;
    }
    if (!duplicate_raw) {
        goto end;
    }

    
    if(!cJSON_IsNumber(duplicate_raw))
    {
    goto end; //Numeric
    }

    // trace_write_drain_report->duplicate_spans
    cJSON *duplicate_spans = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "duplicate_spans");
    if (cJSON_IsNull(duplicate_spans)) {
        duplicate_spans = NULL;
    }
    if (!duplicate_spans) {
        goto end;
    }

    
    if(!cJSON_IsNumber(duplicate_spans))
    {
    goto end; //Numeric
    }

    // trace_write_drain_report->failed_downstream_publishes
    cJSON *failed_downstream_publishes = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "failed_downstream_publishes");
    if (cJSON_IsNull(failed_downstream_publishes)) {
        failed_downstream_publishes = NULL;
    }
    if (!failed_downstream_publishes) {
        goto end;
    }

    
    if(!cJSON_IsNumber(failed_downstream_publishes))
    {
    goto end; //Numeric
    }

    // trace_write_drain_report->failed_writes
    cJSON *failed_writes = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "failed_writes");
    if (cJSON_IsNull(failed_writes)) {
        failed_writes = NULL;
    }
    if (!failed_writes) {
        goto end;
    }

    
    if(!cJSON_IsNumber(failed_writes))
    {
    goto end; //Numeric
    }

    // trace_write_drain_report->invalid_messages
    cJSON *invalid_messages = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "invalid_messages");
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

    // trace_write_drain_report->retried
    cJSON *retried = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "retried");
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

    // trace_write_drain_report->trace_ids
    cJSON *trace_ids = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "trace_ids");
    if (cJSON_IsNull(trace_ids)) {
        trace_ids = NULL;
    }
    if (!trace_ids) {
        goto end;
    }

    
    cJSON *trace_ids_local = NULL;
    if(!cJSON_IsArray(trace_ids)) {
        goto end;//primitive container
    }
    trace_idsList = list_createList();

    cJSON_ArrayForEach(trace_ids_local, trace_ids)
    {
        if(!cJSON_IsString(trace_ids_local))
        {
            goto end;
        }
        list_addElement(trace_idsList , strdup(trace_ids_local->valuestring));
    }

    // trace_write_drain_report->trace_refs
    cJSON *trace_refs = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "trace_refs");
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

    // trace_write_drain_report->written_raw
    cJSON *written_raw = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "written_raw");
    if (cJSON_IsNull(written_raw)) {
        written_raw = NULL;
    }
    if (!written_raw) {
        goto end;
    }

    
    if(!cJSON_IsNumber(written_raw))
    {
    goto end; //Numeric
    }

    // trace_write_drain_report->written_spans
    cJSON *written_spans = cJSON_GetObjectItemCaseSensitive(trace_write_drain_reportJSON, "written_spans");
    if (cJSON_IsNull(written_spans)) {
        written_spans = NULL;
    }
    if (!written_spans) {
        goto end;
    }

    
    if(!cJSON_IsNumber(written_spans))
    {
    goto end; //Numeric
    }


    trace_write_drain_report_local_var = trace_write_drain_report_create_internal (
        consumed->valuedouble,
        dead_lettered->valuedouble,
        downstream_published->valuedouble,
        duplicate_raw->valuedouble,
        duplicate_spans->valuedouble,
        failed_downstream_publishes->valuedouble,
        failed_writes->valuedouble,
        invalid_messages->valuedouble,
        retried->valuedouble,
        trace_idsList,
        trace_refsList,
        written_raw->valuedouble,
        written_spans->valuedouble
        );

    return trace_write_drain_report_local_var;
end:
    if (trace_idsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, trace_idsList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(trace_idsList);
        trace_idsList = NULL;
    }
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
