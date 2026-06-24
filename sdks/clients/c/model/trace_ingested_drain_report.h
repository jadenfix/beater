/*
 * trace_ingested_drain_report.h
 *
 * 
 */

#ifndef _trace_ingested_drain_report_H_
#define _trace_ingested_drain_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct trace_ingested_drain_report_t trace_ingested_drain_report_t;

#include "queued_trace_work.h"



typedef struct trace_ingested_drain_report_t {
    int completed; //numeric
    int consumed; //numeric
    int dead_lettered; //numeric
    int failed_work; //numeric
    int invalid_messages; //numeric
    int retried; //numeric
    list_t *trace_refs; //nonprimitive container

    int _library_owned; // Is the library responsible for freeing this object?
} trace_ingested_drain_report_t;

__attribute__((deprecated)) trace_ingested_drain_report_t *trace_ingested_drain_report_create(
    int completed,
    int consumed,
    int dead_lettered,
    int failed_work,
    int invalid_messages,
    int retried,
    list_t *trace_refs
);

void trace_ingested_drain_report_free(trace_ingested_drain_report_t *trace_ingested_drain_report);

trace_ingested_drain_report_t *trace_ingested_drain_report_parseFromJSON(cJSON *trace_ingested_drain_reportJSON);

cJSON *trace_ingested_drain_report_convertToJSON(trace_ingested_drain_report_t *trace_ingested_drain_report);

#endif /* _trace_ingested_drain_report_H_ */

