/*
 * alert_decision.h
 *
 * 
 */

#ifndef _alert_decision_H_
#define _alert_decision_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct alert_decision_t alert_decision_t;

#include "webhook_delivery.h"



typedef struct alert_decision_t {
    struct webhook_delivery_t *delivery; //model
    int emitted; //boolean
    char *suppressed_reason; // string

    int _library_owned; // Is the library responsible for freeing this object?
} alert_decision_t;

__attribute__((deprecated)) alert_decision_t *alert_decision_create(
    webhook_delivery_t *delivery,
    int emitted,
    char *suppressed_reason
);

void alert_decision_free(alert_decision_t *alert_decision);

alert_decision_t *alert_decision_parseFromJSON(cJSON *alert_decisionJSON);

cJSON *alert_decision_convertToJSON(alert_decision_t *alert_decision);

#endif /* _alert_decision_H_ */

