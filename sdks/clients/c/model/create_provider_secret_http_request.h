/*
 * create_provider_secret_http_request.h
 *
 * 
 */

#ifndef _create_provider_secret_http_request_H_
#define _create_provider_secret_http_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_provider_secret_http_request_t create_provider_secret_http_request_t;




typedef struct create_provider_secret_http_request_t {
    char *display_name; // string
    char *provider; // string
    char *secret_value; // string

    int _library_owned; // Is the library responsible for freeing this object?
} create_provider_secret_http_request_t;

__attribute__((deprecated)) create_provider_secret_http_request_t *create_provider_secret_http_request_create(
    char *display_name,
    char *provider,
    char *secret_value
);

void create_provider_secret_http_request_free(create_provider_secret_http_request_t *create_provider_secret_http_request);

create_provider_secret_http_request_t *create_provider_secret_http_request_parseFromJSON(cJSON *create_provider_secret_http_requestJSON);

cJSON *create_provider_secret_http_request_convertToJSON(create_provider_secret_http_request_t *create_provider_secret_http_request);

#endif /* _create_provider_secret_http_request_H_ */

