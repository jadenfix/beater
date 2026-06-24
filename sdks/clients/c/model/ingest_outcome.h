/*
 * ingest_outcome.h
 *
 * 
 */

#ifndef _ingest_outcome_H_
#define _ingest_outcome_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct ingest_outcome_t ingest_outcome_t;

#include "write_ack.h"



typedef struct ingest_outcome_t {
    struct write_ack_t *ack; //model
    int downstream_queued; //boolean

    int _library_owned; // Is the library responsible for freeing this object?
} ingest_outcome_t;

__attribute__((deprecated)) ingest_outcome_t *ingest_outcome_create(
    write_ack_t *ack,
    int downstream_queued
);

void ingest_outcome_free(ingest_outcome_t *ingest_outcome);

ingest_outcome_t *ingest_outcome_parseFromJSON(cJSON *ingest_outcomeJSON);

cJSON *ingest_outcome_convertToJSON(ingest_outcome_t *ingest_outcome);

#endif /* _ingest_outcome_H_ */

