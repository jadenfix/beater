/*
 * sampling_decision.h
 *
 * 
 */

#ifndef _sampling_decision_H_
#define _sampling_decision_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct sampling_decision_t sampling_decision_t;

#include "sampling_reason.h"



typedef struct sampling_decision_t {
    beater_api_sampling_reason__e reason; //referenced enum
    int selected; //boolean
    int stable_score_per_mille; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} sampling_decision_t;

__attribute__((deprecated)) sampling_decision_t *sampling_decision_create(
    beater_api_sampling_reason__e reason,
    int selected,
    int stable_score_per_mille
);

void sampling_decision_free(sampling_decision_t *sampling_decision);

sampling_decision_t *sampling_decision_parseFromJSON(cJSON *sampling_decisionJSON);

cJSON *sampling_decision_convertToJSON(sampling_decision_t *sampling_decision);

#endif /* _sampling_decision_H_ */

