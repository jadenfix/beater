/*
 * rollup_weighting.h
 *
 * Whether a roll-up estimate honestly accounts for tail-sampling bias (§1 #9, #146). A tail-sampled population is deliberately non-representative, so an unweighted mean is a biased estimator of the population it was drawn from.
 */

#ifndef _rollup_weighting_H_
#define _rollup_weighting_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct rollup_weighting_t rollup_weighting_t;


// Enum  for rollup_weighting

typedef enum { beater_api_rollup_weighting__NULL = 0, beater_api_rollup_weighting__horvitz_thompson, beater_api_rollup_weighting__biased_unweighted } beater_api_rollup_weighting__e;

char* rollup_weighting_rollup_weighting_ToString(beater_api_rollup_weighting__e rollup_weighting);

beater_api_rollup_weighting__e rollup_weighting_rollup_weighting_FromString(char* rollup_weighting);

cJSON *rollup_weighting_convertToJSON(beater_api_rollup_weighting__e rollup_weighting);

beater_api_rollup_weighting__e rollup_weighting_parseFromJSON(cJSON *rollup_weightingJSON);

#endif /* _rollup_weighting_H_ */

