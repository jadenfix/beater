/*
 * auth_context.h
 *
 * 
 */

#ifndef _auth_context_H_
#define _auth_context_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct auth_context_t auth_context_t;




typedef struct auth_context_t {
    char *api_key_id; // string
    list_t *scopes; //primitive container

    int _library_owned; // Is the library responsible for freeing this object?
} auth_context_t;

__attribute__((deprecated)) auth_context_t *auth_context_create(
    char *api_key_id,
    list_t *scopes
);

void auth_context_free(auth_context_t *auth_context);

auth_context_t *auth_context_parseFromJSON(cJSON *auth_contextJSON);

cJSON *auth_context_convertToJSON(auth_context_t *auth_context);

#endif /* _auth_context_H_ */

