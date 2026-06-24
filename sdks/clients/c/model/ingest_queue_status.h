/*
 * ingest_queue_status.h
 *
 * 
 */

#ifndef _ingest_queue_status_H_
#define _ingest_queue_status_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct ingest_queue_status_t ingest_queue_status_t;

#include "dead_letter.h"



typedef struct ingest_queue_status_t {
    list_t *dead_letters; //nonprimitive container
    char *project_id; // string
    char *tenant_id; // string
    int total_depth; //numeric
    int trace_ingested_depth; //numeric
    int trace_write_depth; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} ingest_queue_status_t;

__attribute__((deprecated)) ingest_queue_status_t *ingest_queue_status_create(
    list_t *dead_letters,
    char *project_id,
    char *tenant_id,
    int total_depth,
    int trace_ingested_depth,
    int trace_write_depth
);

void ingest_queue_status_free(ingest_queue_status_t *ingest_queue_status);

ingest_queue_status_t *ingest_queue_status_parseFromJSON(cJSON *ingest_queue_statusJSON);

cJSON *ingest_queue_status_convertToJSON(ingest_queue_status_t *ingest_queue_status);

#endif /* _ingest_queue_status_H_ */

