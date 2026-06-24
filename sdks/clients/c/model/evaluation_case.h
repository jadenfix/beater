/*
 * evaluation_case.h
 *
 * 
 */

#ifndef _evaluation_case_H_
#define _evaluation_case_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct evaluation_case_t evaluation_case_t;

#include "any_type.h"



typedef struct evaluation_case_t {
    any_type_t *input; // custom
    any_type_t *output; // custom
    any_type_t *reference; // custom
    any_type_t *trace; // custom

    int _library_owned; // Is the library responsible for freeing this object?
} evaluation_case_t;

__attribute__((deprecated)) evaluation_case_t *evaluation_case_create(
    any_type_t *input,
    any_type_t *output,
    any_type_t *reference,
    any_type_t *trace
);

void evaluation_case_free(evaluation_case_t *evaluation_case);

evaluation_case_t *evaluation_case_parseFromJSON(cJSON *evaluation_caseJSON);

cJSON *evaluation_case_convertToJSON(evaluation_case_t *evaluation_case);

#endif /* _evaluation_case_H_ */

