/*
 * revoked_provider_secret.h
 *
 * 
 */

#ifndef _revoked_provider_secret_H_
#define _revoked_provider_secret_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct revoked_provider_secret_t revoked_provider_secret_t;




typedef struct revoked_provider_secret_t {
    int active; //boolean
    char *provider_secret_id; // string
    char *rotated_at; //date time

    int _library_owned; // Is the library responsible for freeing this object?
} revoked_provider_secret_t;

__attribute__((deprecated)) revoked_provider_secret_t *revoked_provider_secret_create(
    int active,
    char *provider_secret_id,
    char *rotated_at
);

void revoked_provider_secret_free(revoked_provider_secret_t *revoked_provider_secret);

revoked_provider_secret_t *revoked_provider_secret_parseFromJSON(cJSON *revoked_provider_secretJSON);

cJSON *revoked_provider_secret_convertToJSON(revoked_provider_secret_t *revoked_provider_secret);

#endif /* _revoked_provider_secret_H_ */

