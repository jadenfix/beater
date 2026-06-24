/*
 * usage_total.h
 *
 * 
 */

#ifndef _usage_total_H_
#define _usage_total_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct usage_total_t usage_total_t;




typedef struct usage_total_t {
    long quantity; //numeric
    char *unit; // string

    int _library_owned; // Is the library responsible for freeing this object?
} usage_total_t;

__attribute__((deprecated)) usage_total_t *usage_total_create(
    long quantity,
    char *unit
);

void usage_total_free(usage_total_t *usage_total);

usage_total_t *usage_total_parseFromJSON(cJSON *usage_totalJSON);

cJSON *usage_total_convertToJSON(usage_total_t *usage_total);

#endif /* _usage_total_H_ */

