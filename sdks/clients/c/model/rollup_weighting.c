#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rollup_weighting.h"


char* rollup_weighting_rollup_weighting_ToString(beater_api_rollup_weighting__e rollup_weighting) {
    char *rollup_weightingArray[] =  { "NULL", "horvitz_thompson", "biased_unweighted" };
    return rollup_weightingArray[rollup_weighting];
}

beater_api_rollup_weighting__e rollup_weighting_rollup_weighting_FromString(char* rollup_weighting) {
    int stringToReturn = 0;
    char *rollup_weightingArray[] =  { "NULL", "horvitz_thompson", "biased_unweighted" };
    size_t sizeofArray = sizeof(rollup_weightingArray) / sizeof(rollup_weightingArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(rollup_weighting, rollup_weightingArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *rollup_weighting_convertToJSON(beater_api_rollup_weighting__e rollup_weighting) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "rollup_weighting", rollup_weighting_rollup_weighting_ToString(rollup_weighting)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_rollup_weighting__e rollup_weighting_parseFromJSON(cJSON *rollup_weightingJSON) {
    if(!cJSON_IsString(rollup_weightingJSON) || (rollup_weightingJSON->valuestring == NULL)) {
        return 0;
    }
    return rollup_weighting_rollup_weighting_FromString(rollup_weightingJSON->valuestring);
}
