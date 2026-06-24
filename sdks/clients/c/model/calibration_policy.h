/*
 * calibration_policy.h
 *
 * 
 */

#ifndef _calibration_policy_H_
#define _calibration_policy_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct calibration_policy_t calibration_policy_t;




typedef struct calibration_policy_t {
    double pass_threshold; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} calibration_policy_t;

__attribute__((deprecated)) calibration_policy_t *calibration_policy_create(
    double pass_threshold
);

void calibration_policy_free(calibration_policy_t *calibration_policy);

calibration_policy_t *calibration_policy_parseFromJSON(cJSON *calibration_policyJSON);

cJSON *calibration_policy_convertToJSON(calibration_policy_t *calibration_policy);

#endif /* _calibration_policy_H_ */

