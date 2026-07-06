#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "optimizer_strategy.h"


char* optimizer_strategy_optimizer_strategy_ToString(beater_api_optimizer_strategy__e optimizer_strategy) {
    char *optimizer_strategyArray[] =  { "NULL", "llm_rewrite", "few_shot_bayesian", "mipro", "evolutionary", "gepa", "param_search" };
    return optimizer_strategyArray[optimizer_strategy];
}

beater_api_optimizer_strategy__e optimizer_strategy_optimizer_strategy_FromString(char* optimizer_strategy) {
    int stringToReturn = 0;
    char *optimizer_strategyArray[] =  { "NULL", "llm_rewrite", "few_shot_bayesian", "mipro", "evolutionary", "gepa", "param_search" };
    size_t sizeofArray = sizeof(optimizer_strategyArray) / sizeof(optimizer_strategyArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(optimizer_strategy, optimizer_strategyArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *optimizer_strategy_convertToJSON(beater_api_optimizer_strategy__e optimizer_strategy) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "optimizer_strategy", optimizer_strategy_optimizer_strategy_ToString(optimizer_strategy)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_optimizer_strategy__e optimizer_strategy_parseFromJSON(cJSON *optimizer_strategyJSON) {
    if(!cJSON_IsString(optimizer_strategyJSON) || (optimizer_strategyJSON->valuestring == NULL)) {
        return 0;
    }
    return optimizer_strategy_optimizer_strategy_FromString(optimizer_strategyJSON->valuestring);
}
