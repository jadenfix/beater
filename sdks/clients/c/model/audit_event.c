#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "audit_event.h"



static audit_event_t *audit_event_create_internal(
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
    ) {
    audit_event_t *audit_event_local_var = malloc(sizeof(audit_event_t));
    if (!audit_event_local_var) {
        return NULL;
    }
    audit_event_local_var->action = action;
    audit_event_local_var->actor_api_key_id = actor_api_key_id;
    audit_event_local_var->attributes = attributes;
    audit_event_local_var->audit_event_id = audit_event_id;
    audit_event_local_var->created_at = created_at;
    audit_event_local_var->environment_id = environment_id;
    audit_event_local_var->outcome = outcome;
    audit_event_local_var->project_id = project_id;
    audit_event_local_var->reason = reason;
    audit_event_local_var->resource_id = resource_id;
    audit_event_local_var->resource_type = resource_type;
    audit_event_local_var->tenant_id = tenant_id;

    audit_event_local_var->_library_owned = 1;
    return audit_event_local_var;
}

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
    ) {
    return audit_event_create_internal (
        action,
        actor_api_key_id,
        attributes,
        audit_event_id,
        created_at,
        environment_id,
        outcome,
        project_id,
        reason,
        resource_id,
        resource_type,
        tenant_id
        );
}

void audit_event_free(audit_event_t *audit_event) {
    if(NULL == audit_event){
        return ;
    }
    if(audit_event->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "audit_event_free");
        return ;
    }
    listEntry_t *listEntry;
    if (audit_event->actor_api_key_id) {
        free(audit_event->actor_api_key_id);
        audit_event->actor_api_key_id = NULL;
    }
    if (audit_event->attributes) {
        _free(audit_event->attributes);
        audit_event->attributes = NULL;
    }
    if (audit_event->audit_event_id) {
        free(audit_event->audit_event_id);
        audit_event->audit_event_id = NULL;
    }
    if (audit_event->created_at) {
        free(audit_event->created_at);
        audit_event->created_at = NULL;
    }
    if (audit_event->environment_id) {
        free(audit_event->environment_id);
        audit_event->environment_id = NULL;
    }
    if (audit_event->project_id) {
        free(audit_event->project_id);
        audit_event->project_id = NULL;
    }
    if (audit_event->reason) {
        free(audit_event->reason);
        audit_event->reason = NULL;
    }
    if (audit_event->resource_id) {
        free(audit_event->resource_id);
        audit_event->resource_id = NULL;
    }
    if (audit_event->resource_type) {
        free(audit_event->resource_type);
        audit_event->resource_type = NULL;
    }
    if (audit_event->tenant_id) {
        free(audit_event->tenant_id);
        audit_event->tenant_id = NULL;
    }
    free(audit_event);
}

