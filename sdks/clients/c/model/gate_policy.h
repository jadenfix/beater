/*
 * gate_policy.h
 *
 * 
 */

#ifndef _gate_policy_H_
#define _gate_policy_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_policy_t gate_policy_t;




typedef struct gate_policy_t {
    double alpha; //numeric
    int comparison_count; //numeric
    double max_regression; //numeric
    int min_sample_size; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} gate_policy_t;

__attribute__((deprecated)) gate_policy_t *gate_policy_create(
    double alpha,
    int comparison_count,
    double max_regression,
    int min_sample_size
);

void gate_policy_free(gate_policy_t *gate_policy);

gate_policy_t *gate_policy_parseFromJSON(cJSON *gate_policyJSON);

cJSON *gate_policy_convertToJSON(gate_policy_t *gate_policy);

#endif /* _gate_policy_H_ */

