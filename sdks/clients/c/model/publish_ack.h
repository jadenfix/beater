/*
 * publish_ack.h
 *
 * 
 */

#ifndef _publish_ack_H_
#define _publish_ack_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct publish_ack_t publish_ack_t;




typedef struct publish_ack_t {
    int accepted; //boolean
    int duplicate; //boolean

    int _library_owned; // Is the library responsible for freeing this object?
} publish_ack_t;

__attribute__((deprecated)) publish_ack_t *publish_ack_create(
    int accepted,
    int duplicate
);

void publish_ack_free(publish_ack_t *publish_ack);

publish_ack_t *publish_ack_parseFromJSON(cJSON *publish_ackJSON);

cJSON *publish_ack_convertToJSON(publish_ack_t *publish_ack);

#endif /* _publish_ack_H_ */

