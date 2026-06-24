/*
 * evaluator_kind_one_of.h
 *
 * 
 */

#ifndef _evaluator_kind_one_of_H_
#define _evaluator_kind_one_of_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_kind_one_of_t evaluator_kind_one_of_t;


// Enum TYPE for evaluator_kind_one_of

typedef enum  { beater_api_evaluator_kind_one_of_TYPE_NULL = 0, beater_api_evaluator_kind_one_of_TYPE_exact_match } beater_api_evaluator_kind_one_of_TYPE_e;

char* evaluator_kind_one_of_type_ToString(beater_api_evaluator_kind_one_of_TYPE_e type);

beater_api_evaluator_kind_one_of_TYPE_e evaluator_kind_one_of_type_FromString(char* type);



typedef struct evaluator_kind_one_of_t {
    beater_api_evaluator_kind_one_of_TYPE_e type; //enum

    int _library_owned; // Is the library responsible for freeing this object?
} evaluator_kind_one_of_t;

__attribute__((deprecated)) evaluator_kind_one_of_t *evaluator_kind_one_of_create(
    beater_api_evaluator_kind_one_of_TYPE_e type
);

void evaluator_kind_one_of_free(evaluator_kind_one_of_t *evaluator_kind_one_of);

evaluator_kind_one_of_t *evaluator_kind_one_of_parseFromJSON(cJSON *evaluator_kind_one_ofJSON);

cJSON *evaluator_kind_one_of_convertToJSON(evaluator_kind_one_of_t *evaluator_kind_one_of);

#endif /* _evaluator_kind_one_of_H_ */

