#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "redaction_class.h"


char* redaction_class_redaction_class_ToString(beater_api_redaction_class__e redaction_class) {
    char *redaction_classArray[] =  { "NULL", "public", "internal", "sensitive", "secret" };
    return redaction_classArray[redaction_class];
}

beater_api_redaction_class__e redaction_class_redaction_class_FromString(char* redaction_class) {
    int stringToReturn = 0;
    char *redaction_classArray[] =  { "NULL", "public", "internal", "sensitive", "secret" };
    size_t sizeofArray = sizeof(redaction_classArray) / sizeof(redaction_classArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(redaction_class, redaction_classArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *redaction_class_convertToJSON(beater_api_redaction_class__e redaction_class) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "redaction_class", redaction_class_redaction_class_ToString(redaction_class)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_redaction_class__e redaction_class_parseFromJSON(cJSON *redaction_classJSON) {
    if(!cJSON_IsString(redaction_classJSON) || (redaction_classJSON->valuestring == NULL)) {
        return 0;
    }
    return redaction_class_redaction_class_FromString(redaction_classJSON->valuestring);
}
