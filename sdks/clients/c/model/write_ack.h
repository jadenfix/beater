/*
 * write_ack.h
 *
 * 
 */

#ifndef _write_ack_H_
#define _write_ack_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct write_ack_t write_ack_t;




typedef struct write_ack_t {
    int accepted_raw; //numeric
    int accepted_spans; //numeric
    int duplicate_raw; //numeric
    int duplicate_spans; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} write_ack_t;

__attribute__((deprecated)) write_ack_t *write_ack_create(
    int accepted_raw,
    int accepted_spans,
    int duplicate_raw,
    int duplicate_spans
);

void write_ack_free(write_ack_t *write_ack);

write_ack_t *write_ack_parseFromJSON(cJSON *write_ackJSON);

cJSON *write_ack_convertToJSON(write_ack_t *write_ack);

#endif /* _write_ack_H_ */

