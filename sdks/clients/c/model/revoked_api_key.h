/*
 * revoked_api_key.h
 *
 * 
 */

#ifndef _revoked_api_key_H_
#define _revoked_api_key_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct revoked_api_key_t revoked_api_key_t;




typedef struct revoked_api_key_t {
    int active; //boolean
    char *api_key_id; // string
    char *rotated_at; //date time

    int _library_owned; // Is the library responsible for freeing this object?
} revoked_api_key_t;

__attribute__((deprecated)) revoked_api_key_t *revoked_api_key_create(
    int active,
    char *api_key_id,
    char *rotated_at
);

void revoked_api_key_free(revoked_api_key_t *revoked_api_key);

revoked_api_key_t *revoked_api_key_parseFromJSON(cJSON *revoked_api_keyJSON);

cJSON *revoked_api_key_convertToJSON(revoked_api_key_t *revoked_api_key);

#endif /* _revoked_api_key_H_ */

