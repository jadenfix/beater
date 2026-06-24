/*
 * provider_secret_metadata.h
 *
 * 
 */

#ifndef _provider_secret_metadata_H_
#define _provider_secret_metadata_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct provider_secret_metadata_t provider_secret_metadata_t;




typedef struct provider_secret_metadata_t {
    int active; //boolean
    char *created_at; //date time
    char *display_name; // string
    char *project_id; // string
    char *provider; // string
    char *provider_secret_id; // string
    char *rotated_at; //date time
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} provider_secret_metadata_t;

__attribute__((deprecated)) provider_secret_metadata_t *provider_secret_metadata_create(
    int active,
    char *created_at,
    char *display_name,
    char *project_id,
    char *provider,
    char *provider_secret_id,
    char *rotated_at,
    char *tenant_id
);

void provider_secret_metadata_free(provider_secret_metadata_t *provider_secret_metadata);

provider_secret_metadata_t *provider_secret_metadata_parseFromJSON(cJSON *provider_secret_metadataJSON);

cJSON *provider_secret_metadata_convertToJSON(provider_secret_metadata_t *provider_secret_metadata);

#endif /* _provider_secret_metadata_H_ */

