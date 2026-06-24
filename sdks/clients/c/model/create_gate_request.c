#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_gate_request.h"



static create_gate_request_t *create_gate_request_create_internal(
    char *dataset_id,
    char *evaluator_version_id,
    char *gate_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    char *name
    ) {
    create_gate_request_t *create_gate_request_local_var = malloc(sizeof(create_gate_request_t));
    if (!create_gate_request_local_var) {
        return NULL;
    }
    create_gate_request_local_var->dataset_id = dataset_id;
    create_gate_request_local_var->evaluator_version_id = evaluator_version_id;
    create_gate_request_local_var->gate_id = gate_id;
    create_gate_request_local_var->inconclusive_policy = inconclusive_policy;
    create_gate_request_local_var->name = name;

    create_gate_request_local_var->_library_owned = 1;
    return create_gate_request_local_var;
}

__attribute__((deprecated)) create_gate_request_t *create_gate_request_create(
    char *dataset_id,
    char *evaluator_version_id,
    char *gate_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    char *name
    ) {
    return create_gate_request_create_internal (
        dataset_id,
        evaluator_version_id,
        gate_id,
        inconclusive_policy,
        name
        );
}

void create_gate_request_free(create_gate_request_t *create_gate_request) {
    if(NULL == create_gate_request){
        return ;
    }
    if(create_gate_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "create_gate_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (create_gate_request->dataset_id) {
        free(create_gate_request->dataset_id);
        create_gate_request->dataset_id = NULL;
    }
    if (create_gate_request->evaluator_version_id) {
        free(create_gate_request->evaluator_version_id);
        create_gate_request->evaluator_version_id = NULL;
    }
    if (create_gate_request->gate_id) {
        free(create_gate_request->gate_id);
        create_gate_request->gate_id = NULL;
    }
    if (create_gate_request->name) {
        free(create_gate_request->name);
        create_gate_request->name = NULL;
    }
    free(create_gate_request);
}

cJSON *create_gate_request_convertToJSON(create_gate_request_t *create_gate_request) {
    cJSON *item = cJSON_CreateObject();

    // create_gate_request->dataset_id
    if(create_gate_request->dataset_id) {
    if(cJSON_AddStringToObject(item, "dataset_id", create_gate_request->dataset_id) == NULL) {
    goto fail; //String
    }
    }


    // create_gate_request->evaluator_version_id
    if(create_gate_request->evaluator_version_id) {
    if(cJSON_AddStringToObject(item, "evaluator_version_id", create_gate_request->evaluator_version_id) == NULL) {
    goto fail; //String
    }
    }


    // create_gate_request->gate_id
    if (!create_gate_request->gate_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "gate_id", create_gate_request->gate_id) == NULL) {
    goto fail; //String
    }


    // create_gate_request->inconclusive_policy
    if(create_gate_request->inconclusive_policy != beater_api_inconclusive_policy__NULL) {
    cJSON *inconclusive_policy_local_JSON = inconclusive_policy_convertToJSON(create_gate_request->inconclusive_policy);
    if(inconclusive_policy_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "inconclusive_policy", inconclusive_policy_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // create_gate_request->name
    if (!create_gate_request->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", create_gate_request->name) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

create_gate_request_t *create_gate_request_parseFromJSON(cJSON *create_gate_requestJSON){

    create_gate_request_t *create_gate_request_local_var = NULL;

    // define the local variable for create_gate_request->inconclusive_policy
    beater_api_inconclusive_policy__e inconclusive_policy_local_nonprim = 0;

    // create_gate_request->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(create_gate_requestJSON, "dataset_id");
    if (cJSON_IsNull(dataset_id)) {
        dataset_id = NULL;
    }
    if (dataset_id) { 
    if(!cJSON_IsString(dataset_id) && !cJSON_IsNull(dataset_id))
    {
    goto end; //String
    }
    }

    // create_gate_request->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(create_gate_requestJSON, "evaluator_version_id");
    if (cJSON_IsNull(evaluator_version_id)) {
        evaluator_version_id = NULL;
    }
    if (evaluator_version_id) { 
    if(!cJSON_IsString(evaluator_version_id) && !cJSON_IsNull(evaluator_version_id))
    {
    goto end; //String
    }
    }

    // create_gate_request->gate_id
    cJSON *gate_id = cJSON_GetObjectItemCaseSensitive(create_gate_requestJSON, "gate_id");
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

    // create_gate_request->inconclusive_policy
    cJSON *inconclusive_policy = cJSON_GetObjectItemCaseSensitive(create_gate_requestJSON, "inconclusive_policy");
    if (cJSON_IsNull(inconclusive_policy)) {
        inconclusive_policy = NULL;
    }
    if (inconclusive_policy) { 
    inconclusive_policy_local_nonprim = inconclusive_policy_parseFromJSON(inconclusive_policy); //custom
    }

    // create_gate_request->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(create_gate_requestJSON, "name");
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


    create_gate_request_local_var = create_gate_request_create_internal (
        dataset_id && !cJSON_IsNull(dataset_id) ? strdup(dataset_id->valuestring) : NULL,
        evaluator_version_id && !cJSON_IsNull(evaluator_version_id) ? strdup(evaluator_version_id->valuestring) : NULL,
        strdup(gate_id->valuestring),
        inconclusive_policy ? inconclusive_policy_local_nonprim : 0,
        strdup(name->valuestring)
        );

    return create_gate_request_local_var;
end:
    if (inconclusive_policy_local_nonprim) {
        inconclusive_policy_local_nonprim = 0;
    }
    return NULL;

}
