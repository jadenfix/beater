#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "archived_span_row.h"



static archived_span_row_t *archived_span_row_create_internal(
    char *attributes_json,
    char *cost_amount_micros,
    char *cost_currency,
    char *end_time,
    char *environment_id,
    char *input_tokens,
    char *input_uri,
    char *kind,
    char *model_name,
    char *model_provider,
    char *name,
    char *output_tokens,
    char *output_uri,
    char *parent_span_id,
    char *project_id,
    char *raw_uri,
    char *reasoning_tokens,
    long seq,
    char *span_id,
    char *start_time,
    char *status,
    char *tenant_id,
    char *trace_id,
    char *unmapped_json
    ) {
    archived_span_row_t *archived_span_row_local_var = malloc(sizeof(archived_span_row_t));
    if (!archived_span_row_local_var) {
        return NULL;
    }
    archived_span_row_local_var->attributes_json = attributes_json;
    archived_span_row_local_var->cost_amount_micros = cost_amount_micros;
    archived_span_row_local_var->cost_currency = cost_currency;
    archived_span_row_local_var->end_time = end_time;
    archived_span_row_local_var->environment_id = environment_id;
    archived_span_row_local_var->input_tokens = input_tokens;
    archived_span_row_local_var->input_uri = input_uri;
    archived_span_row_local_var->kind = kind;
    archived_span_row_local_var->model_name = model_name;
    archived_span_row_local_var->model_provider = model_provider;
    archived_span_row_local_var->name = name;
    archived_span_row_local_var->output_tokens = output_tokens;
    archived_span_row_local_var->output_uri = output_uri;
    archived_span_row_local_var->parent_span_id = parent_span_id;
    archived_span_row_local_var->project_id = project_id;
    archived_span_row_local_var->raw_uri = raw_uri;
    archived_span_row_local_var->reasoning_tokens = reasoning_tokens;
    archived_span_row_local_var->seq = seq;
    archived_span_row_local_var->span_id = span_id;
    archived_span_row_local_var->start_time = start_time;
    archived_span_row_local_var->status = status;
    archived_span_row_local_var->tenant_id = tenant_id;
    archived_span_row_local_var->trace_id = trace_id;
    archived_span_row_local_var->unmapped_json = unmapped_json;

    archived_span_row_local_var->_library_owned = 1;
    return archived_span_row_local_var;
}

__attribute__((deprecated)) archived_span_row_t *archived_span_row_create(
    char *attributes_json,
    char *cost_amount_micros,
    char *cost_currency,
    char *end_time,
    char *environment_id,
    char *input_tokens,
    char *input_uri,
    char *kind,
    char *model_name,
    char *model_provider,
    char *name,
    char *output_tokens,
    char *output_uri,
    char *parent_span_id,
    char *project_id,
    char *raw_uri,
    char *reasoning_tokens,
    long seq,
    char *span_id,
    char *start_time,
    char *status,
    char *tenant_id,
    char *trace_id,
    char *unmapped_json
    ) {
    return archived_span_row_create_internal (
        attributes_json,
        cost_amount_micros,
        cost_currency,
        end_time,
        environment_id,
        input_tokens,
        input_uri,
        kind,
        model_name,
        model_provider,
        name,
        output_tokens,
        output_uri,
        parent_span_id,
        project_id,
        raw_uri,
        reasoning_tokens,
        seq,
        span_id,
        start_time,
        status,
        tenant_id,
        trace_id,
        unmapped_json
        );
}

