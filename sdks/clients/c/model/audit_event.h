/*
 * audit_event.h
 *
 * 
 */

#ifndef _audit_event_H_
#define _audit_event_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct audit_event_t audit_event_t;

#include "any_type.h"
#include "audit_action.h"
#include "audit_outcome.h"



typedef struct audit_event_t {
    beater_api_audit_action__e action; //referenced enum
    char *actor_api_key_id; // string
    any_type_t *attributes; // custom
    char *audit_event_id; // string
    char *created_at; //date time
    char *environment_id; // string
    beater_api_audit_outcome__e outcome; //referenced enum
    char *project_id; // string
    char *reason; // string
    char *resource_id; // string
    char *resource_type; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} audit_event_t;

__attribute__((deprecated)) audit_event_t *audit_event_create(
    beater_api_audit_action__e action,
    char *actor_api_key_id,
    any_type_t *attributes,
    char *audit_event_id,
    char *created_at,
    char *environment_id,
    beater_api_audit_outcome__e outcome,
    char *project_id,
    char *reason,
    char *resource_id,
    char *resource_type,
    char *tenant_id
);

void audit_event_free(audit_event_t *audit_event);

audit_event_t *audit_event_parseFromJSON(cJSON *audit_eventJSON);

cJSON *audit_event_convertToJSON(audit_event_t *audit_event);

#endif /* _audit_event_H_ */

