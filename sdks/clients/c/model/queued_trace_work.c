#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queued_trace_work.h"



static queued_trace_work_t *queued_trace_work_create_internal(
    char *project_id,
    char *tenant_id,
    char *trace_id
    ) {
    queued_trace_work_t *queued_trace_work_local_var = malloc(sizeof(queued_trace_work_t));
    if (!queued_trace_work_local_var) {
        return NULL;
    }
    queued_trace_work_local_var->project_id = project_id;
    queued_trace_work_local_var->tenant_id = tenant_id;
    queued_trace_work_local_var->trace_id = trace_id;

    queued_trace_work_local_var->_library_owned = 1;
    return queued_trace_work_local_var;
}

__attribute__((deprecated)) queued_trace_work_t *queued_trace_work_create(
    char *project_id,
    char *tenant_id,
    char *trace_id
    ) {
    return queued_trace_work_create_internal (
        project_id,
        tenant_id,
        trace_id
        );
}

void queued_trace_work_free(queued_trace_work_t *queued_trace_work) {
    if(NULL == queued_trace_work){
        return ;
    }
    if(queued_trace_work->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "queued_trace_work_free");
        return ;
    }
    listEntry_t *listEntry;
    if (queued_trace_work->project_id) {
        free(queued_trace_work->project_id);
        queued_trace_work->project_id = NULL;
    }
    if (queued_trace_work->tenant_id) {
        free(queued_trace_work->tenant_id);
        queued_trace_work->tenant_id = NULL;
    }
    if (queued_trace_work->trace_id) {
        free(queued_trace_work->trace_id);
        queued_trace_work->trace_id = NULL;
    }
    free(queued_trace_work);
}

cJSON *queued_trace_work_convertToJSON(queued_trace_work_t *queued_trace_work) {
    cJSON *item = cJSON_CreateObject();

    // queued_trace_work->project_id
    if (!queued_trace_work->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", queued_trace_work->project_id) == NULL) {
    goto fail; //String
    }


    // queued_trace_work->tenant_id
    if (!queued_trace_work->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", queued_trace_work->tenant_id) == NULL) {
    goto fail; //String
    }


    // queued_trace_work->trace_id
    if (!queued_trace_work->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", queued_trace_work->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

queued_trace_work_t *queued_trace_work_parseFromJSON(cJSON *queued_trace_workJSON){

    queued_trace_work_t *queued_trace_work_local_var = NULL;

    // queued_trace_work->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(queued_trace_workJSON, "project_id");
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

    // queued_trace_work->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(queued_trace_workJSON, "tenant_id");
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

    // queued_trace_work->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(queued_trace_workJSON, "trace_id");
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


    queued_trace_work_local_var = queued_trace_work_create_internal (
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring),
        strdup(trace_id->valuestring)
        );

    return queued_trace_work_local_var;
end:
    return NULL;

}
