/*
 * evaluator_kind_one_of_6.h
 *
 * Browser world-state success: asserts the final step&#39;s observed page (url and/or DOM) matches the configured target — NOT the agent&#39;s self-reported \&quot;done\&quot;. Reads &#x60;trace.browser_steps&#x60;.
 */

#ifndef _evaluator_kind_one_of_6_H_
#define _evaluator_kind_one_of_6_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluator_kind_one_of_6_t evaluator_kind_one_of_6_t;


// Enum TYPE for evaluator_kind_one_of_6

typedef enum  { beater_api_evaluator_kind_one_of_6_TYPE_NULL = 0, beater_api_evaluator_kind_one_of_6_TYPE_browser_task_success } beater_api_evaluator_kind_one_of_6_TYPE_e;

char* evaluator_kind_one_of_6_type_ToString(beater_api_evaluator_kind_one_of_6_TYPE_e type);

beater_api_evaluator_kind_one_of_6_TYPE_e evaluator_kind_one_of_6_type_FromString(char* type);



typedef struct evaluator_kind_one_of_6_t {
    char *dom_contains; // string
    beater_api_evaluator_kind_one_of_6_TYPE_e type; //enum
    char *url_contains; // string

    int _library_owned; // Is the library responsible for freeing this object?
} evaluator_kind_one_of_6_t;

__attribute__((deprecated)) evaluator_kind_one_of_6_t *evaluator_kind_one_of_6_create(
    char *dom_contains,
    beater_api_evaluator_kind_one_of_6_TYPE_e type,
    char *url_contains
);

void evaluator_kind_one_of_6_free(evaluator_kind_one_of_6_t *evaluator_kind_one_of_6);

evaluator_kind_one_of_6_t *evaluator_kind_one_of_6_parseFromJSON(cJSON *evaluator_kind_one_of_6JSON);

cJSON *evaluator_kind_one_of_6_convertToJSON(evaluator_kind_one_of_6_t *evaluator_kind_one_of_6);

#endif /* _evaluator_kind_one_of_6_H_ */

