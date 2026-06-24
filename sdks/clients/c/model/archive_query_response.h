/*
 * archive_query_response.h
 *
 * 
 */

#ifndef _archive_query_response_H_
#define _archive_query_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct archive_query_response_t archive_query_response_t;

#include "archived_span_row.h"



typedef struct archive_query_response_t {
    list_t *rows; //nonprimitive container

    int _library_owned; // Is the library responsible for freeing this object?
} archive_query_response_t;

__attribute__((deprecated)) archive_query_response_t *archive_query_response_create(
    list_t *rows
);

void archive_query_response_free(archive_query_response_t *archive_query_response);

archive_query_response_t *archive_query_response_parseFromJSON(cJSON *archive_query_responseJSON);

cJSON *archive_query_response_convertToJSON(archive_query_response_t *archive_query_response);

#endif /* _archive_query_response_H_ */

