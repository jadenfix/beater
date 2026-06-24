/*
 * review_queue.h
 *
 * 
 */

#ifndef _review_queue_H_
#define _review_queue_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct review_queue_t review_queue_t;

#include "any_type.h"



typedef struct review_queue_t {
    any_type_t *annotation_schema; // custom
    char *created_at; //date time
    char *name; // string
    char *project_id; // string
    char *queue_id; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} review_queue_t;

__attribute__((deprecated)) review_queue_t *review_queue_create(
    any_type_t *annotation_schema,
    char *created_at,
    char *name,
    char *project_id,
    char *queue_id,
    char *tenant_id
);

void review_queue_free(review_queue_t *review_queue);

review_queue_t *review_queue_parseFromJSON(cJSON *review_queueJSON);

cJSON *review_queue_convertToJSON(review_queue_t *review_queue);

#endif /* _review_queue_H_ */

