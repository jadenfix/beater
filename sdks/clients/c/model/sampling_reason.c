#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sampling_reason.h"


char* sampling_reason_sampling_reason_ToString(beater_api_sampling_reason__e sampling_reason) {
    char *sampling_reasonArray[] =  { "NULL", "error_trace", "slow_trace", "high_cost_trace", "routine_sampled", "routine_dropped" };
    return sampling_reasonArray[sampling_reason];
}

beater_api_sampling_reason__e sampling_reason_sampling_reason_FromString(char* sampling_reason) {
    int stringToReturn = 0;
    char *sampling_reasonArray[] =  { "NULL", "error_trace", "slow_trace", "high_cost_trace", "routine_sampled", "routine_dropped" };
    size_t sizeofArray = sizeof(sampling_reasonArray) / sizeof(sampling_reasonArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(sampling_reason, sampling_reasonArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *sampling_reason_convertToJSON(beater_api_sampling_reason__e sampling_reason) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "sampling_reason", sampling_reason_sampling_reason_ToString(sampling_reason)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_sampling_reason__e sampling_reason_parseFromJSON(cJSON *sampling_reasonJSON) {
    if(!cJSON_IsString(sampling_reasonJSON) || (sampling_reasonJSON->valuestring == NULL)) {
        return 0;
    }
    return sampling_reason_sampling_reason_FromString(sampling_reasonJSON->valuestring);
}
