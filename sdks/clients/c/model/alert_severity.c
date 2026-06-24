#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alert_severity.h"


char* alert_severity_alert_severity_ToString(beater_api_alert_severity__e alert_severity) {
    char *alert_severityArray[] =  { "NULL", "info", "warning", "critical" };
    return alert_severityArray[alert_severity];
}

beater_api_alert_severity__e alert_severity_alert_severity_FromString(char* alert_severity) {
    int stringToReturn = 0;
    char *alert_severityArray[] =  { "NULL", "info", "warning", "critical" };
    size_t sizeofArray = sizeof(alert_severityArray) / sizeof(alert_severityArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(alert_severity, alert_severityArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *alert_severity_convertToJSON(beater_api_alert_severity__e alert_severity) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "alert_severity", alert_severity_alert_severity_ToString(alert_severity)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_alert_severity__e alert_severity_parseFromJSON(cJSON *alert_severityJSON) {
    if(!cJSON_IsString(alert_severityJSON) || (alert_severityJSON->valuestring == NULL)) {
        return 0;
    }
    return alert_severity_alert_severity_FromString(alert_severityJSON->valuestring);
}
