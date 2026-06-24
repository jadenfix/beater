/*
 * search_hit.h
 *
 * 
 */

#ifndef _search_hit_H_
#define _search_hit_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct search_hit_t search_hit_t;




typedef struct search_hit_t {
    char *environment_id; // string
    char *kind; // string
    char *model; // string
    char *name; // string
    char *project_id; // string
    float score; //numeric
    char *span_id; // string
    char *status; // string
    char *tenant_id; // string
    char *tool; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} search_hit_t;

__attribute__((deprecated)) search_hit_t *search_hit_create(
    char *environment_id,
    char *kind,
    char *model,
    char *name,
    char *project_id,
    float score,
    char *span_id,
    char *status,
    char *tenant_id,
    char *tool,
    char *trace_id
);

void search_hit_free(search_hit_t *search_hit);

search_hit_t *search_hit_parseFromJSON(cJSON *search_hitJSON);

cJSON *search_hit_convertToJSON(search_hit_t *search_hit);

#endif /* _search_hit_H_ */

