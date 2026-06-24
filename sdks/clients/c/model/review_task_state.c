#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "review_task_state.h"


char* review_task_state_review_task_state_ToString(beater_api_review_task_state__e review_task_state) {
    char *review_task_stateArray[] =  { "NULL", "open", "submitted", "cancelled" };
    return review_task_stateArray[review_task_state];
}

beater_api_review_task_state__e review_task_state_review_task_state_FromString(char* review_task_state) {
    int stringToReturn = 0;
    char *review_task_stateArray[] =  { "NULL", "open", "submitted", "cancelled" };
    size_t sizeofArray = sizeof(review_task_stateArray) / sizeof(review_task_stateArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(review_task_state, review_task_stateArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *review_task_state_convertToJSON(beater_api_review_task_state__e review_task_state) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "review_task_state", review_task_state_review_task_state_ToString(review_task_state)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_review_task_state__e review_task_state_parseFromJSON(cJSON *review_task_stateJSON) {
    if(!cJSON_IsString(review_task_stateJSON) || (review_task_stateJSON->valuestring == NULL)) {
        return 0;
    }
    return review_task_state_review_task_state_FromString(review_task_stateJSON->valuestring);
}
