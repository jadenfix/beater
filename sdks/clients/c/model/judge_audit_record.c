#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "judge_audit_record.h"



static judge_audit_record_t *judge_audit_record_create_internal(
    int cached,
    money_t *charged_cost,
    char *created_at,
    char *evaluator_id,
    char *judge_call_id,
    char *model,
    char *project_id,
    char *provider,
    money_t *provider_cost,
    char *provider_secret_id,
    char *request_hash,
    char *response_hash,
    double score,
    char *tenant_id
    ) {
    judge_audit_record_t *judge_audit_record_local_var = malloc(sizeof(judge_audit_record_t));
    if (!judge_audit_record_local_var) {
        return NULL;
    }
    judge_audit_record_local_var->cached = cached;
    judge_audit_record_local_var->charged_cost = charged_cost;
    judge_audit_record_local_var->created_at = created_at;
    judge_audit_record_local_var->evaluator_id = evaluator_id;
    judge_audit_record_local_var->judge_call_id = judge_call_id;
    judge_audit_record_local_var->model = model;
    judge_audit_record_local_var->project_id = project_id;
    judge_audit_record_local_var->provider = provider;
    judge_audit_record_local_var->provider_cost = provider_cost;
    judge_audit_record_local_var->provider_secret_id = provider_secret_id;
    judge_audit_record_local_var->request_hash = request_hash;
    judge_audit_record_local_var->response_hash = response_hash;
    judge_audit_record_local_var->score = score;
    judge_audit_record_local_var->tenant_id = tenant_id;

    judge_audit_record_local_var->_library_owned = 1;
    return judge_audit_record_local_var;
}

__attribute__((deprecated)) judge_audit_record_t *judge_audit_record_create(
    int cached,
    money_t *charged_cost,
    char *created_at,
    char *evaluator_id,
    char *judge_call_id,
    char *model,
    char *project_id,
    char *provider,
    money_t *provider_cost,
    char *provider_secret_id,
    char *request_hash,
    char *response_hash,
    double score,
    char *tenant_id
    ) {
    return judge_audit_record_create_internal (
        cached,
        charged_cost,
        created_at,
        evaluator_id,
        judge_call_id,
        model,
        project_id,
        provider,
        provider_cost,
        provider_secret_id,
        request_hash,
        response_hash,
        score,
        tenant_id
        );
}

void judge_audit_record_free(judge_audit_record_t *judge_audit_record) {
    if(NULL == judge_audit_record){
        return ;
    }
    if(judge_audit_record->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "judge_audit_record_free");
        return ;
    }
    listEntry_t *listEntry;
    if (judge_audit_record->charged_cost) {
        money_free(judge_audit_record->charged_cost);
        judge_audit_record->charged_cost = NULL;
    }
    if (judge_audit_record->created_at) {
        free(judge_audit_record->created_at);
        judge_audit_record->created_at = NULL;
    }
    if (judge_audit_record->evaluator_id) {
        free(judge_audit_record->evaluator_id);
        judge_audit_record->evaluator_id = NULL;
    }
    if (judge_audit_record->judge_call_id) {
        free(judge_audit_record->judge_call_id);
        judge_audit_record->judge_call_id = NULL;
    }
    if (judge_audit_record->model) {
        free(judge_audit_record->model);
        judge_audit_record->model = NULL;
    }
    if (judge_audit_record->project_id) {
        free(judge_audit_record->project_id);
        judge_audit_record->project_id = NULL;
    }
    if (judge_audit_record->provider) {
        free(judge_audit_record->provider);
        judge_audit_record->provider = NULL;
    }
    if (judge_audit_record->provider_cost) {
        money_free(judge_audit_record->provider_cost);
        judge_audit_record->provider_cost = NULL;
    }
    if (judge_audit_record->provider_secret_id) {
        free(judge_audit_record->provider_secret_id);
        judge_audit_record->provider_secret_id = NULL;
    }
    if (judge_audit_record->request_hash) {
        free(judge_audit_record->request_hash);
        judge_audit_record->request_hash = NULL;
    }
    if (judge_audit_record->response_hash) {
        free(judge_audit_record->response_hash);
        judge_audit_record->response_hash = NULL;
    }
    if (judge_audit_record->tenant_id) {
        free(judge_audit_record->tenant_id);
        judge_audit_record->tenant_id = NULL;
    }
    free(judge_audit_record);
}

