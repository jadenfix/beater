/*
 * token_counts.h
 *
 * 
 */

#ifndef _token_counts_H_
#define _token_counts_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct token_counts_t token_counts_t;




typedef struct token_counts_t {
    long cache_read; //numeric
    long input; //numeric
    long output; //numeric
    long reasoning; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} token_counts_t;

__attribute__((deprecated)) token_counts_t *token_counts_create(
    long cache_read,
    long input,
    long output,
    long reasoning
);

void token_counts_free(token_counts_t *token_counts);

token_counts_t *token_counts_parseFromJSON(cJSON *token_countsJSON);

cJSON *token_counts_convertToJSON(token_counts_t *token_counts);

#endif /* _token_counts_H_ */

