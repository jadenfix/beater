#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "usage_summary.h"



static usage_summary_t *usage_summary_create_internal(
    char *project_id,
    char *tenant_id,
    list_t* totals
    ) {
    usage_summary_t *usage_summary_local_var = malloc(sizeof(usage_summary_t));
    if (!usage_summary_local_var) {
        return NULL;
    }
    usage_summary_local_var->project_id = project_id;
    usage_summary_local_var->tenant_id = tenant_id;
    usage_summary_local_var->totals = totals;

    usage_summary_local_var->_library_owned = 1;
    return usage_summary_local_var;
}

__attribute__((deprecated)) usage_summary_t *usage_summary_create(
    char *project_id,
    char *tenant_id,
    list_t* totals
    ) {
    return usage_summary_create_internal (
        project_id,
        tenant_id,
        totals
        );
}

void usage_summary_free(usage_summary_t *usage_summary) {
    if(NULL == usage_summary){
        return ;
    }
    if(usage_summary->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "usage_summary_free");
        return ;
    }
    listEntry_t *listEntry;
    if (usage_summary->project_id) {
        free(usage_summary->project_id);
        usage_summary->project_id = NULL;
    }
    if (usage_summary->tenant_id) {
        free(usage_summary->tenant_id);
        usage_summary->tenant_id = NULL;
    }
    if (usage_summary->totals) {
        list_ForEach(listEntry, usage_summary->totals) {
            keyValuePair_t *localKeyValue = listEntry->data;
            free (localKeyValue->key);
            free (localKeyValue->value);
            keyValuePair_free(localKeyValue);
        }
        list_freeList(usage_summary->totals);
        usage_summary->totals = NULL;
    }
    free(usage_summary);
}

cJSON *usage_summary_convertToJSON(usage_summary_t *usage_summary) {
    cJSON *item = cJSON_CreateObject();

    // usage_summary->project_id
    if (!usage_summary->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", usage_summary->project_id) == NULL) {
    goto fail; //String
    }


    // usage_summary->tenant_id
    if (!usage_summary->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", usage_summary->tenant_id) == NULL) {
    goto fail; //String
    }


    // usage_summary->totals
    if (!usage_summary->totals) {
        goto fail;
    }
    cJSON *totals = cJSON_AddObjectToObject(item, "totals");
    if(totals == NULL) {
        goto fail; //primitive map container
    }
    cJSON *localMapObject = totals;
    listEntry_t *totalsListEntry;
    if (usage_summary->totals) {
    list_ForEach(totalsListEntry, usage_summary->totals) {
        keyValuePair_t *localKeyValue = totalsListEntry->data;
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

usage_summary_t *usage_summary_parseFromJSON(cJSON *usage_summaryJSON){

    usage_summary_t *usage_summary_local_var = NULL;

    // define the local map for usage_summary->totals
    list_t *totalsList = NULL;

    // usage_summary->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(usage_summaryJSON, "project_id");
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

    // usage_summary->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(usage_summaryJSON, "tenant_id");
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

    // usage_summary->totals
    cJSON *totals = cJSON_GetObjectItemCaseSensitive(usage_summaryJSON, "totals");
    if (cJSON_IsNull(totals)) {
        totals = NULL;
    }
    if (!totals) {
        goto end;
    }

    
    cJSON *totals_local_map = NULL;
    if(!cJSON_IsObject(totals) && !cJSON_IsNull(totals))
    {
        goto end;//primitive map container
    }
    if(cJSON_IsObject(totals))
    {
        totalsList = list_createList();
        keyValuePair_t *localMapKeyPair;
        cJSON_ArrayForEach(totals_local_map, totals)
        {
            cJSON *localMapObject = totals_local_map;
            list_addElement(totalsList , localMapKeyPair);
        }
    }


    usage_summary_local_var = usage_summary_create_internal (
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring),
        totalsList
        );

    return usage_summary_local_var;
end:
    if (totalsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, totalsList) {
            keyValuePair_t *localKeyValue = listEntry->data;
            free(localKeyValue->key);
            localKeyValue->key = NULL;
            keyValuePair_free(localKeyValue);
            localKeyValue = NULL;
        }
        list_freeList(totalsList);
        totalsList = NULL;
    }
    return NULL;

}
