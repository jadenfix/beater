/*
 * health_response.h
 *
 * 
 */

#ifndef _health_response_H_
#define _health_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct health_response_t health_response_t;




typedef struct health_response_t {
    int ok; //boolean

    int _library_owned; // Is the library responsible for freeing this object?
} health_response_t;

__attribute__((deprecated)) health_response_t *health_response_create(
    int ok
);

void health_response_free(health_response_t *health_response);

health_response_t *health_response_parseFromJSON(cJSON *health_responseJSON);

cJSON *health_response_convertToJSON(health_response_t *health_response);

#endif /* _health_response_H_ */