cJSON *audit_event_convertToJSON(audit_event_t *audit_event) {
    cJSON *item = cJSON_CreateObject();

    // audit_event->action
    if (beater_api_audit_action__NULL == audit_event->action) {
        goto fail;
    }
    cJSON *action_local_JSON = audit_action_convertToJSON(audit_event->action);
    if(action_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "action", action_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // audit_event->actor_api_key_id
    if(audit_event->actor_api_key_id) {
    if(cJSON_AddStringToObject(item, "actor_api_key_id", audit_event->actor_api_key_id) == NULL) {
    goto fail; //String
    }
    }


    // audit_event->attributes
    if (!audit_event->attributes) {
        goto fail;
    }
    cJSON *attributes_local_JSON = _convertToJSON(audit_event->attributes);
    if(attributes_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "attributes", attributes_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // audit_event->audit_event_id
    if (!audit_event->audit_event_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "audit_event_id", audit_event->audit_event_id) == NULL) {
    goto fail; //String
    }


    // audit_event->created_at
    if (!audit_event->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", audit_event->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // audit_event->environment_id
    if(audit_event->environment_id) {
    if(cJSON_AddStringToObject(item, "environment_id", audit_event->environment_id) == NULL) {
    goto fail; //String
    }
    }


    // audit_event->outcome
    if (beater_api_audit_outcome__NULL == audit_event->outcome) {
        goto fail;
    }
    cJSON *outcome_local_JSON = audit_outcome_convertToJSON(audit_event->outcome);
    if(outcome_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "outcome", outcome_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // audit_event->project_id
    if (!audit_event->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", audit_event->project_id) == NULL) {
    goto fail; //String
    }


    // audit_event->reason
    if(audit_event->reason) {
    if(cJSON_AddStringToObject(item, "reason", audit_event->reason) == NULL) {
    goto fail; //String
    }
    }


    // audit_event->resource_id
    if (!audit_event->resource_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "resource_id", audit_event->resource_id) == NULL) {
    goto fail; //String
    }


    // audit_event->resource_type
    if (!audit_event->resource_type) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "resource_type", audit_event->resource_type) == NULL) {
    goto fail; //String
    }


    // audit_event->tenant_id
    if (!audit_event->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", audit_event->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

audit_event_t *audit_event_parseFromJSON(cJSON *audit_eventJSON){

    audit_event_t *audit_event_local_var = NULL;

    // define the local variable for audit_event->action
    beater_api_audit_action__e action_local_nonprim = 0;

    // define the local variable for audit_event->attributes
    _t *attributes_local_nonprim = NULL;

    // define the local variable for audit_event->outcome
    beater_api_audit_outcome__e outcome_local_nonprim = 0;

    // audit_event->action
    cJSON *action = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "action");
    if (cJSON_IsNull(action)) {
        action = NULL;
    }
    if (!action) {
        goto end;
    }

    
    action_local_nonprim = audit_action_parseFromJSON(action); //custom

    // audit_event->actor_api_key_id
    cJSON *actor_api_key_id = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "actor_api_key_id");
    if (cJSON_IsNull(actor_api_key_id)) {
        actor_api_key_id = NULL;
    }
    if (actor_api_key_id) { 
    if(!cJSON_IsString(actor_api_key_id) && !cJSON_IsNull(actor_api_key_id))
    {
    goto end; //String
    }
    }

    // audit_event->attributes
    cJSON *attributes = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "attributes");
    if (cJSON_IsNull(attributes)) {
        attributes = NULL;
    }
    if (!attributes) {
        goto end;
    }

    
    attributes_local_nonprim = _parseFromJSON(attributes); //custom

    // audit_event->audit_event_id
    cJSON *audit_event_id = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "audit_event_id");
    if (cJSON_IsNull(audit_event_id)) {
        audit_event_id = NULL;
    }
    if (!audit_event_id) {
        goto end;
    }

    
    if(!cJSON_IsString(audit_event_id))
    {
    goto end; //String
    }

    // audit_event->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "created_at");
    if (cJSON_IsNull(created_at)) {
        created_at = NULL;
    }
    if (!created_at) {
        goto end;
    }

    
    if(!cJSON_IsString(created_at) && !cJSON_IsNull(created_at))
    {
    goto end; //DateTime
    }

    // audit_event->environment_id
    cJSON *environment_id = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "environment_id");
    if (cJSON_IsNull(environment_id)) {
        environment_id = NULL;
    }
    if (environment_id) { 
    if(!cJSON_IsString(environment_id) && !cJSON_IsNull(environment_id))
    {
    goto end; //String
    }
    }

    // audit_event->outcome
    cJSON *outcome = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "outcome");
    if (cJSON_IsNull(outcome)) {
        outcome = NULL;
    }
    if (!outcome) {
        goto end;
    }

    
    outcome_local_nonprim = audit_outcome_parseFromJSON(outcome); //custom

    // audit_event->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "project_id");
    if (cJSON_IsNull(project_id)) {
        project_id = NULL;
    }
    if (!project_id) {
        goto end;
    }

    
    if(!cJSON_IsString(project_id))
    {
    goto end; //String
    }

    // audit_event->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "reason");
    if (cJSON_IsNull(reason)) {
        reason = NULL;
    }
    if (reason) { 
    if(!cJSON_IsString(reason) && !cJSON_IsNull(reason))
    {
    goto end; //String
    }
    }

    // audit_event->resource_id
    cJSON *resource_id = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "resource_id");
    if (cJSON_IsNull(resource_id)) {
        resource_id = NULL;
    }
    if (!resource_id) {
        goto end;
    }

    
    if(!cJSON_IsString(resource_id))
    {
    goto end; //String
    }

    // audit_event->resource_type
    cJSON *resource_type = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "resource_type");
    if (cJSON_IsNull(resource_type)) {
        resource_type = NULL;
    }
    if (!resource_type) {
        goto end;
    }

    
    if(!cJSON_IsString(resource_type))
    {
    goto end; //String
    }

    // audit_event->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(audit_eventJSON, "tenant_id");
    if (cJSON_IsNull(tenant_id)) {
        tenant_id = NULL;
    }
    if (!tenant_id) {
        goto end;
    }

    
    if(!cJSON_IsString(tenant_id))
    {
    goto end; //String
    }


    audit_event_local_var = audit_event_create_internal (
        action_local_nonprim,
        actor_api_key_id && !cJSON_IsNull(actor_api_key_id) ? strdup(actor_api_key_id->valuestring) : NULL,
        attributes_local_nonprim,
        strdup(audit_event_id->valuestring),
        strdup(created_at->valuestring),
        environment_id && !cJSON_IsNull(environment_id) ? strdup(environment_id->valuestring) : NULL,
        outcome_local_nonprim,
        strdup(project_id->valuestring),
        reason && !cJSON_IsNull(reason) ? strdup(reason->valuestring) : NULL,
        strdup(resource_id->valuestring),
        strdup(resource_type->valuestring),
        strdup(tenant_id->valuestring)
        );

    return audit_event_local_var;
end:
    if (action_local_nonprim) {
        action_local_nonprim = 0;
    }
    if (attributes_local_nonprim) {
        _free(attributes_local_nonprim);
        attributes_local_nonprim = NULL;
    }
    if (outcome_local_nonprim) {
        outcome_local_nonprim = 0;
    }
    return NULL;

}
