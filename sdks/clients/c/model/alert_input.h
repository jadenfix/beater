/*
 * alert_input.h
 *
 * 
 */

#ifndef _alert_input_H_
#define _alert_input_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct alert_input_t alert_input_t;

#include "alert_links.h"



typedef struct alert_input_t {
    double baseline_score; //numeric
    char *group_key; // string
    struct alert_links_t *links; //model
    char *now; //date time
    char *project_id; // string
    double score; //numeric
    char *tenant_id; // string
    char *title; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} alert_input_t;

__attribute__((deprecated)) alert_input_t *alert_input_create(
    double baseline_score,
    char *group_key,
    alert_links_t *links,
    char *now,
    char *project_id,
    double score,
    char *tenant_id,
    char *title,
    char *trace_id
);

void alert_input_free(alert_input_t *alert_input);

alert_input_t *alert_input_parseFromJSON(cJSON *alert_inputJSON);

cJSON *alert_input_convertToJSON(alert_input_t *alert_input);

#endif /* _alert_input_H_ */

