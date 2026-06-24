#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trace_view.h"



static trace_view_t *trace_view_create_internal(
    list_t *spans,
    char *tenant_id,
    char *trace_id
    ) {
    trace_view_t *trace_view_local_var = malloc(sizeof(trace_view_t));
    if (!trace_view_local_var) {
        return NULL;
    }
    trace_view_local_var->spans = spans;
    trace_view_local_var->tenant_id = tenant_id;
    trace_view_local_var->trace_id = trace_id;

    trace_view_local_var->_library_owned = 1;
    return trace_view_local_var;
}

__attribute__((deprecated)) trace_view_t *trace_view_create(
    list_t *spans,
    char *tenant_id,
    char *trace_id
    ) {
    return trace_view_create_internal (
        spans,
        tenant_id,
        trace_id
        );
}

void trace_view_free(trace_view_t *trace_view) {
    if(NULL == trace_view){
        return ;
    }
    if(trace_view->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "trace_view_free");
        return ;
    }
    listEntry_t *listEntry;
    if (trace_view->spans) {
        list_ForEach(listEntry, trace_view->spans) {
            canonical_span_free(listEntry->data);
        }
        list_freeList(trace_view->spans);
        trace_view->spans = NULL;
    }
    if (trace_view->tenant_id) {
        free(trace_view->tenant_id);
        trace_view->tenant_id = NULL;
    }
    if (trace_view->trace_id) {
        free(trace_view->trace_id);
        trace_view->trace_id = NULL;
    }
    free(trace_view);
}

cJSON *trace_view_convertToJSON(trace_view_t *trace_view) {
    cJSON *item = cJSON_CreateObject();

    // trace_view->spans
    if (!trace_view->spans) {
        goto fail;
    }
    cJSON *spans = cJSON_AddArrayToObject(item, "spans");
    if(spans == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *spansListEntry;
    if (trace_view->spans) {
    list_ForEach(spansListEntry, trace_view->spans) {
    cJSON *itemLocal = canonical_span_convertToJSON(spansListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(spans, itemLocal);
    }
    }


    // trace_view->tenant_id
    if (!trace_view->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", trace_view->tenant_id) == NULL) {
    goto fail; //String
    }


    // trace_view->trace_id
    if (!trace_view->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", trace_view->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

trace_view_t *trace_view_parseFromJSON(cJSON *trace_viewJSON){

    trace_view_t *trace_view_local_var = NULL;

    // define the local list for trace_view->spans
    list_t *spansList = NULL;

    // trace_view->spans
    cJSON *spans = cJSON_GetObjectItemCaseSensitive(trace_viewJSON, "spans");
    if (cJSON_IsNull(spans)) {
        spans = NULL;
    }
    if (!spans) {
        goto end;
    }

    
    cJSON *spans_local_nonprimitive = NULL;
    if(!cJSON_IsArray(spans)){
        goto end; //nonprimitive container
    }

    spansList = list_createList();

    cJSON_ArrayForEach(spans_local_nonprimitive,spans )
    {
        if(!cJSON_IsObject(spans_local_nonprimitive)){
            goto end;
        }
        canonical_span_t *spansItem = canonical_span_parseFromJSON(spans_local_nonprimitive);

        list_addElement(spansList, spansItem);
    }

    // trace_view->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(trace_viewJSON, "tenant_id");
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

    // trace_view->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(trace_viewJSON, "trace_id");
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


    trace_view_local_var = trace_view_create_internal (
        spansList,
        strdup(tenant_id->valuestring),
        strdup(trace_id->valuestring)
        );

    return trace_view_local_var;
end:
    if (spansList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, spansList) {
            canonical_span_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(spansList);
        spansList = NULL;
    }
    return NULL;

}
