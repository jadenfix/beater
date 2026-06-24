/*
 * tenant_scope.h
 *
 * 
 */

#ifndef _tenant_scope_H_
#define _tenant_scope_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct tenant_scope_t tenant_scope_t;




typedef struct tenant_scope_t {
    char *environment_id; // string
    char *project_id; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} tenant_scope_t;

__attribute__((deprecated)) tenant_scope_t *tenant_scope_create(
    char *environment_id,
    char *project_id,
    char *tenant_id
);

void tenant_scope_free(tenant_scope_t *tenant_scope);

tenant_scope_t *tenant_scope_parseFromJSON(cJSON *tenant_scopeJSON);

cJSON *tenant_scope_convertToJSON(tenant_scope_t *tenant_scope);

#endif /* _tenant_scope_H_ */

