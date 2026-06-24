/*
 * page_run_summary_items_inner.h
 *
 * 
 */

#ifndef _page_run_summary_items_inner_H_
#define _page_run_summary_items_inner_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct page_run_summary_items_inner_t page_run_summary_items_inner_t;

#include "model_ref.h"
#include "money.h"
#include "span_status.h"



typedef struct page_run_summary_items_inner_t {
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
} page_run_summary_items_inner_t;

__attribute__((deprecated)) page_run_summary_items_inner_t *page_run_summary_items_inner_create(
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

void page_run_summary_items_inner_free(page_run_summary_items_inner_t *page_run_summary_items_inner);

page_run_summary_items_inner_t *page_run_summary_items_inner_parseFromJSON(cJSON *page_run_summary_items_innerJSON);

cJSON *page_run_summary_items_inner_convertToJSON(page_run_summary_items_inner_t *page_run_summary_items_inner);

#endif /* _page_run_summary_items_inner_H_ */

