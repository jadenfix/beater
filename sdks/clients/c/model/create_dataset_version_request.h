/*
 * create_dataset_version_request.h
 *
 * 
 */

#ifndef _create_dataset_version_request_H_
#define _create_dataset_version_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_dataset_version_request_t create_dataset_version_request_t;




typedef struct create_dataset_version_request_t {
    list_t *case_ids; //primitive container

    int _library_owned; // Is the library responsible for freeing this object?
} create_dataset_version_request_t;

__attribute__((deprecated)) create_dataset_version_request_t *create_dataset_version_request_create(
    list_t *case_ids
);

void create_dataset_version_request_free(create_dataset_version_request_t *create_dataset_version_request);

create_dataset_version_request_t *create_dataset_version_request_parseFromJSON(cJSON *create_dataset_version_requestJSON);

cJSON *create_dataset_version_request_convertToJSON(create_dataset_version_request_t *create_dataset_version_request);

#endif /* _create_dataset_version_request_H_ */