cJSON *judge_audit_record_convertToJSON(judge_audit_record_t *judge_audit_record) {
    cJSON *item = cJSON_CreateObject();

    // judge_audit_record->cached
    if (!judge_audit_record->cached) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "cached", judge_audit_record->cached) == NULL) {
    goto fail; //Bool
    }


    // judge_audit_record->charged_cost
    if (!judge_audit_record->charged_cost) {
        goto fail;
    }
    cJSON *charged_cost_local_JSON = money_convertToJSON(judge_audit_record->charged_cost);
    if(charged_cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "charged_cost", charged_cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // judge_audit_record->created_at
    if (!judge_audit_record->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", judge_audit_record->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // judge_audit_record->evaluator_id
    if (!judge_audit_record->evaluator_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_id", judge_audit_record->evaluator_id) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->judge_call_id
    if (!judge_audit_record->judge_call_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "judge_call_id", judge_audit_record->judge_call_id) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->model
    if (!judge_audit_record->model) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "model", judge_audit_record->model) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->project_id
    if (!judge_audit_record->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", judge_audit_record->project_id) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->provider
    if (!judge_audit_record->provider) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "provider", judge_audit_record->provider) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->provider_cost
    if (!judge_audit_record->provider_cost) {
        goto fail;
    }
    cJSON *provider_cost_local_JSON = money_convertToJSON(judge_audit_record->provider_cost);
    if(provider_cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "provider_cost", provider_cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // judge_audit_record->provider_secret_id
    if (!judge_audit_record->provider_secret_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "provider_secret_id", judge_audit_record->provider_secret_id) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->request_hash
    if (!judge_audit_record->request_hash) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "request_hash", judge_audit_record->request_hash) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->response_hash
    if (!judge_audit_record->response_hash) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "response_hash", judge_audit_record->response_hash) == NULL) {
    goto fail; //String
    }


    // judge_audit_record->score
    if (!judge_audit_record->score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "score", judge_audit_record->score) == NULL) {
    goto fail; //Numeric
    }


    // judge_audit_record->tenant_id
    if (!judge_audit_record->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", judge_audit_record->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

judge_audit_record_t *judge_audit_record_parseFromJSON(cJSON *judge_audit_recordJSON){

    judge_audit_record_t *judge_audit_record_local_var = NULL;

    // define the local variable for judge_audit_record->charged_cost
    money_t *charged_cost_local_nonprim = NULL;

    // define the local variable for judge_audit_record->provider_cost
    money_t *provider_cost_local_nonprim = NULL;

    // judge_audit_record->cached
    cJSON *cached = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "cached");
    if (cJSON_IsNull(cached)) {
        cached = NULL;
    }
    if (!cached) {
        goto end;
    }

    
    if(!cJSON_IsBool(cached))
    {
    goto end; //Bool
    }

    // judge_audit_record->charged_cost
    cJSON *charged_cost = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "charged_cost");
    if (cJSON_IsNull(charged_cost)) {
        charged_cost = NULL;
    }
    if (!charged_cost) {
        goto end;
    }

    
    charged_cost_local_nonprim = money_parseFromJSON(charged_cost); //nonprimitive

    // judge_audit_record->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "created_at");
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

    // judge_audit_record->evaluator_id
    cJSON *evaluator_id = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "evaluator_id");
    if (cJSON_IsNull(evaluator_id)) {
        evaluator_id = NULL;
    }
    if (!evaluator_id) {
        goto end;
    }

    
    if(!cJSON_IsString(evaluator_id))
    {
    goto end; //String
    }

    // judge_audit_record->judge_call_id
    cJSON *judge_call_id = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "judge_call_id");
    if (cJSON_IsNull(judge_call_id)) {
        judge_call_id = NULL;
    }
    if (!judge_call_id) {
        goto end;
    }

    
    if(!cJSON_IsString(judge_call_id))
    {
    goto end; //String
    }

    // judge_audit_record->model
    cJSON *model = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "model");
    if (cJSON_IsNull(model)) {
        model = NULL;
    }
    if (!model) {
        goto end;
    }

    
    if(!cJSON_IsString(model))
    {
    goto end; //String
    }

    // judge_audit_record->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "project_id");
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

    // judge_audit_record->provider
    cJSON *provider = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "provider");
    if (cJSON_IsNull(provider)) {
        provider = NULL;
    }
    if (!provider) {
        goto end;
    }

    
    if(!cJSON_IsString(provider))
    {
    goto end; //String
    }

    // judge_audit_record->provider_cost
    cJSON *provider_cost = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "provider_cost");
    if (cJSON_IsNull(provider_cost)) {
        provider_cost = NULL;
    }
    if (!provider_cost) {
        goto end;
    }

    
    provider_cost_local_nonprim = money_parseFromJSON(provider_cost); //nonprimitive

    // judge_audit_record->provider_secret_id
    cJSON *provider_secret_id = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "provider_secret_id");
    if (cJSON_IsNull(provider_secret_id)) {
        provider_secret_id = NULL;
    }
    if (!provider_secret_id) {
        goto end;
    }

    
    if(!cJSON_IsString(provider_secret_id))
    {
    goto end; //String
    }

    // judge_audit_record->request_hash
    cJSON *request_hash = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "request_hash");
    if (cJSON_IsNull(request_hash)) {
        request_hash = NULL;
    }
    if (!request_hash) {
        goto end;
    }

    
    if(!cJSON_IsString(request_hash))
    {
    goto end; //String
    }

    // judge_audit_record->response_hash
    cJSON *response_hash = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "response_hash");
    if (cJSON_IsNull(response_hash)) {
        response_hash = NULL;
    }
    if (!response_hash) {
        goto end;
    }

    
    if(!cJSON_IsString(response_hash))
    {
    goto end; //String
    }

    // judge_audit_record->score
    cJSON *score = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "score");
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

    // judge_audit_record->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(judge_audit_recordJSON, "tenant_id");
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


    judge_audit_record_local_var = judge_audit_record_create_internal (
        cached->valueint,
        charged_cost_local_nonprim,
        strdup(created_at->valuestring),
        strdup(evaluator_id->valuestring),
        strdup(judge_call_id->valuestring),
        strdup(model->valuestring),
        strdup(project_id->valuestring),
        strdup(provider->valuestring),
        provider_cost_local_nonprim,
        strdup(provider_secret_id->valuestring),
        strdup(request_hash->valuestring),
        strdup(response_hash->valuestring),
        score->valuedouble,
        strdup(tenant_id->valuestring)
        );

    return judge_audit_record_local_var;
end:
    if (charged_cost_local_nonprim) {
        money_free(charged_cost_local_nonprim);
        charged_cost_local_nonprim = NULL;
    }
    if (provider_cost_local_nonprim) {
        money_free(provider_cost_local_nonprim);
        provider_cost_local_nonprim = NULL;
    }
    return NULL;

}
