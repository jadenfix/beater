/*
 * archive_manifest.h
 *
 * 
 */

#ifndef _archive_manifest_H_
#define _archive_manifest_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct archive_manifest_t archive_manifest_t;




typedef struct archive_manifest_t {
    char *created_at; //date time
    char *path; // string
    char *project_id; // string
    int span_count; //numeric
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} archive_manifest_t;

__attribute__((deprecated)) archive_manifest_t *archive_manifest_create(
    char *created_at,
    char *path,
    char *project_id,
    int span_count,
    char *tenant_id
);

void archive_manifest_free(archive_manifest_t *archive_manifest);

archive_manifest_t *archive_manifest_parseFromJSON(cJSON *archive_manifestJSON);

cJSON *archive_manifest_convertToJSON(archive_manifest_t *archive_manifest);

#endif /* _archive_manifest_H_ */

