/*
 * search_response.h
 *
 * 
 */

#ifndef _search_response_H_
#define _search_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct search_response_t search_response_t;

#include "search_hit.h"



typedef struct search_response_t {
    list_t *hits; //nonprimitive container

    int _library_owned; // Is the library responsible for freeing this object?
} search_response_t;

__attribute__((deprecated)) search_response_t *search_response_create(
    list_t *hits
);

void search_response_free(search_response_t *search_response);

search_response_t *search_response_parseFromJSON(cJSON *search_responseJSON);

cJSON *search_response_convertToJSON(search_response_t *search_response);

#endif /* _search_response_H_ */

