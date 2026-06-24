/*
 * enqueue_review_task_from_trace_http_request.h
 *
 * 
 */

#ifndef _enqueue_review_task_from_trace_http_request_H_
#define _enqueue_review_task_from_trace_http_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct enqueue_review_task_from_trace_http_request_t enqueue_review_task_from_trace_http_request_t;




typedef struct enqueue_review_task_from_trace_http_request_t {
    char *dataset_case_id; // string
    char *dataset_id; // string
    long priority; //numeric
    char *span_id; // string
    char *task_id; // string
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} enqueue_review_task_from_trace_http_request_t;

__attribute__((deprecated)) enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request_create(
    char *dataset_case_id,
    char *dataset_id,
    long priority,
    char *span_id,
    char *task_id,
    char *trace_id
);

void enqueue_review_task_from_trace_http_request_free(enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request);

enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request_parseFromJSON(cJSON *enqueue_review_task_from_trace_http_requestJSON);

cJSON *enqueue_review_task_from_trace_http_request_convertToJSON(enqueue_review_task_from_trace_http_request_t *enqueue_review_task_from_trace_http_request);

#endif /* _enqueue_review_task_from_trace_http_request_H_ */

