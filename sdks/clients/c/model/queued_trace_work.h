/*
 * queued_trace_work.h
 *
 * 
 */

#ifndef _queued_trace_work_H_
#define _queued_trace_work_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct queued_trace_work_t queued_trace_work_t;




typedef struct queued_trace_work_t {
    char *project_id; // string
    char *tenant_id; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} queued_trace_work_t;

__attribute__((deprecated)) queued_trace_work_t *queued_trace_work_create(
    char *project_id,
    char *tenant_id,
    char *trace_id
);

void queued_trace_work_free(queued_trace_work_t *queued_trace_work);

queued_trace_work_t *queued_trace_work_parseFromJSON(cJSON *queued_trace_workJSON);

cJSON *queued_trace_work_convertToJSON(queued_trace_work_t *queued_trace_work);

#endif /* _queued_trace_work_H_ */

