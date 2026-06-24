#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "health_response.h"



static health_response_t *health_response_create_internal(
    int ok
    ) {
    health_response_t *health_response_local_var = malloc(sizeof(health_response_t));
    if (!health_response_local_var) {
        return NULL;
    }
    health_response_local_var->ok = ok;

    health_response_local_var->_library_owned = 1;
    return health_response_local_var;
}

__attribute__((deprecated)) health_response_t *health_response_create(
    int ok
    ) {
    return health_response_create_internal (
        ok
        );
}

void health_response_free(health_response_t *health_response) {
    if(NULL == health_response){
        return ;
    }
    if(health_response->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "health_response_free");
        return ;
    }
    listEntry_t *listEntry;
    free(health_response);
}

cJSON *health_response_convertToJSON(health_response_t *health_response) {
    cJSON *item = cJSON_CreateObject();

    // health_response->ok
    if (!health_response->ok) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "ok", health_response->ok) == NULL) {
    goto fail; //Bool
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

health_response_t *health_response_parseFromJSON(cJSON *health_responseJSON){

    health_response_t *health_response_local_var = NULL;

    // health_response->ok
    cJSON *ok = cJSON_GetObjectItemCaseSensitive(health_responseJSON, "ok");
    if (cJSON_IsNull(ok)) {
        ok = NULL;
    }
    if (!ok) {
        goto end;
    }

    
    if(!cJSON_IsBool(ok))
    {
    goto end; //Bool
    }


    health_response_local_var = health_response_create_internal (
        ok->valueint
        );

    return health_response_local_var;
end:
    return NULL;

}
