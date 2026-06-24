/*
 * bus_message.h
 *
 * 
 */

#ifndef _bus_message_H_
#define _bus_message_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct bus_message_t bus_message_t;




typedef struct bus_message_t {
    int attempts; //numeric
    char *enqueued_at; //date time
    char *idempotency_key; // string
    char *kind; // string
    int max_attempts; //numeric
    char *message_id; // string
    list_t *payload; //primitive container
    char *project_id; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} bus_message_t;

__attribute__((deprecated)) bus_message_t *bus_message_create(
    int attempts,
    char *enqueued_at,
    char *idempotency_key,
    char *kind,
    int max_attempts,
    char *message_id,
    list_t *payload,
    char *project_id,
    char *tenant_id
);

void bus_message_free(bus_message_t *bus_message);

bus_message_t *bus_message_parseFromJSON(cJSON *bus_messageJSON);

cJSON *bus_message_convertToJSON(bus_message_t *bus_message);

#endif /* _bus_message_H_ */

