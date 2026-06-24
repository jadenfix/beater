/*
 * gate_definition.h
 *
 * 
 */

#ifndef _gate_definition_H_
#define _gate_definition_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_definition_t gate_definition_t;

#include "inconclusive_policy.h"



typedef struct gate_definition_t {
    char *created_at; //date time
    char *dataset_id; // string
    char *evaluator_version_id; // string
    char *gate_id; // string
    beater_api_inconclusive_policy__e inconclusive_policy; //referenced enum
    char *name; // string
    char *project_id; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} gate_definition_t;

__attribute__((deprecated)) gate_definition_t *gate_definition_create(
    char *created_at,
    char *dataset_id,
    char *evaluator_version_id,
    char *gate_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    char *name,
    char *project_id,
    char *tenant_id
);

void gate_definition_free(gate_definition_t *gate_definition);

gate_definition_t *gate_definition_parseFromJSON(cJSON *gate_definitionJSON);

cJSON *gate_definition_convertToJSON(gate_definition_t *gate_definition);

#endif /* _gate_definition_H_ */

