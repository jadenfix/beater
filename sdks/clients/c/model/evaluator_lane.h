/*
 * evaluator_lane.h
 *
 * 
 */

#ifndef _evaluator_lane_H_
#define _evaluator_lane_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_lane_t evaluator_lane_t;


// Enum  for evaluator_lane

typedef enum { beater_api_evaluator_lane__NULL = 0, beater_api_evaluator_lane__deterministic_wasi, beater_api_evaluator_lane__judge_broker, beater_api_evaluator_lane__human, beater_api_evaluator_lane__hybrid } beater_api_evaluator_lane__e;

char* evaluator_lane_evaluator_lane_ToString(beater_api_evaluator_lane__e evaluator_lane);

beater_api_evaluator_lane__e evaluator_lane_evaluator_lane_FromString(char* evaluator_lane);

cJSON *evaluator_lane_convertToJSON(beater_api_evaluator_lane__e evaluator_lane);

beater_api_evaluator_lane__e evaluator_lane_parseFromJSON(cJSON *evaluator_laneJSON);

#endif /* _evaluator_lane_H_ */