void archived_span_row_free(archived_span_row_t *archived_span_row) {
    if(NULL == archived_span_row){
        return ;
    }
    if(archived_span_row->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "archived_span_row_free");
        return ;
    }
    listEntry_t *listEntry;
    if (archived_span_row->attributes_json) {
        free(archived_span_row->attributes_json);
        archived_span_row->attributes_json = NULL;
    }
    if (archived_span_row->cost_amount_micros) {
        free(archived_span_row->cost_amount_micros);
        archived_span_row->cost_amount_micros = NULL;
    }
    if (archived_span_row->cost_currency) {
        free(archived_span_row->cost_currency);
        archived_span_row->cost_currency = NULL;
    }
    if (archived_span_row->end_time) {
        free(archived_span_row->end_time);
        archived_span_row->end_time = NULL;
    }
    if (archived_span_row->environment_id) {
        free(archived_span_row->environment_id);
        archived_span_row->environment_id = NULL;
    }
    if (archived_span_row->input_tokens) {
        free(archived_span_row->input_tokens);
        archived_span_row->input_tokens = NULL;
    }
    if (archived_span_row->input_uri) {
        free(archived_span_row->input_uri);
        archived_span_row->input_uri = NULL;
    }
    if (archived_span_row->kind) {
        free(archived_span_row->kind);
        archived_span_row->kind = NULL;
    }
    if (archived_span_row->model_name) {
        free(archived_span_row->model_name);
        archived_span_row->model_name = NULL;
    }
    if (archived_span_row->model_provider) {
        free(archived_span_row->model_provider);
        archived_span_row->model_provider = NULL;
    }
    if (archived_span_row->name) {
        free(archived_span_row->name);
        archived_span_row->name = NULL;
    }
    if (archived_span_row->output_tokens) {
        free(archived_span_row->output_tokens);
        archived_span_row->output_tokens = NULL;
    }
    if (archived_span_row->output_uri) {
        free(archived_span_row->output_uri);
        archived_span_row->output_uri = NULL;
    }
    if (archived_span_row->parent_span_id) {
        free(archived_span_row->parent_span_id);
        archived_span_row->parent_span_id = NULL;
    }
    if (archived_span_row->project_id) {
        free(archived_span_row->project_id);
        archived_span_row->project_id = NULL;
    }
    if (archived_span_row->raw_uri) {
        free(archived_span_row->raw_uri);
        archived_span_row->raw_uri = NULL;
    }
    if (archived_span_row->reasoning_tokens) {
        free(archived_span_row->reasoning_tokens);
        archived_span_row->reasoning_tokens = NULL;
    }
    if (archived_span_row->span_id) {
        free(archived_span_row->span_id);
        archived_span_row->span_id = NULL;
    }
    if (archived_span_row->start_time) {
        free(archived_span_row->start_time);
        archived_span_row->start_time = NULL;
    }
    if (archived_span_row->status) {
        free(archived_span_row->status);
        archived_span_row->status = NULL;
    }
    if (archived_span_row->tenant_id) {
        free(archived_span_row->tenant_id);
        archived_span_row->tenant_id = NULL;
    }
    if (archived_span_row->trace_id) {
        free(archived_span_row->trace_id);
        archived_span_row->trace_id = NULL;
    }
    if (archived_span_row->unmapped_json) {
        free(archived_span_row->unmapped_json);
        archived_span_row->unmapped_json = NULL;
    }
    free(archived_span_row);
}

