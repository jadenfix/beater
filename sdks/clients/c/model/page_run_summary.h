/*
 * page_run_summary.h
 *
 * 
 */

#ifndef _page_run_summary_H_
#define _page_run_summary_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct page_run_summary_t page_run_summary_t;

#include "page_run_summary_items_inner.h"



typedef struct page_run_summary_t {
    list_t *items; //nonprimitive container
    char *next_cursor; // string

    int _library_owned; // Is the library responsible for freeing this object?
} page_run_summary_t;

__attribute__((deprecated)) page_run_summary_t *page_run_summary_create(
    list_t *items,
    char *next_cursor
);

void page_run_summary_free(page_run_summary_t *page_run_summary);

page_run_summary_t *page_run_summary_parseFromJSON(cJSON *page_run_summaryJSON);

cJSON *page_run_summary_convertToJSON(page_run_summary_t *page_run_summary);

#endif /* _page_run_summary_H_ */

