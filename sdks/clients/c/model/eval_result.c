#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "eval_result.h"



static eval_result_t *eval_result_create_internal(
    money_t *cost,
    char *created_at,
    char *eval_result_id,
    any_type_t *evidence,
    char *label,
    char *non_reproducible_reason,
    char *project_id,
    eval_reproducibility_t *reproducibility,
    double score,
    char *span_id,
    char *tenant_id,
    token_counts_t *tokens,
    char *trace_id
    ) {
    eval_result_t *eval_result_local_var = malloc(sizeof(eval_result_t));
    if (!eval_result_local_var) {
        return NULL;
    }
    eval_result_local_var->cost = cost;
    eval_result_local_var->created_at = created_at;
    eval_result_local_var->eval_result_id = eval_result_id;
    eval_result_local_var->evidence = evidence;
    eval_result_local_var->label = label;
    eval_result_local_var->non_reproducible_reason = non_reproducible_reason;
    eval_result_local_var->project_id = project_id;
    eval_result_local_var->reproducibility = reproducibility;
    eval_result_local_var->score = score;
    eval_result_local_var->span_id = span_id;
    eval_result_local_var->tenant_id = tenant_id;
    eval_result_local_var->tokens = tokens;
    eval_result_local_var->trace_id = trace_id;

    eval_result_local_var->_library_owned = 1;
    return eval_result_local_var;
}

__attribute__((deprecated)) eval_result_t *eval_result_create(
    money_t *cost,
    char *created_at,
    char *eval_result_id,
    any_type_t *evidence,
    char *label,
    char *non_reproducible_reason,
    char *project_id,
    eval_reproducibility_t *reproducibility,
    double score,
    char *span_id,
    char *tenant_id,
    token_counts_t *tokens,
    char *trace_id
    ) {
    return eval_result_create_internal (
        cost,
        created_at,
        eval_result_id,
        evidence,
        label,
        non_reproducible_reason,
        project_id,
        reproducibility,
        score,
        span_id,
        tenant_id,
        tokens,
        trace_id
        );
}

void eval_result_free(eval_result_t *eval_result) {
    if(NULL == eval_result){
        return ;
    }
    if(eval_result->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "eval_result_free");
        return ;
    }
    listEntry_t *listEntry;
    if (eval_result->cost) {
        money_free(eval_result->cost);
        eval_result->cost = NULL;
    }
    if (eval_result->created_at) {
        free(eval_result->created_at);
        eval_result->created_at = NULL;
    }
    if (eval_result->eval_result_id) {
        free(eval_result->eval_result_id);
        eval_result->eval_result_id = NULL;
    }
    if (eval_result->evidence) {
        _free(eval_result->evidence);
        eval_result->evidence = NULL;
    }
    if (eval_result->label) {
        free(eval_result->label);
        eval_result->label = NULL;
    }
    if (eval_result->non_reproducible_reason) {
        free(eval_result->non_reproducible_reason);
        eval_result->non_reproducible_reason = NULL;
    }
    if (eval_result->project_id) {
        free(eval_result->project_id);
        eval_result->project_id = NULL;
    }
    if (eval_result->reproducibility) {
        eval_reproducibility_free(eval_result->reproducibility);
        eval_result->reproducibility = NULL;
    }
    if (eval_result->span_id) {
        free(eval_result->span_id);
        eval_result->span_id = NULL;
    }
    if (eval_result->tenant_id) {
        free(eval_result->tenant_id);
        eval_result->tenant_id = NULL;
    }
    if (eval_result->tokens) {
        token_counts_free(eval_result->tokens);
        eval_result->tokens = NULL;
    }
    if (eval_result->trace_id) {
        free(eval_result->trace_id);
        eval_result->trace_id = NULL;
    }
    free(eval_result);
}

