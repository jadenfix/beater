#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "currency.h"


char* currency_currency_ToString(beater_api_currency__e currency) {
    char *currencyArray[] =  { "NULL", "USD" };
    return currencyArray[currency];
}

beater_api_currency__e currency_currency_FromString(char* currency) {
    int stringToReturn = 0;
    char *currencyArray[] =  { "NULL", "USD" };
    size_t sizeofArray = sizeof(currencyArray) / sizeof(currencyArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(currency, currencyArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *currency_convertToJSON(beater_api_currency__e currency) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "currency", currency_currency_ToString(currency)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_currency__e currency_parseFromJSON(cJSON *currencyJSON) {
    if(!cJSON_IsString(currencyJSON) || (currencyJSON->valuestring == NULL)) {
        return 0;
    }
    return currency_currency_FromString(currencyJSON->valuestring);
}
