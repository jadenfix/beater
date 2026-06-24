/*
 * evaluator_spec.h
 *
 * 
 */

#ifndef _evaluator_spec_H_
#define _evaluator_spec_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_spec_t evaluator_spec_t;

#include "evaluator_kind.h"
#include "evaluator_lane.h"



typedef struct evaluator_spec_t {
    char *id; // string
    struct evaluator_kind_t *kind; //model
    beater_api_evaluator_lane__e lane; //referenced enum

    int _library_owned; // Is the library responsible for freeing this object?
} evaluator_spec_t;

__attribute__((deprecated)) evaluator_spec_t *evaluator_spec_create(
    char *id,
    evaluator_kind_t *kind,
    beater_api_evaluator_lane__e lane
);

void evaluator_spec_free(evaluator_spec_t *evaluator_spec);

evaluator_spec_t *evaluator_spec_parseFromJSON(cJSON *evaluator_specJSON);

cJSON *evaluator_spec_convertToJSON(evaluator_spec_t *evaluator_spec);

#endif /* _evaluator_spec_H_ */

