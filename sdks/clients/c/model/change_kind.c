#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "change_kind.h"


char* change_kind_change_kind_ToString(beater_api_change_kind__e change_kind) {
    char *change_kindArray[] =  { "NULL", "system_prompt", "customer_prompt", "code", "tool_add", "tool_remove", "memory_config", "model_params", "data_label" };
    return change_kindArray[change_kind];
}

beater_api_change_kind__e change_kind_change_kind_FromString(char* change_kind) {
    int stringToReturn = 0;
    char *change_kindArray[] =  { "NULL", "system_prompt", "customer_prompt", "code", "tool_add", "tool_remove", "memory_config", "model_params", "data_label" };
    size_t sizeofArray = sizeof(change_kindArray) / sizeof(change_kindArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(change_kind, change_kindArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *change_kind_convertToJSON(beater_api_change_kind__e change_kind) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "change_kind", change_kind_change_kind_ToString(change_kind)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_change_kind__e change_kind_parseFromJSON(cJSON *change_kindJSON) {
    if(!cJSON_IsString(change_kindJSON) || (change_kindJSON->valuestring == NULL)) {
        return 0;
    }
    return change_kind_change_kind_FromString(change_kindJSON->valuestring);
}
