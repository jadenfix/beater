/*
 * webhook_delivery.h
 *
 * 
 */

#ifndef _webhook_delivery_H_
#define _webhook_delivery_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct webhook_delivery_t webhook_delivery_t;

#include "any_type.h"



typedef struct webhook_delivery_t {
    any_type_t *body; // custom
    char *endpoint_url; // string
    list_t* headers; //map

    int _library_owned; // Is the library responsible for freeing this object?
} webhook_delivery_t;

__attribute__((deprecated)) webhook_delivery_t *webhook_delivery_create(
    any_type_t *body,
    char *endpoint_url,
    list_t* headers
);

void webhook_delivery_free(webhook_delivery_t *webhook_delivery);

webhook_delivery_t *webhook_delivery_parseFromJSON(cJSON *webhook_deliveryJSON);

cJSON *webhook_delivery_convertToJSON(webhook_delivery_t *webhook_delivery);

#endif /* _webhook_delivery_H_ */

