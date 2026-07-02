#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_candidate_change_request.h"



static gate_candidate_change_request_t *gate_candidate_change_request_create_internal(
    char *description,
    char *kind,
    char *proposed_by,
    char *rationale,
    char *target
    ) {
    gate_candidate_change_request_t *gate_candidate_change_request_local_var = malloc(sizeof(gate_candidate_change_request_t));
    if (!gate_candidate_change_request_local_var) {
        return NULL;
    }
    gate_candidate_change_request_local_var->description = description;
    gate_candidate_change_request_local_var->kind = kind;
    gate_candidate_change_request_local_var->proposed_by = proposed_by;
    gate_candidate_change_request_local_var->rationale = rationale;
    gate_candidate_change_request_local_var->target = target;

    gate_candidate_change_request_local_var->_library_owned = 1;
    return gate_candidate_change_request_local_var;
}

__attribute__((deprecated)) gate_candidate_change_request_t *gate_candidate_change_request_create(
    char *description,
    char *kind,
    char *proposed_by,
    char *rationale,
    char *target
    ) {
    return gate_candidate_change_request_create_internal (
        description,
        kind,
        proposed_by,
        rationale,
        target
        );
}

void gate_candidate_change_request_free(gate_candidate_change_request_t *gate_candidate_change_request) {
    if(NULL == gate_candidate_change_request){
        return ;
    }
    if(gate_candidate_change_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_candidate_change_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (gate_candidate_change_request->description) {
        free(gate_candidate_change_request->description);
        gate_candidate_change_request->description = NULL;
    }
    if (gate_candidate_change_request->kind) {
        free(gate_candidate_change_request->kind);
        gate_candidate_change_request->kind = NULL;
    }
    if (gate_candidate_change_request->proposed_by) {
        free(gate_candidate_change_request->proposed_by);
        gate_candidate_change_request->proposed_by = NULL;
    }
    if (gate_candidate_change_request->rationale) {
        free(gate_candidate_change_request->rationale);
        gate_candidate_change_request->rationale = NULL;
    }
    if (gate_candidate_change_request->target) {
        free(gate_candidate_change_request->target);
        gate_candidate_change_request->target = NULL;
    }
    free(gate_candidate_change_request);
}

cJSON *gate_candidate_change_request_convertToJSON(gate_candidate_change_request_t *gate_candidate_change_request) {
    cJSON *item = cJSON_CreateObject();

    // gate_candidate_change_request->description
    if (!gate_candidate_change_request->description) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "description", gate_candidate_change_request->description) == NULL) {
    goto fail; //String
    }


    // gate_candidate_change_request->kind
    if (!gate_candidate_change_request->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", gate_candidate_change_request->kind) == NULL) {
    goto fail; //String
    }


    // gate_candidate_change_request->proposed_by
    if (!gate_candidate_change_request->proposed_by) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "proposed_by", gate_candidate_change_request->proposed_by) == NULL) {
    goto fail; //String
    }


    // gate_candidate_change_request->rationale
    if (!gate_candidate_change_request->rationale) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "rationale", gate_candidate_change_request->rationale) == NULL) {
    goto fail; //String
    }


    // gate_candidate_change_request->target
    if (!gate_candidate_change_request->target) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "target", gate_candidate_change_request->target) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

gate_candidate_change_request_t *gate_candidate_change_request_parseFromJSON(cJSON *gate_candidate_change_requestJSON){

    gate_candidate_change_request_t *gate_candidate_change_request_local_var = NULL;

    // gate_candidate_change_request->description
    cJSON *description = cJSON_GetObjectItemCaseSensitive(gate_candidate_change_requestJSON, "description");
    if (cJSON_IsNull(description)) {
        description = NULL;
    }
    if (!description) {
        goto end;
    }

    
    if(!cJSON_IsString(description))
    {
    goto end; //String
    }

    // gate_candidate_change_request->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(gate_candidate_change_requestJSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    
    if(!cJSON_IsString(kind))
    {
    goto end; //String
    }

    // gate_candidate_change_request->proposed_by
    cJSON *proposed_by = cJSON_GetObjectItemCaseSensitive(gate_candidate_change_requestJSON, "proposed_by");
    if (cJSON_IsNull(proposed_by)) {
        proposed_by = NULL;
    }
    if (!proposed_by) {
        goto end;
    }

    
    if(!cJSON_IsString(proposed_by))
    {
    goto end; //String
    }

    // gate_candidate_change_request->rationale
    cJSON *rationale = cJSON_GetObjectItemCaseSensitive(gate_candidate_change_requestJSON, "rationale");
    if (cJSON_IsNull(rationale)) {
        rationale = NULL;
    }
    if (!rationale) {
        goto end;
    }

    
    if(!cJSON_IsString(rationale))
    {
    goto end; //String
    }

    // gate_candidate_change_request->target
    cJSON *target = cJSON_GetObjectItemCaseSensitive(gate_candidate_change_requestJSON, "target");
    if (cJSON_IsNull(target)) {
        target = NULL;
    }
    if (!target) {
        goto end;
    }

    
    if(!cJSON_IsString(target))
    {
    goto end; //String
    }


    gate_candidate_change_request_local_var = gate_candidate_change_request_create_internal (
        strdup(description->valuestring),
        strdup(kind->valuestring),
        strdup(proposed_by->valuestring),
        strdup(rationale->valuestring),
        strdup(target->valuestring)
        );

    return gate_candidate_change_request_local_var;
end:
    return NULL;

}
