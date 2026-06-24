/*
 * evaluator_kind_one_of_1.h
 *
 * 
 */

#ifndef _evaluator_kind_one_of_1_H_
#define _evaluator_kind_one_of_1_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_kind_one_of_1_t evaluator_kind_one_of_1_t;


// Enum TYPE for evaluator_kind_one_of_1

typedef enum  { beater_api_evaluator_kind_one_of_1_TYPE_NULL = 0, beater_api_evaluator_kind_one_of_1_TYPE_regex_match } beater_api_evaluator_kind_one_of_1_TYPE_e;

char* evaluator_kind_one_of_1_type_ToString(beater_api_evaluator_kind_one_of_1_TYPE_e type);

beater_api_evaluator_kind_one_of_1_TYPE_e evaluator_kind_one_of_1_type_FromString(char* type);



typedef struct evaluator_kind_one_of_1_t {
    char *pattern; // string
    beater_api_evaluator_kind_one_of_1_TYPE_e type; //enum

    int _library_owned; // Is the library responsible for freeing this object?
} evaluator_kind_one_of_1_t;

__attribute__((deprecated)) evaluator_kind_one_of_1_t *evaluator_kind_one_of_1_create(
    char *pattern,
    beater_api_evaluator_kind_one_of_1_TYPE_e type
);

void evaluator_kind_one_of_1_free(evaluator_kind_one_of_1_t *evaluator_kind_one_of_1);

evaluator_kind_one_of_1_t *evaluator_kind_one_of_1_parseFromJSON(cJSON *evaluator_kind_one_of_1JSON);

cJSON *evaluator_kind_one_of_1_convertToJSON(evaluator_kind_one_of_1_t *evaluator_kind_one_of_1);

#endif /* _evaluator_kind_one_of_1_H_ */

