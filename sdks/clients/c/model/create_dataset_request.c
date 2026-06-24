#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_dataset_request.h"



static create_dataset_request_t *create_dataset_request_create_internal(
    char *name
    ) {
    create_dataset_request_t *create_dataset_request_local_var = malloc(sizeof(create_dataset_request_t));
    if (!create_dataset_request_local_var) {
        return NULL;
    }
    create_dataset_request_local_var->name = name;

    create_dataset_request_local_var->_library_owned = 1;
    return create_dataset_request_local_var;
}

__attribute__((deprecated)) create_dataset_request_t *create_dataset_request_create(
    char *name
    ) {
    return create_dataset_request_create_internal (
        name
        );
}

void create_dataset_request_free(create_dataset_request_t *create_dataset_request) {
    if(NULL == create_dataset_request){
        return ;
    }
    if(create_dataset_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "create_dataset_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (create_dataset_request->name) {
        free(create_dataset_request->name);
        create_dataset_request->name = NULL;
    }
    free(create_dataset_request);
}

cJSON *create_dataset_request_convertToJSON(create_dataset_request_t *create_dataset_request) {
    cJSON *item = cJSON_CreateObject();

    // create_dataset_request->name
    if (!create_dataset_request->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", create_dataset_request->name) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

create_dataset_request_t *create_dataset_request_parseFromJSON(cJSON *create_dataset_requestJSON){

    create_dataset_request_t *create_dataset_request_local_var = NULL;

    // create_dataset_request->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(create_dataset_requestJSON, "name");
    if (cJSON_IsNull(name)) {
        name = NULL;
    }
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }


    create_dataset_request_local_var = create_dataset_request_create_internal (
        strdup(name->valuestring)
        );

    return create_dataset_request_local_var;
end:
    return NULL;

}
