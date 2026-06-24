/*
 * trace_view.h
 *
 * 
 */

#ifndef _trace_view_H_
#define _trace_view_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct trace_view_t trace_view_t;

#include "canonical_span.h"



typedef struct trace_view_t {
    list_t *spans; //nonprimitive container
    char *tenant_id; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} trace_view_t;

__attribute__((deprecated)) trace_view_t *trace_view_create(
    list_t *spans,
    char *tenant_id,
    char *trace_id
);

void trace_view_free(trace_view_t *trace_view);

trace_view_t *trace_view_parseFromJSON(cJSON *trace_viewJSON);

cJSON *trace_view_convertToJSON(trace_view_t *trace_view);

#endif /* _trace_view_H_ */

