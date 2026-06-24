/*
 * alert_links.h
 *
 * 
 */

#ifndef _alert_links_H_
#define _alert_links_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct alert_links_t alert_links_t;




typedef struct alert_links_t {
    char *cluster_url; // string
    char *dataset_url; // string
    char *gate_url; // string
    char *trace_url; // string

    int _library_owned; // Is the library responsible for freeing this object?
} alert_links_t;

__attribute__((deprecated)) alert_links_t *alert_links_create(
    char *cluster_url,
    char *dataset_url,
    char *gate_url,
    char *trace_url
);

void alert_links_free(alert_links_t *alert_links);

alert_links_t *alert_links_parseFromJSON(cJSON *alert_linksJSON);

cJSON *alert_links_convertToJSON(alert_links_t *alert_links);

#endif /* _alert_links_H_ */