cJSON *eval_result_convertToJSON(eval_result_t *eval_result) {
    cJSON *item = cJSON_CreateObject();

    // eval_result->cost
    if(eval_result->cost) {
    cJSON *cost_local_JSON = money_convertToJSON(eval_result->cost);
    if(cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "cost", cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // eval_result->created_at
    if (!eval_result->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", eval_result->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // eval_result->eval_result_id
    if (!eval_result->eval_result_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "eval_result_id", eval_result->eval_result_id) == NULL) {
    goto fail; //String
    }


    // eval_result->evidence
    if (!eval_result->evidence) {
        goto fail;
    }
    cJSON *evidence_local_JSON = _convertToJSON(eval_result->evidence);
    if(evidence_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "evidence", evidence_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // eval_result->label
    if(eval_result->label) {
    if(cJSON_AddStringToObject(item, "label", eval_result->label) == NULL) {
    goto fail; //String
    }
    }


    // eval_result->non_reproducible_reason
    if(eval_result->non_reproducible_reason) {
    if(cJSON_AddStringToObject(item, "non_reproducible_reason", eval_result->non_reproducible_reason) == NULL) {
    goto fail; //String
    }
    }


    // eval_result->project_id
    if (!eval_result->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", eval_result->project_id) == NULL) {
    goto fail; //String
    }


    // eval_result->reproducibility
    if (!eval_result->reproducibility) {
        goto fail;
    }
    cJSON *reproducibility_local_JSON = eval_reproducibility_convertToJSON(eval_result->reproducibility);
    if(reproducibility_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "reproducibility", reproducibility_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // eval_result->score
    if (!eval_result->score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "score", eval_result->score) == NULL) {
    goto fail; //Numeric
    }


    // eval_result->span_id
    if(eval_result->span_id) {
    if(cJSON_AddStringToObject(item, "span_id", eval_result->span_id) == NULL) {
    goto fail; //String
    }
    }


    // eval_result->tenant_id
    if (!eval_result->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", eval_result->tenant_id) == NULL) {
    goto fail; //String
    }


    // eval_result->tokens
    if(eval_result->tokens) {
    cJSON *tokens_local_JSON = token_counts_convertToJSON(eval_result->tokens);
    if(tokens_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "tokens", tokens_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // eval_result->trace_id
    if (!eval_result->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", eval_result->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

eval_result_t *eval_result_parseFromJSON(cJSON *eval_resultJSON){

    eval_result_t *eval_result_local_var = NULL;

    // define the local variable for eval_result->cost
    money_t *cost_local_nonprim = NULL;

    // define the local variable for eval_result->evidence
    _t *evidence_local_nonprim = NULL;

    // define the local variable for eval_result->reproducibility
    eval_reproducibility_t *reproducibility_local_nonprim = NULL;

    // define the local variable for eval_result->tokens
    token_counts_t *tokens_local_nonprim = NULL;

    // eval_result->cost
    cJSON *cost = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "cost");
    if (cJSON_IsNull(cost)) {
        cost = NULL;
    }
    if (cost) { 
    cost_local_nonprim = money_parseFromJSON(cost); //nonprimitive
    }

    // eval_result->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "created_at");
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

    // eval_result->eval_result_id
    cJSON *eval_result_id = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "eval_result_id");
    if (cJSON_IsNull(eval_result_id)) {
        eval_result_id = NULL;
    }
    if (!eval_result_id) {
        goto end;
    }

    
    if(!cJSON_IsString(eval_result_id))
    {
    goto end; //String
    }

    // eval_result->evidence
    cJSON *evidence = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "evidence");
    if (cJSON_IsNull(evidence)) {
        evidence = NULL;
    }
    if (!evidence) {
        goto end;
    }

    
    evidence_local_nonprim = _parseFromJSON(evidence); //custom

    // eval_result->label
    cJSON *label = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "label");
    if (cJSON_IsNull(label)) {
        label = NULL;
    }
    if (label) { 
    if(!cJSON_IsString(label) && !cJSON_IsNull(label))
    {
    goto end; //String
    }
    }

    // eval_result->non_reproducible_reason
    cJSON *non_reproducible_reason = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "non_reproducible_reason");
    if (cJSON_IsNull(non_reproducible_reason)) {
        non_reproducible_reason = NULL;
    }
    if (non_reproducible_reason) { 
    if(!cJSON_IsString(non_reproducible_reason) && !cJSON_IsNull(non_reproducible_reason))
    {
    goto end; //String
    }
    }

    // eval_result->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "project_id");
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

    // eval_result->reproducibility
    cJSON *reproducibility = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "reproducibility");
    if (cJSON_IsNull(reproducibility)) {
        reproducibility = NULL;
    }
    if (!reproducibility) {
        goto end;
    }

    
    reproducibility_local_nonprim = eval_reproducibility_parseFromJSON(reproducibility); //nonprimitive

    // eval_result->score
    cJSON *score = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "score");
    if (cJSON_IsNull(score)) {
        score = NULL;
    }
    if (!score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(score))
    {
    goto end; //Numeric
    }

    // eval_result->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "span_id");
    if (cJSON_IsNull(span_id)) {
        span_id = NULL;
    }
    if (span_id) { 
    if(!cJSON_IsString(span_id) && !cJSON_IsNull(span_id))
    {
    goto end; //String
    }
    }

    // eval_result->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "tenant_id");
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

    // eval_result->tokens
    cJSON *tokens = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "tokens");
    if (cJSON_IsNull(tokens)) {
        tokens = NULL;
    }
    if (tokens) { 
    tokens_local_nonprim = token_counts_parseFromJSON(tokens); //nonprimitive
    }

    // eval_result->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(eval_resultJSON, "trace_id");
    if (cJSON_IsNull(trace_id)) {
        trace_id = NULL;
    }
    if (!trace_id) {
        goto end;
    }

    
    if(!cJSON_IsString(trace_id))
    {
    goto end; //String
    }


    eval_result_local_var = eval_result_create_internal (
        cost ? cost_local_nonprim : NULL,
        strdup(created_at->valuestring),
        strdup(eval_result_id->valuestring),
        evidence_local_nonprim,
        label && !cJSON_IsNull(label) ? strdup(label->valuestring) : NULL,
        non_reproducible_reason && !cJSON_IsNull(non_reproducible_reason) ? strdup(non_reproducible_reason->valuestring) : NULL,
        strdup(project_id->valuestring),
        reproducibility_local_nonprim,
        score->valuedouble,
        span_id && !cJSON_IsNull(span_id) ? strdup(span_id->valuestring) : NULL,
        strdup(tenant_id->valuestring),
        tokens ? tokens_local_nonprim : NULL,
        strdup(trace_id->valuestring)
        );

    return eval_result_local_var;
end:
    if (cost_local_nonprim) {
        money_free(cost_local_nonprim);
        cost_local_nonprim = NULL;
    }
    if (evidence_local_nonprim) {
        _free(evidence_local_nonprim);
        evidence_local_nonprim = NULL;
    }
    if (reproducibility_local_nonprim) {
        eval_reproducibility_free(reproducibility_local_nonprim);
        reproducibility_local_nonprim = NULL;
    }
    if (tokens_local_nonprim) {
        token_counts_free(tokens_local_nonprim);
        tokens_local_nonprim = NULL;
    }
    return NULL;

}
