/*
 * evaluator_kind_one_of_4.h
 *
 * 
 */

#ifndef _evaluator_kind_one_of_4_H_
#define _evaluator_kind_one_of_4_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_kind_one_of_4_t evaluator_kind_one_of_4_t;


// Enum TYPE for evaluator_kind_one_of_4

typedef enum  { beater_api_evaluator_kind_one_of_4_TYPE_NULL = 0, beater_api_evaluator_kind_one_of_4_TYPE_latency_budget_ms } beater_api_evaluator_kind_one_of_4_TYPE_e;

char* evaluator_kind_one_of_4_type_ToString(beater_api_evaluator_kind_one_of_4_TYPE_e type);

beater_api_evaluator_kind_one_of_4_TYPE_e evaluator_kind_one_of_4_type_FromString(char* type);



typedef struct evaluator_kind_one_of_4_t {
    long max_ms; //numeric
    beater_api_evaluator_kind_one_of_4_TYPE_e type; //enum

    int _library_owned; // Is the library responsible for freeing this object?
} evaluator_kind_one_of_4_t;

__attribute__((deprecated)) evaluator_kind_one_of_4_t *evaluator_kind_one_of_4_create(
    long max_ms,
    beater_api_evaluator_kind_one_of_4_TYPE_e type
);

void evaluator_kind_one_of_4_free(evaluator_kind_one_of_4_t *evaluator_kind_one_of_4);

evaluator_kind_one_of_4_t *evaluator_kind_one_of_4_parseFromJSON(cJSON *evaluator_kind_one_of_4JSON);

cJSON *evaluator_kind_one_of_4_convertToJSON(evaluator_kind_one_of_4_t *evaluator_kind_one_of_4);

#endif /* _evaluator_kind_one_of_4_H_ */

