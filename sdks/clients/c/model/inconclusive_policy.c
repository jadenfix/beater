#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inconclusive_policy.h"


char* inconclusive_policy_inconclusive_policy_ToString(beater_api_inconclusive_policy__e inconclusive_policy) {
    char *inconclusive_policyArray[] =  { "NULL", "pass", "fail" };
    return inconclusive_policyArray[inconclusive_policy];
}

beater_api_inconclusive_policy__e inconclusive_policy_inconclusive_policy_FromString(char* inconclusive_policy) {
    int stringToReturn = 0;
    char *inconclusive_policyArray[] =  { "NULL", "pass", "fail" };
    size_t sizeofArray = sizeof(inconclusive_policyArray) / sizeof(inconclusive_policyArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(inconclusive_policy, inconclusive_policyArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *inconclusive_policy_convertToJSON(beater_api_inconclusive_policy__e inconclusive_policy) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "inconclusive_policy", inconclusive_policy_inconclusive_policy_ToString(inconclusive_policy)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_inconclusive_policy__e inconclusive_policy_parseFromJSON(cJSON *inconclusive_policyJSON) {
    if(!cJSON_IsString(inconclusive_policyJSON) || (inconclusive_policyJSON->valuestring == NULL)) {
        return 0;
    }
    return inconclusive_policy_inconclusive_policy_FromString(inconclusive_policyJSON->valuestring);
}
