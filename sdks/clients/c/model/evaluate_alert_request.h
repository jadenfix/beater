/*
 * evaluate_alert_request.h
 *
 * 
 */

#ifndef _evaluate_alert_request_H_
#define _evaluate_alert_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluate_alert_request_t evaluate_alert_request_t;

#include "alert_input.h"
#include "alert_policy.h"



typedef struct evaluate_alert_request_t {
    struct alert_input_t *input; //model
    struct alert_policy_t *policy; //model

    int _library_owned; // Is the library responsible for freeing this object?
} evaluate_alert_request_t;

__attribute__((deprecated)) evaluate_alert_request_t *evaluate_alert_request_create(
    alert_input_t *input,
    alert_policy_t *policy
);

void evaluate_alert_request_free(evaluate_alert_request_t *evaluate_alert_request);

evaluate_alert_request_t *evaluate_alert_request_parseFromJSON(cJSON *evaluate_alert_requestJSON);

cJSON *evaluate_alert_request_convertToJSON(evaluate_alert_request_t *evaluate_alert_request);

#endif /* _evaluate_alert_request_H_ */

