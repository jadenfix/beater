/*
 * evaluator_kind_one_of_5.h
 *
 * 
 */

#ifndef _evaluator_kind_one_of_5_H_
#define _evaluator_kind_one_of_5_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_kind_one_of_5_t evaluator_kind_one_of_5_t;


// Enum TYPE for evaluator_kind_one_of_5

typedef enum  { beater_api_evaluator_kind_one_of_5_TYPE_NULL = 0, beater_api_evaluator_kind_one_of_5_TYPE_llm_judge } beater_api_evaluator_kind_one_of_5_TYPE_e;

char* evaluator_kind_one_of_5_type_ToString(beater_api_evaluator_kind_one_of_5_TYPE_e type);

beater_api_evaluator_kind_one_of_5_TYPE_e evaluator_kind_one_of_5_type_FromString(char* type);



typedef struct evaluator_kind_one_of_5_t {
    char *model; // string
    char *rubric; // string
    beater_api_evaluator_kind_one_of_5_TYPE_e type; //enum

    int _library_owned; // Is the library responsible for freeing this object?
} evaluator_kind_one_of_5_t;

__attribute__((deprecated)) evaluator_kind_one_of_5_t *evaluator_kind_one_of_5_create(
    char *model,
    char *rubric,
    beater_api_evaluator_kind_one_of_5_TYPE_e type
);

void evaluator_kind_one_of_5_free(evaluator_kind_one_of_5_t *evaluator_kind_one_of_5);

evaluator_kind_one_of_5_t *evaluator_kind_one_of_5_parseFromJSON(cJSON *evaluator_kind_one_of_5JSON);

cJSON *evaluator_kind_one_of_5_convertToJSON(evaluator_kind_one_of_5_t *evaluator_kind_one_of_5);

#endif /* _evaluator_kind_one_of_5_H_ */

