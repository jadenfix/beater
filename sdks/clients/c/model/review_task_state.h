/*
 * review_task_state.h
 *
 * 
 */

#ifndef _review_task_state_H_
#define _review_task_state_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct review_task_state_t review_task_state_t;


// Enum  for review_task_state

typedef enum { beater_api_review_task_state__NULL = 0, beater_api_review_task_state__open, beater_api_review_task_state__submitted, beater_api_review_task_state__cancelled } beater_api_review_task_state__e;

char* review_task_state_review_task_state_ToString(beater_api_review_task_state__e review_task_state);

beater_api_review_task_state__e review_task_state_review_task_state_FromString(char* review_task_state);

cJSON *review_task_state_convertToJSON(beater_api_review_task_state__e review_task_state);

beater_api_review_task_state__e review_task_state_parseFromJSON(cJSON *review_task_stateJSON);

#endif /* _review_task_state_H_ */

