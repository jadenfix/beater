/*
 * span_io_response.h
 *
 * 
 */

#ifndef _span_io_response_H_
#define _span_io_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct span_io_response_t span_io_response_t;

#include "span_io_value.h"



typedef struct span_io_response_t {
    struct span_io_value_t *input; //model
    struct span_io_value_t *output; //model
    char *span_id; // string
    char *tenant_id; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} span_io_response_t;

__attribute__((deprecated)) span_io_response_t *span_io_response_create(
    span_io_value_t *input,
    span_io_value_t *output,
    char *span_id,
    char *tenant_id,
    char *trace_id
);

void span_io_response_free(span_io_response_t *span_io_response);

span_io_response_t *span_io_response_parseFromJSON(cJSON *span_io_responseJSON);

cJSON *span_io_response_convertToJSON(span_io_response_t *span_io_response);

#endif /* _span_io_response_H_ */

