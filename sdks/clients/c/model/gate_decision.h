/*
 * gate_decision.h
 *
 * 
 */

#ifndef _gate_decision_H_
#define _gate_decision_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_decision_t gate_decision_t;


// Enum  for gate_decision

typedef enum { beater_api_gate_decision__NULL = 0, beater_api_gate_decision__pass, beater_api_gate_decision__fail_regression, beater_api_gate_decision__inconclusive } beater_api_gate_decision__e;

char* gate_decision_gate_decision_ToString(beater_api_gate_decision__e gate_decision);

beater_api_gate_decision__e gate_decision_gate_decision_FromString(char* gate_decision);

cJSON *gate_decision_convertToJSON(beater_api_gate_decision__e gate_decision);

beater_api_gate_decision__e gate_decision_parseFromJSON(cJSON *gate_decisionJSON);

#endif /* _gate_decision_H_ */

