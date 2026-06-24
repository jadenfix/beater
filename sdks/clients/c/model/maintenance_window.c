#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "maintenance_window.h"



static maintenance_window_t *maintenance_window_create_internal(
    char *ends_at,
    char *starts_at
    ) {
    maintenance_window_t *maintenance_window_local_var = malloc(sizeof(maintenance_window_t));
    if (!maintenance_window_local_var) {
        return NULL;
    }
    maintenance_window_local_var->ends_at = ends_at;
    maintenance_window_local_var->starts_at = starts_at;

    maintenance_window_local_var->_library_owned = 1;
    return maintenance_window_local_var;
}

__attribute__((deprecated)) maintenance_window_t *maintenance_window_create(
    char *ends_at,
    char *starts_at
    ) {
    return maintenance_window_create_internal (
        ends_at,
        starts_at
        );
}

void maintenance_window_free(maintenance_window_t *maintenance_window) {
    if(NULL == maintenance_window){
        return ;
    }
    if(maintenance_window->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "maintenance_window_free");
        return ;
    }
    listEntry_t *listEntry;
    if (maintenance_window->ends_at) {
        free(maintenance_window->ends_at);
        maintenance_window->ends_at = NULL;
    }
    if (maintenance_window->starts_at) {
        free(maintenance_window->starts_at);
        maintenance_window->starts_at = NULL;
    }
    free(maintenance_window);
}

cJSON *maintenance_window_convertToJSON(maintenance_window_t *maintenance_window) {
    cJSON *item = cJSON_CreateObject();

    // maintenance_window->ends_at
    if (!maintenance_window->ends_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "ends_at", maintenance_window->ends_at) == NULL) {
    goto fail; //Date-Time
    }


    // maintenance_window->starts_at
    if (!maintenance_window->starts_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "starts_at", maintenance_window->starts_at) == NULL) {
    goto fail; //Date-Time
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

maintenance_window_t *maintenance_window_parseFromJSON(cJSON *maintenance_windowJSON){

    maintenance_window_t *maintenance_window_local_var = NULL;

    // maintenance_window->ends_at
    cJSON *ends_at = cJSON_GetObjectItemCaseSensitive(maintenance_windowJSON, "ends_at");
    if (cJSON_IsNull(ends_at)) {
        ends_at = NULL;
    }
    if (!ends_at) {
        goto end;
    }

    
    if(!cJSON_IsString(ends_at) && !cJSON_IsNull(ends_at))
    {
    goto end; //DateTime
    }

    // maintenance_window->starts_at
    cJSON *starts_at = cJSON_GetObjectItemCaseSensitive(maintenance_windowJSON, "starts_at");
    if (cJSON_IsNull(starts_at)) {
        starts_at = NULL;
    }
    if (!starts_at) {
        goto end;
    }

    
    if(!cJSON_IsString(starts_at) && !cJSON_IsNull(starts_at))
    {
    goto end; //DateTime
    }


    maintenance_window_local_var = maintenance_window_create_internal (
        strdup(ends_at->valuestring),
        strdup(starts_at->valuestring)
        );

    return maintenance_window_local_var;
end:
    return NULL;

}
