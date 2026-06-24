/*
 * case_output_override_request.h
 *
 * 
 */

#ifndef _case_output_override_request_H_
#define _case_output_override_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct case_output_override_request_t case_output_override_request_t;

#include "any_type.h"



typedef struct case_output_override_request_t {
    char *case_id; // string
    any_type_t *output; // custom
    any_type_t *trace; // custom

    int _library_owned; // Is the library responsible for freeing this object?
} case_output_override_request_t;

__attribute__((deprecated)) case_output_override_request_t *case_output_override_request_create(
    char *case_id,
    any_type_t *output,
    any_type_t *trace
);

void case_output_override_request_free(case_output_override_request_t *case_output_override_request);

case_output_override_request_t *case_output_override_request_parseFromJSON(cJSON *case_output_override_requestJSON);

cJSON *case_output_override_request_convertToJSON(case_output_override_request_t *case_output_override_request);

#endif /* _case_output_override_request_H_ */

