/*
 * submit_review_annotation_http_request.h
 *
 * 
 */

#ifndef _submit_review_annotation_http_request_H_
#define _submit_review_annotation_http_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct submit_review_annotation_http_request_t submit_review_annotation_http_request_t;

#include "any_type.h"
#include "review_verdict.h"



typedef struct submit_review_annotation_http_request_t {
    char *annotation_id; // string
    any_type_t *payload; // custom
    char *reviewer_id; // string
    beater_api_review_verdict__e verdict; //referenced enum

    int _library_owned; // Is the library responsible for freeing this object?
} submit_review_annotation_http_request_t;

__attribute__((deprecated)) submit_review_annotation_http_request_t *submit_review_annotation_http_request_create(
    char *annotation_id,
    any_type_t *payload,
    char *reviewer_id,
    beater_api_review_verdict__e verdict
);

void submit_review_annotation_http_request_free(submit_review_annotation_http_request_t *submit_review_annotation_http_request);

submit_review_annotation_http_request_t *submit_review_annotation_http_request_parseFromJSON(cJSON *submit_review_annotation_http_requestJSON);

cJSON *submit_review_annotation_http_request_convertToJSON(submit_review_annotation_http_request_t *submit_review_annotation_http_request);

#endif /* _submit_review_annotation_http_request_H_ */

