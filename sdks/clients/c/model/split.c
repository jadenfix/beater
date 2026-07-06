#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "split.h"


char* split_split_ToString(beater_api_split__e split) {
    char *splitArray[] =  { "NULL", "train", "val", "test" };
    return splitArray[split];
}

beater_api_split__e split_split_FromString(char* split) {
    int stringToReturn = 0;
    char *splitArray[] =  { "NULL", "train", "val", "test" };
    size_t sizeofArray = sizeof(splitArray) / sizeof(splitArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(split, splitArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *split_convertToJSON(beater_api_split__e split) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "split", split_split_ToString(split)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_split__e split_parseFromJSON(cJSON *splitJSON) {
    if(!cJSON_IsString(splitJSON) || (splitJSON->valuestring == NULL)) {
        return 0;
    }
    return split_split_FromString(splitJSON->valuestring);
}
