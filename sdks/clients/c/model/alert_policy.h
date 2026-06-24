/*
 * alert_policy.h
 *
 * 
 */

#ifndef _alert_policy_H_
#define _alert_policy_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct alert_policy_t alert_policy_t;

#include "alert_severity.h"
#include "maintenance_window.h"



typedef struct alert_policy_t {
    long dedupe_window_seconds; //numeric
    char *endpoint_url; // string
    double fire_when_score_at_or_below; //numeric
    list_t *maintenance_windows; //nonprimitive container
    char *policy_id; // string
    beater_api_alert_severity__e severity; //referenced enum
    char *signing_secret; // string

    int _library_owned; // Is the library responsible for freeing this object?
} alert_policy_t;

__attribute__((deprecated)) alert_policy_t *alert_policy_create(
    long dedupe_window_seconds,
    char *endpoint_url,
    double fire_when_score_at_or_below,
    list_t *maintenance_windows,
    char *policy_id,
    beater_api_alert_severity__e severity,
    char *signing_secret
);

void alert_policy_free(alert_policy_t *alert_policy);

alert_policy_t *alert_policy_parseFromJSON(cJSON *alert_policyJSON);

cJSON *alert_policy_convertToJSON(alert_policy_t *alert_policy);

#endif /* _alert_policy_H_ */

