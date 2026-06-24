#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "span_status.h"


char* span_status_span_status_ToString(beater_api_span_status__e span_status) {
    char *span_statusArray[] =  { "NULL", "ok", "error", "unset" };
    return span_statusArray[span_status];
}

beater_api_span_status__e span_status_span_status_FromString(char* span_status) {
    int stringToReturn = 0;
    char *span_statusArray[] =  { "NULL", "ok", "error", "unset" };
    size_t sizeofArray = sizeof(span_statusArray) / sizeof(span_statusArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(span_status, span_statusArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *span_status_convertToJSON(beater_api_span_status__e span_status) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "span_status", span_status_span_status_ToString(span_status)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_span_status__e span_status_parseFromJSON(cJSON *span_statusJSON) {
    if(!cJSON_IsString(span_statusJSON) || (span_statusJSON->valuestring == NULL)) {
        return 0;
    }
    return span_status_span_status_FromString(span_statusJSON->valuestring);
}
