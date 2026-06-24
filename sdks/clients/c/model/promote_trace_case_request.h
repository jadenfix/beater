/*
 * promote_trace_case_request.h
 *
 * 
 */

#ifndef _promote_trace_case_request_H_
#define _promote_trace_case_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct promote_trace_case_request_t promote_trace_case_request_t;

#include "any_type.h"



typedef struct promote_trace_case_request_t {
    any_type_t *reference; // custom
    char *span_id; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} promote_trace_case_request_t;

__attribute__((deprecated)) promote_trace_case_request_t *promote_trace_case_request_create(
    any_type_t *reference,
    char *span_id,
    char *trace_id
);

void promote_trace_case_request_free(promote_trace_case_request_t *promote_trace_case_request);

promote_trace_case_request_t *promote_trace_case_request_parseFromJSON(cJSON *promote_trace_case_requestJSON);

cJSON *promote_trace_case_request_convertToJSON(promote_trace_case_request_t *promote_trace_case_request);

#endif /* _promote_trace_case_request_H_ */

