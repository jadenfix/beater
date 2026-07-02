/*
 * overfit_response.h
 *
 * The anti-overfitting (generalization-gap) assessment.
 */

#ifndef _overfit_response_H_
#define _overfit_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct overfit_response_t overfit_response_t;




typedef struct overfit_response_t {
    double gap; //numeric
    double gap_ci_high; //numeric
    double gap_ci_low; //numeric
    double holdout_lift; //numeric
    double optimize_lift; //numeric
    int overfit; //boolean

    int _library_owned; // Is the library responsible for freeing this object?
} overfit_response_t;

__attribute__((deprecated)) overfit_response_t *overfit_response_create(
    double gap,
    double gap_ci_high,
    double gap_ci_low,
    double holdout_lift,
    double optimize_lift,
    int overfit
);

void overfit_response_free(overfit_response_t *overfit_response);

overfit_response_t *overfit_response_parseFromJSON(cJSON *overfit_responseJSON);

cJSON *overfit_response_convertToJSON(overfit_response_t *overfit_response);

#endif /* _overfit_response_H_ */

