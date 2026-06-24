#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "audit_outcome.h"


char* audit_outcome_audit_outcome_ToString(beater_api_audit_outcome__e audit_outcome) {
    char *audit_outcomeArray[] =  { "NULL", "allowed", "denied" };
    return audit_outcomeArray[audit_outcome];
}

beater_api_audit_outcome__e audit_outcome_audit_outcome_FromString(char* audit_outcome) {
    int stringToReturn = 0;
    char *audit_outcomeArray[] =  { "NULL", "allowed", "denied" };
    size_t sizeofArray = sizeof(audit_outcomeArray) / sizeof(audit_outcomeArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(audit_outcome, audit_outcomeArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *audit_outcome_convertToJSON(beater_api_audit_outcome__e audit_outcome) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "audit_outcome", audit_outcome_audit_outcome_ToString(audit_outcome)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_audit_outcome__e audit_outcome_parseFromJSON(cJSON *audit_outcomeJSON) {
    if(!cJSON_IsString(audit_outcomeJSON) || (audit_outcomeJSON->valuestring == NULL)) {
        return 0;
    }
    return audit_outcome_audit_outcome_FromString(audit_outcomeJSON->valuestring);
}
