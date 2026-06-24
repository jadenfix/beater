/*
 * usage_summary.h
 *
 * 
 */

#ifndef _usage_summary_H_
#define _usage_summary_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct usage_summary_t usage_summary_t;

#include "usage_total.h"



typedef struct usage_summary_t {
    char *project_id; // string
    char *tenant_id; // string
    list_t* totals; //map

    int _library_owned; // Is the library responsible for freeing this object?
} usage_summary_t;

__attribute__((deprecated)) usage_summary_t *usage_summary_create(
    char *project_id,
    char *tenant_id,
    list_t* totals
);

void usage_summary_free(usage_summary_t *usage_summary);

usage_summary_t *usage_summary_parseFromJSON(cJSON *usage_summaryJSON);

cJSON *usage_summary_convertToJSON(usage_summary_t *usage_summary);

#endif /* _usage_summary_H_ */

