#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_decision.h"


char* gate_decision_gate_decision_ToString(beater_api_gate_decision__e gate_decision) {
    char *gate_decisionArray[] =  { "NULL", "pass", "fail_regression", "inconclusive" };
    return gate_decisionArray[gate_decision];
}

beater_api_gate_decision__e gate_decision_gate_decision_FromString(char* gate_decision) {
    int stringToReturn = 0;
    char *gate_decisionArray[] =  { "NULL", "pass", "fail_regression", "inconclusive" };
    size_t sizeofArray = sizeof(gate_decisionArray) / sizeof(gate_decisionArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(gate_decision, gate_decisionArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *gate_decision_convertToJSON(beater_api_gate_decision__e gate_decision) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "gate_decision", gate_decision_gate_decision_ToString(gate_decision)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_gate_decision__e gate_decision_parseFromJSON(cJSON *gate_decisionJSON) {
    if(!cJSON_IsString(gate_decisionJSON) || (gate_decisionJSON->valuestring == NULL)) {
        return 0;
    }
    return gate_decision_gate_decision_FromString(gate_decisionJSON->valuestring);
}
