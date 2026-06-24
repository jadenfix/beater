#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ingest_queue_status.h"



static ingest_queue_status_t *ingest_queue_status_create_internal(
    list_t *dead_letters,
    char *project_id,
    char *tenant_id,
    int total_depth,
    int trace_ingested_depth,
    int trace_write_depth
    ) {
    ingest_queue_status_t *ingest_queue_status_local_var = malloc(sizeof(ingest_queue_status_t));
    if (!ingest_queue_status_local_var) {
        return NULL;
    }
    ingest_queue_status_local_var->dead_letters = dead_letters;
    ingest_queue_status_local_var->project_id = project_id;
    ingest_queue_status_local_var->tenant_id = tenant_id;
    ingest_queue_status_local_var->total_depth = total_depth;
    ingest_queue_status_local_var->trace_ingested_depth = trace_ingested_depth;
    ingest_queue_status_local_var->trace_write_depth = trace_write_depth;

    ingest_queue_status_local_var->_library_owned = 1;
    return ingest_queue_status_local_var;
}

__attribute__((deprecated)) ingest_queue_status_t *ingest_queue_status_create(
    list_t *dead_letters,
    char *project_id,
    char *tenant_id,
    int total_depth,
    int trace_ingested_depth,
    int trace_write_depth
    ) {
    return ingest_queue_status_create_internal (
        dead_letters,
        project_id,
        tenant_id,
        total_depth,
        trace_ingested_depth,
        trace_write_depth
        );
}

void ingest_queue_status_free(ingest_queue_status_t *ingest_queue_status) {
    if(NULL == ingest_queue_status){
        return ;
    }
    if(ingest_queue_status->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "ingest_queue_status_free");
        return ;
    }
    listEntry_t *listEntry;
    if (ingest_queue_status->dead_letters) {
        list_ForEach(listEntry, ingest_queue_status->dead_letters) {
            dead_letter_free(listEntry->data);
        }
        list_freeList(ingest_queue_status->dead_letters);
        ingest_queue_status->dead_letters = NULL;
    }
    if (ingest_queue_status->project_id) {
        free(ingest_queue_status->project_id);
        ingest_queue_status->project_id = NULL;
    }
    if (ingest_queue_status->tenant_id) {
        free(ingest_queue_status->tenant_id);
        ingest_queue_status->tenant_id = NULL;
    }
    free(ingest_queue_status);
}

cJSON *ingest_queue_status_convertToJSON(ingest_queue_status_t *ingest_queue_status) {
    cJSON *item = cJSON_CreateObject();

    // ingest_queue_status->dead_letters
    if (!ingest_queue_status->dead_letters) {
        goto fail;
    }
    cJSON *dead_letters = cJSON_AddArrayToObject(item, "dead_letters");
    if(dead_letters == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *dead_lettersListEntry;
    if (ingest_queue_status->dead_letters) {
    list_ForEach(dead_lettersListEntry, ingest_queue_status->dead_letters) {
    cJSON *itemLocal = dead_letter_convertToJSON(dead_lettersListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(dead_letters, itemLocal);
    }
    }


    // ingest_queue_status->project_id
    if (!ingest_queue_status->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", ingest_queue_status->project_id) == NULL) {
    goto fail; //String
    }


    // ingest_queue_status->tenant_id
    if (!ingest_queue_status->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", ingest_queue_status->tenant_id) == NULL) {
    goto fail; //String
    }


    // ingest_queue_status->total_depth
    if (!ingest_queue_status->total_depth) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "total_depth", ingest_queue_status->total_depth) == NULL) {
    goto fail; //Numeric
    }


    // ingest_queue_status->trace_ingested_depth
    if (!ingest_queue_status->trace_ingested_depth) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "trace_ingested_depth", ingest_queue_status->trace_ingested_depth) == NULL) {
    goto fail; //Numeric
    }


    // ingest_queue_status->trace_write_depth
    if (!ingest_queue_status->trace_write_depth) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "trace_write_depth", ingest_queue_status->trace_write_depth) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ingest_queue_status_t *ingest_queue_status_parseFromJSON(cJSON *ingest_queue_statusJSON){

    ingest_queue_status_t *ingest_queue_status_local_var = NULL;

    // define the local list for ingest_queue_status->dead_letters
    list_t *dead_lettersList = NULL;

    // ingest_queue_status->dead_letters
    cJSON *dead_letters = cJSON_GetObjectItemCaseSensitive(ingest_queue_statusJSON, "dead_letters");
    if (cJSON_IsNull(dead_letters)) {
        dead_letters = NULL;
    }
    if (!dead_letters) {
        goto end;
    }

    
    cJSON *dead_letters_local_nonprimitive = NULL;
    if(!cJSON_IsArray(dead_letters)){
        goto end; //nonprimitive container
    }

    dead_lettersList = list_createList();

    cJSON_ArrayForEach(dead_letters_local_nonprimitive,dead_letters )
    {
        if(!cJSON_IsObject(dead_letters_local_nonprimitive)){
            goto end;
        }
        dead_letter_t *dead_lettersItem = dead_letter_parseFromJSON(dead_letters_local_nonprimitive);

        list_addElement(dead_lettersList, dead_lettersItem);
    }

    // ingest_queue_status->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(ingest_queue_statusJSON, "project_id");
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

    // ingest_queue_status->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(ingest_queue_statusJSON, "tenant_id");
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

    // ingest_queue_status->total_depth
    cJSON *total_depth = cJSON_GetObjectItemCaseSensitive(ingest_queue_statusJSON, "total_depth");
    if (cJSON_IsNull(total_depth)) {
        total_depth = NULL;
    }
    if (!total_depth) {
        goto end;
    }

    
    if(!cJSON_IsNumber(total_depth))
    {
    goto end; //Numeric
    }

    // ingest_queue_status->trace_ingested_depth
    cJSON *trace_ingested_depth = cJSON_GetObjectItemCaseSensitive(ingest_queue_statusJSON, "trace_ingested_depth");
    if (cJSON_IsNull(trace_ingested_depth)) {
        trace_ingested_depth = NULL;
    }
    if (!trace_ingested_depth) {
        goto end;
    }

    
    if(!cJSON_IsNumber(trace_ingested_depth))
    {
    goto end; //Numeric
    }

    // ingest_queue_status->trace_write_depth
    cJSON *trace_write_depth = cJSON_GetObjectItemCaseSensitive(ingest_queue_statusJSON, "trace_write_depth");
    if (cJSON_IsNull(trace_write_depth)) {
        trace_write_depth = NULL;
    }
    if (!trace_write_depth) {
        goto end;
    }

    
    if(!cJSON_IsNumber(trace_write_depth))
    {
    goto end; //Numeric
    }


    ingest_queue_status_local_var = ingest_queue_status_create_internal (
        dead_lettersList,
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring),
        total_depth->valuedouble,
        trace_ingested_depth->valuedouble,
        trace_write_depth->valuedouble
        );

    return ingest_queue_status_local_var;
end:
    if (dead_lettersList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, dead_lettersList) {
            dead_letter_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(dead_lettersList);
        dead_lettersList = NULL;
    }
    return NULL;

}
