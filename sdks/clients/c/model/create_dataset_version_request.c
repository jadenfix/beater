#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_dataset_version_request.h"



static create_dataset_version_request_t *create_dataset_version_request_create_internal(
    list_t *case_ids
    ) {
    create_dataset_version_request_t *create_dataset_version_request_local_var = malloc(sizeof(create_dataset_version_request_t));
    if (!create_dataset_version_request_local_var) {
        return NULL;
    }
    create_dataset_version_request_local_var->case_ids = case_ids;

    create_dataset_version_request_local_var->_library_owned = 1;
    return create_dataset_version_request_local_var;
}

__attribute__((deprecated)) create_dataset_version_request_t *create_dataset_version_request_create(
    list_t *case_ids
    ) {
    return create_dataset_version_request_create_internal (
        case_ids
        );
}

void create_dataset_version_request_free(create_dataset_version_request_t *create_dataset_version_request) {
    if(NULL == create_dataset_version_request){
        return ;
    }
    if(create_dataset_version_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "create_dataset_version_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (create_dataset_version_request->case_ids) {
        list_ForEach(listEntry, create_dataset_version_request->case_ids) {
            free(listEntry->data);
        }
        list_freeList(create_dataset_version_request->case_ids);
        create_dataset_version_request->case_ids = NULL;
    }
    free(create_dataset_version_request);
}

cJSON *create_dataset_version_request_convertToJSON(create_dataset_version_request_t *create_dataset_version_request) {
    cJSON *item = cJSON_CreateObject();

    // create_dataset_version_request->case_ids
    if(create_dataset_version_request->case_ids) {
    cJSON *case_ids = cJSON_AddArrayToObject(item, "case_ids");
    if(case_ids == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *case_idsListEntry;
    list_ForEach(case_idsListEntry, create_dataset_version_request->case_ids) {
    if(cJSON_AddStringToObject(case_ids, "", case_idsListEntry->data) == NULL)
    {
        goto fail;
    }
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

create_dataset_version_request_t *create_dataset_version_request_parseFromJSON(cJSON *create_dataset_version_requestJSON){

    create_dataset_version_request_t *create_dataset_version_request_local_var = NULL;

    // define the local list for create_dataset_version_request->case_ids
    list_t *case_idsList = NULL;

    // create_dataset_version_request->case_ids
    cJSON *case_ids = cJSON_GetObjectItemCaseSensitive(create_dataset_version_requestJSON, "case_ids");
    if (cJSON_IsNull(case_ids)) {
        case_ids = NULL;
    }
    if (case_ids) { 
    cJSON *case_ids_local = NULL;
    if(!cJSON_IsArray(case_ids)) {
        goto end;//primitive container
    }
    case_idsList = list_createList();

    cJSON_ArrayForEach(case_ids_local, case_ids)
    {
        if(!cJSON_IsString(case_ids_local))
        {
            goto end;
        }
        list_addElement(case_idsList , strdup(case_ids_local->valuestring));
    }
    }


    create_dataset_version_request_local_var = create_dataset_version_request_create_internal (
        case_ids ? case_idsList : NULL
        );

    return create_dataset_version_request_local_var;
end:
    if (case_idsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, case_idsList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(case_idsList);
        case_idsList = NULL;
    }
    return NULL;

}
