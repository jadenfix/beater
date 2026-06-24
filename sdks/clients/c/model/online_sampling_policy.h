/*
 * online_sampling_policy.h
 *
 * 
 */

#ifndef _online_sampling_policy_H_
#define _online_sampling_policy_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct online_sampling_policy_t online_sampling_policy_t;




typedef struct online_sampling_policy_t {
    long high_cost_micros_threshold; //numeric
    int keep_errors; //boolean
    int sample_rate_per_mille; //numeric
    long slow_ms_threshold; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} online_sampling_policy_t;

__attribute__((deprecated)) online_sampling_policy_t *online_sampling_policy_create(
    long high_cost_micros_threshold,
    int keep_errors,
    int sample_rate_per_mille,
    long slow_ms_threshold
);

void online_sampling_policy_free(online_sampling_policy_t *online_sampling_policy);

online_sampling_policy_t *online_sampling_policy_parseFromJSON(cJSON *online_sampling_policyJSON);

cJSON *online_sampling_policy_convertToJSON(online_sampling_policy_t *online_sampling_policy);

#endif /* _online_sampling_policy_H_ */

