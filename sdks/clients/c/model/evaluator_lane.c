#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluator_lane.h"


char* evaluator_lane_evaluator_lane_ToString(beater_api_evaluator_lane__e evaluator_lane) {
    char *evaluator_laneArray[] =  { "NULL", "deterministic_wasi", "judge_broker", "human", "hybrid" };
    return evaluator_laneArray[evaluator_lane];
}

beater_api_evaluator_lane__e evaluator_lane_evaluator_lane_FromString(char* evaluator_lane) {
    int stringToReturn = 0;
    char *evaluator_laneArray[] =  { "NULL", "deterministic_wasi", "judge_broker", "human", "hybrid" };
    size_t sizeofArray = sizeof(evaluator_laneArray) / sizeof(evaluator_laneArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(evaluator_lane, evaluator_laneArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

cJSON *evaluator_lane_convertToJSON(beater_api_evaluator_lane__e evaluator_lane) {
    cJSON *item = cJSON_CreateObject();
    if(cJSON_AddStringToObject(item, "evaluator_lane", evaluator_lane_evaluator_lane_ToString(evaluator_lane)) == NULL) {
        goto fail;
    }
    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

beater_api_evaluator_lane__e evaluator_lane_parseFromJSON(cJSON *evaluator_laneJSON) {
    if(!cJSON_IsString(evaluator_laneJSON) || (evaluator_laneJSON->valuestring == NULL)) {
        return 0;
    }
    return evaluator_lane_evaluator_lane_FromString(evaluator_laneJSON->valuestring);
}
