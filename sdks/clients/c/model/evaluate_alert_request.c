#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluate_alert_request.h"



static evaluate_alert_request_t *evaluate_alert_request_create_internal(
    alert_input_t *input,
    alert_policy_t *policy
    ) {
    evaluate_alert_request_t *evaluate_alert_request_local_var = malloc(sizeof(evaluate_alert_request_t));
    if (!evaluate_alert_request_local_var) {
        return NULL;
    }
    evaluate_alert_request_local_var->input = input;
    evaluate_alert_request_local_var->policy = policy;

    evaluate_alert_request_local_var->_library_owned = 1;
    return evaluate_alert_request_local_var;
}

__attribute__((deprecated)) evaluate_alert_request_t *evaluate_alert_request_create(
    alert_input_t *input,
    alert_policy_t *policy
    ) {
    return evaluate_alert_request_create_internal (
        input,
        policy
        );
}

void evaluate_alert_request_free(evaluate_alert_request_t *evaluate_alert_request) {
    if(NULL == evaluate_alert_request){
        return ;
    }
    if(evaluate_alert_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "evaluate_alert_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (evaluate_alert_request->input) {
        alert_input_free(evaluate_alert_request->input);
        evaluate_alert_request->input = NULL;
    }
    if (evaluate_alert_request->policy) {
        alert_policy_free(evaluate_alert_request->policy);
        evaluate_alert_request->policy = NULL;
    }
    free(evaluate_alert_request);
}

cJSON *evaluate_alert_request_convertToJSON(evaluate_alert_request_t *evaluate_alert_request) {
    cJSON *item = cJSON_CreateObject();

    // evaluate_alert_request->input
    if (!evaluate_alert_request->input) {
        goto fail;
    }
    cJSON *input_local_JSON = alert_input_convertToJSON(evaluate_alert_request->input);
    if(input_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "input", input_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // evaluate_alert_request->policy
    if (!evaluate_alert_request->policy) {
        goto fail;
    }
    cJSON *policy_local_JSON = alert_policy_convertToJSON(evaluate_alert_request->policy);
    if(policy_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "policy", policy_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

evaluate_alert_request_t *evaluate_alert_request_parseFromJSON(cJSON *evaluate_alert_requestJSON){

    evaluate_alert_request_t *evaluate_alert_request_local_var = NULL;

    // define the local variable for evaluate_alert_request->input
    alert_input_t *input_local_nonprim = NULL;

    // define the local variable for evaluate_alert_request->policy
    alert_policy_t *policy_local_nonprim = NULL;

    // evaluate_alert_request->input
    cJSON *input = cJSON_GetObjectItemCaseSensitive(evaluate_alert_requestJSON, "input");
    if (cJSON_IsNull(input)) {
        input = NULL;
    }
    if (!input) {
        goto end;
    }

    
    input_local_nonprim = alert_input_parseFromJSON(input); //nonprimitive

    // evaluate_alert_request->policy
    cJSON *policy = cJSON_GetObjectItemCaseSensitive(evaluate_alert_requestJSON, "policy");
    if (cJSON_IsNull(policy)) {
        policy = NULL;
    }
    if (!policy) {
        goto end;
    }

    
    policy_local_nonprim = alert_policy_parseFromJSON(policy); //nonprimitive


    evaluate_alert_request_local_var = evaluate_alert_request_create_internal (
        input_local_nonprim,
        policy_local_nonprim
        );

    return evaluate_alert_request_local_var;
end:
    if (input_local_nonprim) {
        alert_input_free(input_local_nonprim);
        input_local_nonprim = NULL;
    }
    if (policy_local_nonprim) {
        alert_policy_free(policy_local_nonprim);
        policy_local_nonprim = NULL;
    }
    return NULL;

}
