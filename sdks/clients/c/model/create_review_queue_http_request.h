/*
 * create_review_queue_http_request.h
 *
 * 
 */

#ifndef _create_review_queue_http_request_H_
#define _create_review_queue_http_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_review_queue_http_request_t create_review_queue_http_request_t;

#include "any_type.h"



typedef struct create_review_queue_http_request_t {
    any_type_t *annotation_schema; // custom
    char *name; // string
    char *queue_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} create_review_queue_http_request_t;

__attribute__((deprecated)) create_review_queue_http_request_t *create_review_queue_http_request_create(
    any_type_t *annotation_schema,
    char *name,
    char *queue_id
);

void create_review_queue_http_request_free(create_review_queue_http_request_t *create_review_queue_http_request);

create_review_queue_http_request_t *create_review_queue_http_request_parseFromJSON(cJSON *create_review_queue_http_requestJSON);

cJSON *create_review_queue_http_request_convertToJSON(create_review_queue_http_request_t *create_review_queue_http_request);

#endif /* _create_review_queue_http_request_H_ */

