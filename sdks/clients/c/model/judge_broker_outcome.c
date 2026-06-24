#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "judge_broker_outcome.h"



static judge_broker_outcome_t *judge_broker_outcome_create_internal(
    judge_audit_record_t *audit,
    money_t *remaining_budget,
    score_result_t *result
    ) {
    judge_broker_outcome_t *judge_broker_outcome_local_var = malloc(sizeof(judge_broker_outcome_t));
    if (!judge_broker_outcome_local_var) {
        return NULL;
    }
    judge_broker_outcome_local_var->audit = audit;
    judge_broker_outcome_local_var->remaining_budget = remaining_budget;
    judge_broker_outcome_local_var->result = result;

    judge_broker_outcome_local_var->_library_owned = 1;
    return judge_broker_outcome_local_var;
}

__attribute__((deprecated)) judge_broker_outcome_t *judge_broker_outcome_create(
    judge_audit_record_t *audit,
    money_t *remaining_budget,
    score_result_t *result
    ) {
    return judge_broker_outcome_create_internal (
        audit,
        remaining_budget,
        result
        );
}

void judge_broker_outcome_free(judge_broker_outcome_t *judge_broker_outcome) {
    if(NULL == judge_broker_outcome){
        return ;
    }
    if(judge_broker_outcome->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "judge_broker_outcome_free");
        return ;
    }
    listEntry_t *listEntry;
    if (judge_broker_outcome->audit) {
        judge_audit_record_free(judge_broker_outcome->audit);
        judge_broker_outcome->audit = NULL;
    }
    if (judge_broker_outcome->remaining_budget) {
        money_free(judge_broker_outcome->remaining_budget);
        judge_broker_outcome->remaining_budget = NULL;
    }
    if (judge_broker_outcome->result) {
        score_result_free(judge_broker_outcome->result);
        judge_broker_outcome->result = NULL;
    }
    free(judge_broker_outcome);
}

cJSON *judge_broker_outcome_convertToJSON(judge_broker_outcome_t *judge_broker_outcome) {
    cJSON *item = cJSON_CreateObject();

    // judge_broker_outcome->audit
    if (!judge_broker_outcome->audit) {
        goto fail;
    }
    cJSON *audit_local_JSON = judge_audit_record_convertToJSON(judge_broker_outcome->audit);
    if(audit_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "audit", audit_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // judge_broker_outcome->remaining_budget
    if (!judge_broker_outcome->remaining_budget) {
        goto fail;
    }
    cJSON *remaining_budget_local_JSON = money_convertToJSON(judge_broker_outcome->remaining_budget);
    if(remaining_budget_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "remaining_budget", remaining_budget_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // judge_broker_outcome->result
    if (!judge_broker_outcome->result) {
        goto fail;
    }
    cJSON *result_local_JSON = score_result_convertToJSON(judge_broker_outcome->result);
    if(result_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "result", result_local_JSON);
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

judge_broker_outcome_t *judge_broker_outcome_parseFromJSON(cJSON *judge_broker_outcomeJSON){

    judge_broker_outcome_t *judge_broker_outcome_local_var = NULL;

    // define the local variable for judge_broker_outcome->audit
    judge_audit_record_t *audit_local_nonprim = NULL;

    // define the local variable for judge_broker_outcome->remaining_budget
    money_t *remaining_budget_local_nonprim = NULL;

    // define the local variable for judge_broker_outcome->result
    score_result_t *result_local_nonprim = NULL;

    // judge_broker_outcome->audit
    cJSON *audit = cJSON_GetObjectItemCaseSensitive(judge_broker_outcomeJSON, "audit");
    if (cJSON_IsNull(audit)) {
        audit = NULL;
    }
    if (!audit) {
        goto end;
    }

    
    audit_local_nonprim = judge_audit_record_parseFromJSON(audit); //nonprimitive

    // judge_broker_outcome->remaining_budget
    cJSON *remaining_budget = cJSON_GetObjectItemCaseSensitive(judge_broker_outcomeJSON, "remaining_budget");
    if (cJSON_IsNull(remaining_budget)) {
        remaining_budget = NULL;
    }
    if (!remaining_budget) {
        goto end;
    }

    
    remaining_budget_local_nonprim = money_parseFromJSON(remaining_budget); //nonprimitive

    // judge_broker_outcome->result
    cJSON *result = cJSON_GetObjectItemCaseSensitive(judge_broker_outcomeJSON, "result");
    if (cJSON_IsNull(result)) {
        result = NULL;
    }
    if (!result) {
        goto end;
    }

    
    result_local_nonprim = score_result_parseFromJSON(result); //nonprimitive


    judge_broker_outcome_local_var = judge_broker_outcome_create_internal (
        audit_local_nonprim,
        remaining_budget_local_nonprim,
        result_local_nonprim
        );

    return judge_broker_outcome_local_var;
end:
    if (audit_local_nonprim) {
        judge_audit_record_free(audit_local_nonprim);
        audit_local_nonprim = NULL;
    }
    if (remaining_budget_local_nonprim) {
        money_free(remaining_budget_local_nonprim);
        remaining_budget_local_nonprim = NULL;
    }
    if (result_local_nonprim) {
        score_result_free(result_local_nonprim);
        result_local_nonprim = NULL;
    }
    return NULL;

}
