/*
 * evaluator_kind.h
 *
 * 
 */

#ifndef _evaluator_kind_H_
#define _evaluator_kind_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_kind_t evaluator_kind_t;

#include "evaluator_kind_one_of.h"
#include "evaluator_kind_one_of_1.h"
#include "evaluator_kind_one_of_2.h"
#include "evaluator_kind_one_of_3.h"
#include "evaluator_kind_one_of_4.h"
#include "evaluator_kind_one_of_5.h"

// Enum TYPE for evaluator_kind

typedef enum  { beater_api_evaluator_kind_TYPE_NULL = 0, beater_api_evaluator_kind_TYPE_exact_match, beater_api_evaluator_kind_TYPE_regex_match, beater_api_evaluator_kind_TYPE_json_object, beater_api_evaluator_kind_TYPE_cost_budget, beater_api_evaluator_kind_TYPE_latency_budget_ms, beater_api_evaluator_kind_TYPE_llm_judge } beater_api_evaluator_kind_TYPE_e;

char* evaluator_kind_type_ToString(beater_api_evaluator_kind_TYPE_e type);

beater_api_evaluator_kind_TYPE_e evaluator_kind_type_FromString(char* type);



typedef struct evaluator_kind_t {
    beater_api_evaluator_kind_TYPE_e type; //enum
    char *pattern; // string
    long max_micros; //numeric
    long max_ms; //numeric
    char *model; // string
    char *rubric; // string

    int _library_owned; // Is the library responsible for freeing this object?
} evaluator_kind_t;

__attribute__((deprecated)) evaluator_kind_t *evaluator_kind_create(
    beater_api_evaluator_kind_TYPE_e type,
    char *pattern,
    long max_micros,
    long max_ms,
    char *model,
    char *rubric
);

void evaluator_kind_free(evaluator_kind_t *evaluator_kind);

evaluator_kind_t *evaluator_kind_parseFromJSON(cJSON *evaluator_kindJSON);

cJSON *evaluator_kind_convertToJSON(evaluator_kind_t *evaluator_kind);

#endif /* _evaluator_kind_H_ */

