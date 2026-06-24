#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_definition.h"



static gate_definition_t *gate_definition_create_internal(
    char *created_at,
    char *dataset_id,
    char *evaluator_version_id,
    char *gate_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    char *name,
    char *project_id,
    char *tenant_id
    ) {
    gate_definition_t *gate_definition_local_var = malloc(sizeof(gate_definition_t));
    if (!gate_definition_local_var) {
        return NULL;
    }
    gate_definition_local_var->created_at = created_at;
    gate_definition_local_var->dataset_id = dataset_id;
    gate_definition_local_var->evaluator_version_id = evaluator_version_id;
    gate_definition_local_var->gate_id = gate_id;
    gate_definition_local_var->inconclusive_policy = inconclusive_policy;
    gate_definition_local_var->name = name;
    gate_definition_local_var->project_id = project_id;
    gate_definition_local_var->tenant_id = tenant_id;

    gate_definition_local_var->_library_owned = 1;
    return gate_definition_local_var;
}

__attribute__((deprecated)) gate_definition_t *gate_definition_create(
    char *created_at,
    char *dataset_id,
    char *evaluator_version_id,
    char *gate_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    char *name,
    char *project_id,
    char *tenant_id
    ) {
    return gate_definition_create_internal (
        created_at,
        dataset_id,
        evaluator_version_id,
        gate_id,
        inconclusive_policy,
        name,
        project_id,
        tenant_id
        );
}

void gate_definition_free(gate_definition_t *gate_definition) {
    if(NULL == gate_definition){
        return ;
    }
    if(gate_definition->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_definition_free");
        return ;
    }
    listEntry_t *listEntry;
    if (gate_definition->created_at) {
        free(gate_definition->created_at);
        gate_definition->created_at = NULL;
    }
    if (gate_definition->dataset_id) {
        free(gate_definition->dataset_id);
        gate_definition->dataset_id = NULL;
    }
    if (gate_definition->evaluator_version_id) {
        free(gate_definition->evaluator_version_id);
        gate_definition->evaluator_version_id = NULL;
    }
    if (gate_definition->gate_id) {
        free(gate_definition->gate_id);
        gate_definition->gate_id = NULL;
    }
    if (gate_definition->name) {
        free(gate_definition->name);
        gate_definition->name = NULL;
    }
    if (gate_definition->project_id) {
        free(gate_definition->project_id);
        gate_definition->project_id = NULL;
    }
    if (gate_definition->tenant_id) {
        free(gate_definition->tenant_id);
        gate_definition->tenant_id = NULL;
    }
    free(gate_definition);
}

cJSON *gate_definition_convertToJSON(gate_definition_t *gate_definition) {
    cJSON *item = cJSON_CreateObject();

    // gate_definition->created_at
    if (!gate_definition->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", gate_definition->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // gate_definition->dataset_id
    if(gate_definition->dataset_id) {
    if(cJSON_AddStringToObject(item, "dataset_id", gate_definition->dataset_id) == NULL) {
    goto fail; //String
    }
    }


    // gate_definition->evaluator_version_id
    if(gate_definition->evaluator_version_id) {
    if(cJSON_AddStringToObject(item, "evaluator_version_id", gate_definition->evaluator_version_id) == NULL) {
    goto fail; //String
    }
    }


    // gate_definition->gate_id
    if (!gate_definition->gate_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "gate_id", gate_definition->gate_id) == NULL) {
    goto fail; //String
    }


    // gate_definition->inconclusive_policy
    if(gate_definition->inconclusive_policy != beater_api_inconclusive_policy__NULL) {
    cJSON *inconclusive_policy_local_JSON = inconclusive_policy_convertToJSON(gate_definition->inconclusive_policy);
    if(inconclusive_policy_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "inconclusive_policy", inconclusive_policy_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // gate_definition->name
    if (!gate_definition->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", gate_definition->name) == NULL) {
    goto fail; //String
    }


    // gate_definition->project_id
    if (!gate_definition->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", gate_definition->project_id) == NULL) {
    goto fail; //String
    }


    // gate_definition->tenant_id
    if (!gate_definition->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", gate_definition->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

gate_definition_t *gate_definition_parseFromJSON(cJSON *gate_definitionJSON){

    gate_definition_t *gate_definition_local_var = NULL;

    // define the local variable for gate_definition->inconclusive_policy
    beater_api_inconclusive_policy__e inconclusive_policy_local_nonprim = 0;

    // gate_definition->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "created_at");
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

    // gate_definition->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "dataset_id");
    if (cJSON_IsNull(dataset_id)) {
        dataset_id = NULL;
    }
    if (dataset_id) { 
    if(!cJSON_IsString(dataset_id) && !cJSON_IsNull(dataset_id))
    {
    goto end; //String
    }
    }

    // gate_definition->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "evaluator_version_id");
    if (cJSON_IsNull(evaluator_version_id)) {
        evaluator_version_id = NULL;
    }
    if (evaluator_version_id) { 
    if(!cJSON_IsString(evaluator_version_id) && !cJSON_IsNull(evaluator_version_id))
    {
    goto end; //String
    }
    }

    // gate_definition->gate_id
    cJSON *gate_id = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "gate_id");
    if (cJSON_IsNull(gate_id)) {
        gate_id = NULL;
    }
    if (!gate_id) {
        goto end;
    }

    
    if(!cJSON_IsString(gate_id))
    {
    goto end; //String
    }

    // gate_definition->inconclusive_policy
    cJSON *inconclusive_policy = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "inconclusive_policy");
    if (cJSON_IsNull(inconclusive_policy)) {
        inconclusive_policy = NULL;
    }
    if (inconclusive_policy) { 
    inconclusive_policy_local_nonprim = inconclusive_policy_parseFromJSON(inconclusive_policy); //custom
    }

    // gate_definition->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "name");
    if (cJSON_IsNull(name)) {
        name = NULL;
    }
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }

    // gate_definition->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "project_id");
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

    // gate_definition->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(gate_definitionJSON, "tenant_id");
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


    gate_definition_local_var = gate_definition_create_internal (
        strdup(created_at->valuestring),
        dataset_id && !cJSON_IsNull(dataset_id) ? strdup(dataset_id->valuestring) : NULL,
        evaluator_version_id && !cJSON_IsNull(evaluator_version_id) ? strdup(evaluator_version_id->valuestring) : NULL,
        strdup(gate_id->valuestring),
        inconclusive_policy ? inconclusive_policy_local_nonprim : 0,
        strdup(name->valuestring),
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring)
        );

    return gate_definition_local_var;
end:
    if (inconclusive_policy_local_nonprim) {
        inconclusive_policy_local_nonprim = 0;
    }
    return NULL;

}