cJSON *archived_span_row_convertToJSON(archived_span_row_t *archived_span_row) {
    cJSON *item = cJSON_CreateObject();

    // archived_span_row->attributes_json
    if (!archived_span_row->attributes_json) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "attributes_json", archived_span_row->attributes_json) == NULL) {
    goto fail; //String
    }


    // archived_span_row->cost_amount_micros
    if(archived_span_row->cost_amount_micros) {
    if(cJSON_AddStringToObject(item, "cost_amount_micros", archived_span_row->cost_amount_micros) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->cost_currency
    if(archived_span_row->cost_currency) {
    if(cJSON_AddStringToObject(item, "cost_currency", archived_span_row->cost_currency) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->end_time
    if(archived_span_row->end_time) {
    if(cJSON_AddStringToObject(item, "end_time", archived_span_row->end_time) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->environment_id
    if (!archived_span_row->environment_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "environment_id", archived_span_row->environment_id) == NULL) {
    goto fail; //String
    }


    // archived_span_row->input_tokens
    if(archived_span_row->input_tokens) {
    if(cJSON_AddStringToObject(item, "input_tokens", archived_span_row->input_tokens) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->input_uri
    if(archived_span_row->input_uri) {
    if(cJSON_AddStringToObject(item, "input_uri", archived_span_row->input_uri) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->kind
    if (!archived_span_row->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", archived_span_row->kind) == NULL) {
    goto fail; //String
    }


    // archived_span_row->model_name
    if(archived_span_row->model_name) {
    if(cJSON_AddStringToObject(item, "model_name", archived_span_row->model_name) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->model_provider
    if(archived_span_row->model_provider) {
    if(cJSON_AddStringToObject(item, "model_provider", archived_span_row->model_provider) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->name
    if (!archived_span_row->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", archived_span_row->name) == NULL) {
    goto fail; //String
    }


    // archived_span_row->output_tokens
    if(archived_span_row->output_tokens) {
    if(cJSON_AddStringToObject(item, "output_tokens", archived_span_row->output_tokens) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->output_uri
    if(archived_span_row->output_uri) {
    if(cJSON_AddStringToObject(item, "output_uri", archived_span_row->output_uri) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->parent_span_id
    if(archived_span_row->parent_span_id) {
    if(cJSON_AddStringToObject(item, "parent_span_id", archived_span_row->parent_span_id) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->project_id
    if (!archived_span_row->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", archived_span_row->project_id) == NULL) {
    goto fail; //String
    }


    // archived_span_row->raw_uri
    if (!archived_span_row->raw_uri) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "raw_uri", archived_span_row->raw_uri) == NULL) {
    goto fail; //String
    }


    // archived_span_row->reasoning_tokens
    if(archived_span_row->reasoning_tokens) {
    if(cJSON_AddStringToObject(item, "reasoning_tokens", archived_span_row->reasoning_tokens) == NULL) {
    goto fail; //String
    }
    }


    // archived_span_row->seq
    if (!archived_span_row->seq) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "seq", archived_span_row->seq) == NULL) {
    goto fail; //Numeric
    }


    // archived_span_row->span_id
    if (!archived_span_row->span_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "span_id", archived_span_row->span_id) == NULL) {
    goto fail; //String
    }


    // archived_span_row->start_time
    if (!archived_span_row->start_time) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "start_time", archived_span_row->start_time) == NULL) {
    goto fail; //String
    }


    // archived_span_row->status
    if (!archived_span_row->status) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "status", archived_span_row->status) == NULL) {
    goto fail; //String
    }


    // archived_span_row->tenant_id
    if (!archived_span_row->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", archived_span_row->tenant_id) == NULL) {
    goto fail; //String
    }


    // archived_span_row->trace_id
    if (!archived_span_row->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", archived_span_row->trace_id) == NULL) {
    goto fail; //String
    }


    // archived_span_row->unmapped_json
    if (!archived_span_row->unmapped_json) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "unmapped_json", archived_span_row->unmapped_json) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

archived_span_row_t *archived_span_row_parseFromJSON(cJSON *archived_span_rowJSON){

    archived_span_row_t *archived_span_row_local_var = NULL;

    // archived_span_row->attributes_json
    cJSON *attributes_json = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "attributes_json");
    if (cJSON_IsNull(attributes_json)) {
        attributes_json = NULL;
    }
    if (!attributes_json) {
        goto end;
    }

    
    if(!cJSON_IsString(attributes_json))
    {
    goto end; //String
    }

    // archived_span_row->cost_amount_micros
    cJSON *cost_amount_micros = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "cost_amount_micros");
    if (cJSON_IsNull(cost_amount_micros)) {
        cost_amount_micros = NULL;
    }
    if (cost_amount_micros) { 
    if(!cJSON_IsString(cost_amount_micros) && !cJSON_IsNull(cost_amount_micros))
    {
    goto end; //String
    }
    }

    // archived_span_row->cost_currency
    cJSON *cost_currency = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "cost_currency");
    if (cJSON_IsNull(cost_currency)) {
        cost_currency = NULL;
    }
    if (cost_currency) { 
    if(!cJSON_IsString(cost_currency) && !cJSON_IsNull(cost_currency))
    {
    goto end; //String
    }
    }

    // archived_span_row->end_time
    cJSON *end_time = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "end_time");
    if (cJSON_IsNull(end_time)) {
        end_time = NULL;
    }
    if (end_time) { 
    if(!cJSON_IsString(end_time) && !cJSON_IsNull(end_time))
    {
    goto end; //String
    }
    }

    // archived_span_row->environment_id
    cJSON *environment_id = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "environment_id");
    if (cJSON_IsNull(environment_id)) {
        environment_id = NULL;
    }
    if (!environment_id) {
        goto end;
    }

    
    if(!cJSON_IsString(environment_id))
    {
    goto end; //String
    }

    // archived_span_row->input_tokens
    cJSON *input_tokens = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "input_tokens");
    if (cJSON_IsNull(input_tokens)) {
        input_tokens = NULL;
    }
    if (input_tokens) { 
    if(!cJSON_IsString(input_tokens) && !cJSON_IsNull(input_tokens))
    {
    goto end; //String
    }
    }

    // archived_span_row->input_uri
    cJSON *input_uri = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "input_uri");
    if (cJSON_IsNull(input_uri)) {
        input_uri = NULL;
    }
    if (input_uri) { 
    if(!cJSON_IsString(input_uri) && !cJSON_IsNull(input_uri))
    {
    goto end; //String
    }
    }

    // archived_span_row->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "kind");
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

    // archived_span_row->model_name
    cJSON *model_name = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "model_name");
    if (cJSON_IsNull(model_name)) {
        model_name = NULL;
    }
    if (model_name) { 
    if(!cJSON_IsString(model_name) && !cJSON_IsNull(model_name))
    {
    goto end; //String
    }
    }

    // archived_span_row->model_provider
    cJSON *model_provider = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "model_provider");
    if (cJSON_IsNull(model_provider)) {
        model_provider = NULL;
    }
    if (model_provider) { 
    if(!cJSON_IsString(model_provider) && !cJSON_IsNull(model_provider))
    {
    goto end; //String
    }
    }

    // archived_span_row->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "name");
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

    // archived_span_row->output_tokens
    cJSON *output_tokens = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "output_tokens");
    if (cJSON_IsNull(output_tokens)) {
        output_tokens = NULL;
    }
    if (output_tokens) { 
    if(!cJSON_IsString(output_tokens) && !cJSON_IsNull(output_tokens))
    {
    goto end; //String
    }
    }

    // archived_span_row->output_uri
    cJSON *output_uri = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "output_uri");
    if (cJSON_IsNull(output_uri)) {
        output_uri = NULL;
    }
    if (output_uri) { 
    if(!cJSON_IsString(output_uri) && !cJSON_IsNull(output_uri))
    {
    goto end; //String
    }
    }

    // archived_span_row->parent_span_id
    cJSON *parent_span_id = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "parent_span_id");
    if (cJSON_IsNull(parent_span_id)) {
        parent_span_id = NULL;
    }
    if (parent_span_id) { 
    if(!cJSON_IsString(parent_span_id) && !cJSON_IsNull(parent_span_id))
    {
    goto end; //String
    }
    }

    // archived_span_row->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "project_id");
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

    // archived_span_row->raw_uri
    cJSON *raw_uri = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "raw_uri");
    if (cJSON_IsNull(raw_uri)) {
        raw_uri = NULL;
    }
    if (!raw_uri) {
        goto end;
    }

    
    if(!cJSON_IsString(raw_uri))
    {
    goto end; //String
    }

    // archived_span_row->reasoning_tokens
    cJSON *reasoning_tokens = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "reasoning_tokens");
    if (cJSON_IsNull(reasoning_tokens)) {
        reasoning_tokens = NULL;
    }
    if (reasoning_tokens) { 
    if(!cJSON_IsString(reasoning_tokens) && !cJSON_IsNull(reasoning_tokens))
    {
    goto end; //String
    }
    }

    // archived_span_row->seq
    cJSON *seq = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "seq");
    if (cJSON_IsNull(seq)) {
        seq = NULL;
    }
    if (!seq) {
        goto end;
    }

    
    if(!cJSON_IsNumber(seq))
    {
    goto end; //Numeric
    }

    // archived_span_row->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "span_id");
    if (cJSON_IsNull(span_id)) {
        span_id = NULL;
    }
    if (!span_id) {
        goto end;
    }

    
    if(!cJSON_IsString(span_id))
    {
    goto end; //String
    }

    // archived_span_row->start_time
    cJSON *start_time = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "start_time");
    if (cJSON_IsNull(start_time)) {
        start_time = NULL;
    }
    if (!start_time) {
        goto end;
    }

    
    if(!cJSON_IsString(start_time))
    {
    goto end; //String
    }

    // archived_span_row->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "status");
    if (cJSON_IsNull(status)) {
        status = NULL;
    }
    if (!status) {
        goto end;
    }

    
    if(!cJSON_IsString(status))
    {
    goto end; //String
    }

    // archived_span_row->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "tenant_id");
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

    // archived_span_row->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "trace_id");
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

    // archived_span_row->unmapped_json
    cJSON *unmapped_json = cJSON_GetObjectItemCaseSensitive(archived_span_rowJSON, "unmapped_json");
    if (cJSON_IsNull(unmapped_json)) {
        unmapped_json = NULL;
    }
    if (!unmapped_json) {
        goto end;
    }

    
    if(!cJSON_IsString(unmapped_json))
    {
    goto end; //String
    }


    archived_span_row_local_var = archived_span_row_create_internal (
        strdup(attributes_json->valuestring),
        cost_amount_micros && !cJSON_IsNull(cost_amount_micros) ? strdup(cost_amount_micros->valuestring) : NULL,
        cost_currency && !cJSON_IsNull(cost_currency) ? strdup(cost_currency->valuestring) : NULL,
        end_time && !cJSON_IsNull(end_time) ? strdup(end_time->valuestring) : NULL,
        strdup(environment_id->valuestring),
        input_tokens && !cJSON_IsNull(input_tokens) ? strdup(input_tokens->valuestring) : NULL,
        input_uri && !cJSON_IsNull(input_uri) ? strdup(input_uri->valuestring) : NULL,
        strdup(kind->valuestring),
        model_name && !cJSON_IsNull(model_name) ? strdup(model_name->valuestring) : NULL,
        model_provider && !cJSON_IsNull(model_provider) ? strdup(model_provider->valuestring) : NULL,
        strdup(name->valuestring),
        output_tokens && !cJSON_IsNull(output_tokens) ? strdup(output_tokens->valuestring) : NULL,
        output_uri && !cJSON_IsNull(output_uri) ? strdup(output_uri->valuestring) : NULL,
        parent_span_id && !cJSON_IsNull(parent_span_id) ? strdup(parent_span_id->valuestring) : NULL,
        strdup(project_id->valuestring),
        strdup(raw_uri->valuestring),
        reasoning_tokens && !cJSON_IsNull(reasoning_tokens) ? strdup(reasoning_tokens->valuestring) : NULL,
        seq->valuedouble,
        strdup(span_id->valuestring),
        strdup(start_time->valuestring),
        strdup(status->valuestring),
        strdup(tenant_id->valuestring),
        strdup(trace_id->valuestring),
        strdup(unmapped_json->valuestring)
        );

    return archived_span_row_local_var;
end:
    return NULL;

}
