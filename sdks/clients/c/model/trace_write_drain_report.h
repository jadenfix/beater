/*
 * trace_write_drain_report.h
 *
 * 
 */

#ifndef _trace_write_drain_report_H_
#define _trace_write_drain_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct trace_write_drain_report_t trace_write_drain_report_t;

#include "queued_trace_work.h"



typedef struct trace_write_drain_report_t {
    int consumed; //numeric
    int dead_lettered; //numeric
    int downstream_published; //numeric
    int duplicate_raw; //numeric
    int duplicate_spans; //numeric
    int failed_downstream_publishes; //numeric
    int failed_writes; //numeric
    int invalid_messages; //numeric
    int retried; //numeric
    list_t *trace_ids; //primitive container
    list_t *trace_refs; //nonprimitive container
    int written_raw; //numeric
    int written_spans; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} trace_write_drain_report_t;

__attribute__((deprecated)) trace_write_drain_report_t *trace_write_drain_report_create(
    int consumed,
    int dead_lettered,
    int downstream_published,
    int duplicate_raw,
    int duplicate_spans,
    int failed_downstream_publishes,
    int failed_writes,
    int invalid_messages,
    int retried,
    list_t *trace_ids,
    list_t *trace_refs,
    int written_raw,
    int written_spans
);

void trace_write_drain_report_free(trace_write_drain_report_t *trace_write_drain_report);

trace_write_drain_report_t *trace_write_drain_report_parseFromJSON(cJSON *trace_write_drain_reportJSON);

cJSON *trace_write_drain_report_convertToJSON(trace_write_drain_report_t *trace_write_drain_report);

#endif /* _trace_write_drain_report_H_ */

