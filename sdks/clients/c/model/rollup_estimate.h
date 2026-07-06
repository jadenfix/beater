/*
 * rollup_estimate.h
 *
 * A population-mean roll-up paired with the honesty label saying whether it is inverse-probability weighted or a biased unweighted average (§1 #9). The label travels with the value so a caller can never silently render a tail-sampled average as if it were unbiased.
 */

#ifndef _rollup_estimate_H_
#define _rollup_estimate_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct rollup_estimate_t rollup_estimate_t;

#include "rollup_weighting.h"



typedef struct rollup_estimate_t {
    double value; //numeric
    beater_api_rollup_weighting__e weighting; //referenced enum

    int _library_owned; // Is the library responsible for freeing this object?
} rollup_estimate_t;

__attribute__((deprecated)) rollup_estimate_t *rollup_estimate_create(
    double value,
    beater_api_rollup_weighting__e weighting
);

void rollup_estimate_free(rollup_estimate_t *rollup_estimate);

rollup_estimate_t *rollup_estimate_parseFromJSON(cJSON *rollup_estimateJSON);

cJSON *rollup_estimate_convertToJSON(rollup_estimate_t *rollup_estimate);

#endif /* _rollup_estimate_H_ */

