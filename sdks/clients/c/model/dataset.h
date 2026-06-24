/*
 * dataset.h
 *
 * 
 */

#ifndef _dataset_H_
#define _dataset_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct dataset_t dataset_t;




typedef struct dataset_t {
    char *created_at; //date time
    char *dataset_id; // string
    char *name; // string
    char *project_id; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} dataset_t;

__attribute__((deprecated)) dataset_t *dataset_create(
    char *created_at,
    char *dataset_id,
    char *name,
    char *project_id,
    char *tenant_id
);

void dataset_free(dataset_t *dataset);

dataset_t *dataset_parseFromJSON(cJSON *datasetJSON);

cJSON *dataset_convertToJSON(dataset_t *dataset);

#endif /* _dataset_H_ */

