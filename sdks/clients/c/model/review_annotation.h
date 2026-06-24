/*
 * review_annotation.h
 *
 * 
 */

#ifndef _review_annotation_H_
#define _review_annotation_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct review_annotation_t review_annotation_t;

#include "any_type.h"
#include "review_verdict.h"



typedef struct review_annotation_t {
    char *annotation_id; // string
    char *created_at; //date time
    any_type_t *payload; // custom
    char *project_id; // string
    char *queue_id; // string
    char *reviewer_id; // string
    char *task_id; // string
    char *tenant_id; // string
    beater_api_review_verdict__e verdict; //referenced enum

    int _library_owned; // Is the library responsible for freeing this object?
} review_annotation_t;

__attribute__((deprecated)) review_annotation_t *review_annotation_create(
    char *annotation_id,
    char *created_at,
    any_type_t *payload,
    char *project_id,
    char *queue_id,
    char *reviewer_id,
    char *task_id,
    char *tenant_id,
    beater_api_review_verdict__e verdict
);

void review_annotation_free(review_annotation_t *review_annotation);

review_annotation_t *review_annotation_parseFromJSON(cJSON *review_annotationJSON);

cJSON *review_annotation_convertToJSON(review_annotation_t *review_annotation);

#endif /* _review_annotation_H_ */

