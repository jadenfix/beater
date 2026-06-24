/*
 * trace_ingested_reconcile_report.h
 *
 * 
 */

#ifndef _trace_ingested_reconcile_report_H_
#define _trace_ingested_reconcile_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct trace_ingested_reconcile_report_t trace_ingested_reconcile_report_t;




typedef struct trace_ingested_reconcile_report_t {
    int downstream_accepted; //numeric
    int downstream_duplicate; //numeric
    int downstream_queued; //boolean
    char *project_id; // string
    int span_count; //numeric
    char *tenant_id; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} trace_ingested_reconcile_report_t;

__attribute__((deprecated)) trace_ingested_reconcile_report_t *trace_ingested_reconcile_report_create(
    int downstream_accepted,
    int downstream_duplicate,
    int downstream_queued,
    char *project_id,
    int span_count,
    char *tenant_id,
    char *trace_id
);

void trace_ingested_reconcile_report_free(trace_ingested_reconcile_report_t *trace_ingested_reconcile_report);

trace_ingested_reconcile_report_t *trace_ingested_reconcile_report_parseFromJSON(cJSON *trace_ingested_reconcile_reportJSON);

cJSON *trace_ingested_reconcile_report_convertToJSON(trace_ingested_reconcile_report_t *trace_ingested_reconcile_report);

#endif /* _trace_ingested_reconcile_report_H_ */

