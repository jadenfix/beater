/*
 * run_summary.h
 *
 * 
 */

#ifndef _run_summary_H_
#define _run_summary_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct run_summary_t run_summary_t;

#include "model_ref.h"
#include "money.h"
#include "span_status.h"



typedef struct run_summary_t {
    long duration_ms; //numeric
    char *ended_at; //date time
    char *first_span_name; // string
    list_t *models; //nonprimitive container
    char *project_id; // string
    list_t *release_ids; //primitive container
    int span_count; //numeric
    char *started_at; //date time
    beater_api_span_status__e status; //referenced enum
    char *tenant_id; // string
    struct money_t *total_cost; //model
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} run_summary_t;

__attribute__((deprecated)) run_summary_t *run_summary_create(
    long duration_ms,
    char *ended_at,
    char *first_span_name,
    list_t *models,
    char *project_id,
    list_t *release_ids,
    int span_count,
    char *started_at,
    beater_api_span_status__e status,
    char *tenant_id,
    money_t *total_cost,
    char *trace_id
);

void run_summary_free(run_summary_t *run_summary);

run_summary_t *run_summary_parseFromJSON(cJSON *run_summaryJSON);

cJSON *run_summary_convertToJSON(run_summary_t *run_summary);

#endif /* _run_summary_H_ */

