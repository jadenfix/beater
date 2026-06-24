/*
 * promote_review_annotation_http_request.h
 *
 * 
 */

#ifndef _promote_review_annotation_http_request_H_
#define _promote_review_annotation_http_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct promote_review_annotation_http_request_t promote_review_annotation_http_request_t;

#include "any_type.h"



typedef struct promote_review_annotation_http_request_t {
    char *dataset_id; // string
    any_type_t *reference; // custom

    int _library_owned; // Is the library responsible for freeing this object?
} promote_review_annotation_http_request_t;

__attribute__((deprecated)) promote_review_annotation_http_request_t *promote_review_annotation_http_request_create(
    char *dataset_id,
    any_type_t *reference
);

void promote_review_annotation_http_request_free(promote_review_annotation_http_request_t *promote_review_annotation_http_request);

promote_review_annotation_http_request_t *promote_review_annotation_http_request_parseFromJSON(cJSON *promote_review_annotation_http_requestJSON);

cJSON *promote_review_annotation_http_request_convertToJSON(promote_review_annotation_http_request_t *promote_review_annotation_http_request);

#endif /* _promote_review_annotation_http_request_H_ */

