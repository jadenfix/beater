#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "review_verdict.h"


char* review_verdict_review_verdict_ToString(beater_api_review_verdict__e review_verdict) {
    char *review_verdictArray[] =  { "NULL", "pass", "fail", "needs_fix", "unsure" };
    return review_verdictArray[review_verdict];
}

beater_api_review_verdict__e review_verdict_review_verdict_FromString(char* review_verdict) {
    int stringToReturn = 0;
    char *review_verdictArray[] =  { "NULL", "pass", "fail", "needs_fix", "unsure" };
    size_t sizeofArray = sizeof(review_verdictArray) / sizeof(review_verdictArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(review_verdict, review_verdictArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *review_verdict_convertToJSON(beater_api_review_verdict__e review_verdict) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "review_verdict", review_verdict_review_verdict_ToString(review_verdict)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_review_verdict__e review_verdict_parseFromJSON(cJSON *review_verdictJSON) {
    if(!cJSON_IsString(review_verdictJSON) || (review_verdictJSON->valuestring == NULL)) {
        return 0;
    }
    return review_verdict_review_verdict_FromString(review_verdictJSON->valuestring);
}
