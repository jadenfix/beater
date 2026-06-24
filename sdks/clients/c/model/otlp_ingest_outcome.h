/*
 * otlp_ingest_outcome.h
 *
 * 
 */

#ifndef _otlp_ingest_outcome_H_
#define _otlp_ingest_outcome_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct otlp_ingest_outcome_t otlp_ingest_outcome_t;




typedef struct otlp_ingest_outcome_t {
    int accepted_raw; //numeric
    int accepted_spans; //numeric
    int downstream_queued; //boolean
    int duplicate_raw; //numeric
    int duplicate_spans; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} otlp_ingest_outcome_t;

__attribute__((deprecated)) otlp_ingest_outcome_t *otlp_ingest_outcome_create(
    int accepted_raw,
    int accepted_spans,
    int downstream_queued,
    int duplicate_raw,
    int duplicate_spans
);

void otlp_ingest_outcome_free(otlp_ingest_outcome_t *otlp_ingest_outcome);

otlp_ingest_outcome_t *otlp_ingest_outcome_parseFromJSON(cJSON *otlp_ingest_outcomeJSON);

cJSON *otlp_ingest_outcome_convertToJSON(otlp_ingest_outcome_t *otlp_ingest_outcome);

#endif /* _otlp_ingest_outcome_H_ */

