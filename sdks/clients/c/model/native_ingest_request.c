#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "native_ingest_request.h"



static native_ingest_request_t *native_ingest_request_create_internal(
    list_t* attributes,
    auth_context_t *auth_context,
    money_t *cost,
    char *end_time,
    char *idempotency_key,
    any_type_t *input,
    char *kind,
    model_ref_t *model,
    char *name,
    any_type_t *output,
    char *parent_span_id,
    beater_api_redaction_class__e redaction_class,
    tenant_scope_t *scope,
    long seq,
    char *span_id,
    char *start_time,
    beater_api_span_status__e status,
    token_counts_t *tokens,
    char *trace_id
    ) {
    native_ingest_request_t *native_ingest_request_local_var = malloc(sizeof(native_ingest_request_t));
    if (!native_ingest_request_local_var) {
        return NULL;
    }
    native_ingest_request_local_var->attributes = attributes;
    native_ingest_request_local_var->auth_context = auth_context;
    native_ingest_request_local_var->cost = cost;
    native_ingest_request_local_var->end_time = end_time;
    native_ingest_request_local_var->idempotency_key = idempotency_key;
    native_ingest_request_local_var->input = input;
    native_ingest_request_local_var->kind = kind;
    native_ingest_request_local_var->model = model;
    native_ingest_request_local_var->name = name;
    native_ingest_request_local_var->output = output;
    native_ingest_request_local_var->parent_span_id = parent_span_id;
    native_ingest_request_local_var->redaction_class = redaction_class;
    native_ingest_request_local_var->scope = scope;
    native_ingest_request_local_var->seq = seq;
    native_ingest_request_local_var->span_id = span_id;
    native_ingest_request_local_var->start_time = start_time;
    native_ingest_request_local_var->status = status;
    native_ingest_request_local_var->tokens = tokens;
    native_ingest_request_local_var->trace_id = trace_id;

    native_ingest_request_local_var->_library_owned = 1;
    return native_ingest_request_local_var;
}

__attribute__((deprecated)) native_ingest_request_t *native_ingest_request_create(
    list_t* attributes,
    auth_context_t *auth_context,
    money_t *cost,
    char *end_time,
    char *idempotency_key,
    any_type_t *input,
    char *kind,
    model_ref_t *model,
    char *name,
    any_type_t *output,
    char *parent_span_id,
    beater_api_redaction_class__e redaction_class,
    tenant_scope_t *scope,
    long seq,
    char *span_id,
    char *start_time,
    beater_api_span_status__e status,
    token_counts_t *tokens,
    char *trace_id
    ) {
    return native_ingest_request_create_internal (
        attributes,
        auth_context,
        cost,
        end_time,
        idempotency_key,
        input,
        kind,
        model,
        name,
        output,
        parent_span_id,
        redaction_class,
        scope,
        seq,
        span_id,
        start_time,
        status,
        tokens,
        trace_id
        );
}

void native_ingest_request_free(native_ingest_request_t *native_ingest_request) {
    if(NULL == native_ingest_request){
        return ;
    }
    if(native_ingest_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "native_ingest_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (native_ingest_request->attributes) {
        list_ForEach(listEntry, native_ingest_request->attributes) {
            keyValuePair_t *localKeyValue = listEntry->data;
            free (localKeyValue->key);
            free (localKeyValue->value);
            keyValuePair_free(localKeyValue);
        }
        list_freeList(native_ingest_request->attributes);
        native_ingest_request->attributes = NULL;
    }
    if (native_ingest_request->auth_context) {
        auth_context_free(native_ingest_request->auth_context);
        native_ingest_request->auth_context = NULL;
    }
    if (native_ingest_request->cost) {
        money_free(native_ingest_request->cost);
        native_ingest_request->cost = NULL;
    }
    if (native_ingest_request->end_time) {
        free(native_ingest_request->end_time);
        native_ingest_request->end_time = NULL;
    }
    if (native_ingest_request->idempotency_key) {
        free(native_ingest_request->idempotency_key);
        native_ingest_request->idempotency_key = NULL;
    }
    if (native_ingest_request->input) {
        _free(native_ingest_request->input);
        native_ingest_request->input = NULL;
    }
    if (native_ingest_request->kind) {
        free(native_ingest_request->kind);
        native_ingest_request->kind = NULL;
    }
    if (native_ingest_request->model) {
        model_ref_free(native_ingest_request->model);
        native_ingest_request->model = NULL;
    }
    if (native_ingest_request->name) {
        free(native_ingest_request->name);
        native_ingest_request->name = NULL;
    }
    if (native_ingest_request->output) {
        _free(native_ingest_request->output);
        native_ingest_request->output = NULL;
    }
    if (native_ingest_request->parent_span_id) {
        free(native_ingest_request->parent_span_id);
        native_ingest_request->parent_span_id = NULL;
    }
    if (native_ingest_request->scope) {
        tenant_scope_free(native_ingest_request->scope);
        native_ingest_request->scope = NULL;
    }
    if (native_ingest_request->span_id) {
        free(native_ingest_request->span_id);
        native_ingest_request->span_id = NULL;
    }
    if (native_ingest_request->start_time) {
        free(native_ingest_request->start_time);
        native_ingest_request->start_time = NULL;
    }
    if (native_ingest_request->tokens) {
        token_counts_free(native_ingest_request->tokens);
        native_ingest_request->tokens = NULL;
    }
    if (native_ingest_request->trace_id) {
        free(native_ingest_request->trace_id);
        native_ingest_request->trace_id = NULL;
    }
    free(native_ingest_request);
}

cJSON *native_ingest_request_convertToJSON(native_ingest_request_t *native_ingest_request) {
    cJSON *item = cJSON_CreateObject();

    // native_ingest_request->attributes
    if (!native_ingest_request->attributes) {
        goto fail;
    }
    cJSON *attributes = cJSON_AddObjectToObject(item, "attributes");
    if(attributes == NULL) {
        goto fail; //primitive map container
    }
    cJSON *localMapObject = attributes;
    listEntry_t *attributesListEntry;
    if (native_ingest_request->attributes) {
    list_ForEach(attributesListEntry, native_ingest_request->attributes) {
        keyValuePair_t *localKeyValue = attributesListEntry->data;
    }
    }


    // native_ingest_request->auth_context
    if(native_ingest_request->auth_context) {
    cJSON *auth_context_local_JSON = auth_context_convertToJSON(native_ingest_request->auth_context);
    if(auth_context_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "auth_context", auth_context_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // native_ingest_request->cost
    if(native_ingest_request->cost) {
    cJSON *cost_local_JSON = money_convertToJSON(native_ingest_request->cost);
    if(cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "cost", cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // native_ingest_request->end_time
    if(native_ingest_request->end_time) {
    if(cJSON_AddStringToObject(item, "end_time", native_ingest_request->end_time) == NULL) {
    goto fail; //Date-Time
    }
    }


    // native_ingest_request->idempotency_key
    if(native_ingest_request->idempotency_key) {
    if(cJSON_AddStringToObject(item, "idempotency_key", native_ingest_request->idempotency_key) == NULL) {
    goto fail; //String
    }
    }


    // native_ingest_request->input
    if(native_ingest_request->input) {
    cJSON *input_local_JSON = _convertToJSON(native_ingest_request->input);
    if(input_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "input", input_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // native_ingest_request->kind
    if (!native_ingest_request->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", native_ingest_request->kind) == NULL) {
    goto fail; //String
    }


    // native_ingest_request->model
    if(native_ingest_request->model) {
    cJSON *model_local_JSON = model_ref_convertToJSON(native_ingest_request->model);
    if(model_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "model", model_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // native_ingest_request->name
    if (!native_ingest_request->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", native_ingest_request->name) == NULL) {
    goto fail; //String
    }


    // native_ingest_request->output
    if(native_ingest_request->output) {
    cJSON *output_local_JSON = _convertToJSON(native_ingest_request->output);
    if(output_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "output", output_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // native_ingest_request->parent_span_id
    if(native_ingest_request->parent_span_id) {
    if(cJSON_AddStringToObject(item, "parent_span_id", native_ingest_request->parent_span_id) == NULL) {
    goto fail; //String
    }
    }


    // native_ingest_request->redaction_class
    if (beater_api_redaction_class__NULL == native_ingest_request->redaction_class) {
        goto fail;
    }
    cJSON *redaction_class_local_JSON = redaction_class_convertToJSON(native_ingest_request->redaction_class);
    if(redaction_class_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "redaction_class", redaction_class_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // native_ingest_request->scope
    if (!native_ingest_request->scope) {
        goto fail;
    }
    cJSON *scope_local_JSON = tenant_scope_convertToJSON(native_ingest_request->scope);
    if(scope_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "scope", scope_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // native_ingest_request->seq
    if (!native_ingest_request->seq) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "seq", native_ingest_request->seq) == NULL) {
    goto fail; //Numeric
    }


    // native_ingest_request->span_id
    if (!native_ingest_request->span_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "span_id", native_ingest_request->span_id) == NULL) {
    goto fail; //String
    }


    // native_ingest_request->start_time
    if(native_ingest_request->start_time) {
    if(cJSON_AddStringToObject(item, "start_time", native_ingest_request->start_time) == NULL) {
    goto fail; //Date-Time
    }
    }


    // native_ingest_request->status
    if (beater_api_span_status__NULL == native_ingest_request->status) {
        goto fail;
    }
    cJSON *status_local_JSON = span_status_convertToJSON(native_ingest_request->status);
    if(status_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "status", status_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // native_ingest_request->tokens
    if(native_ingest_request->tokens) {
    cJSON *tokens_local_JSON = token_counts_convertToJSON(native_ingest_request->tokens);
    if(tokens_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "tokens", tokens_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // native_ingest_request->trace_id
    if (!native_ingest_request->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", native_ingest_request->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

native_ingest_request_t *native_ingest_request_parseFromJSON(cJSON *native_ingest_requestJSON){

    native_ingest_request_t *native_ingest_request_local_var = NULL;

    // define the local map for native_ingest_request->attributes
    list_t *attributesList = NULL;

    // define the local variable for native_ingest_request->auth_context
    auth_context_t *auth_context_local_nonprim = NULL;

    // define the local variable for native_ingest_request->cost
    money_t *cost_local_nonprim = NULL;

    // define the local variable for native_ingest_request->input
    _t *input_local_nonprim = NULL;

    // define the local variable for native_ingest_request->model
    model_ref_t *model_local_nonprim = NULL;

    // define the local variable for native_ingest_request->output
    _t *output_local_nonprim = NULL;

    // define the local variable for native_ingest_request->redaction_class
    beater_api_redaction_class__e redaction_class_local_nonprim = 0;

    // define the local variable for native_ingest_request->scope
    tenant_scope_t *scope_local_nonprim = NULL;

    // define the local variable for native_ingest_request->status
    beater_api_span_status__e status_local_nonprim = 0;

    // define the local variable for native_ingest_request->tokens
    token_counts_t *tokens_local_nonprim = NULL;

    // native_ingest_request->attributes
    cJSON *attributes = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "attributes");
    if (cJSON_IsNull(attributes)) {
        attributes = NULL;
    }
    if (!attributes) {
        goto end;
    }

    
    cJSON *attributes_local_map = NULL;
    if(!cJSON_IsObject(attributes) && !cJSON_IsNull(attributes))
    {
        goto end;//primitive map container
    }
    if(cJSON_IsObject(attributes))
    {
        attributesList = list_createList();
        keyValuePair_t *localMapKeyPair;
        cJSON_ArrayForEach(attributes_local_map, attributes)
        {
            cJSON *localMapObject = attributes_local_map;
            list_addElement(attributesList , localMapKeyPair);
        }
    }

    // native_ingest_request->auth_context
    cJSON *auth_context = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "auth_context");
    if (cJSON_IsNull(auth_context)) {
        auth_context = NULL;
    }
    if (auth_context) { 
    auth_context_local_nonprim = auth_context_parseFromJSON(auth_context); //nonprimitive
    }

    // native_ingest_request->cost
    cJSON *cost = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "cost");
    if (cJSON_IsNull(cost)) {
        cost = NULL;
    }
    if (cost) { 
    cost_local_nonprim = money_parseFromJSON(cost); //nonprimitive
    }

    // native_ingest_request->end_time
    cJSON *end_time = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "end_time");
    if (cJSON_IsNull(end_time)) {
        end_time = NULL;
    }
    if (end_time) { 
    if(!cJSON_IsString(end_time) && !cJSON_IsNull(end_time))
    {
    goto end; //DateTime
    }
    }

    // native_ingest_request->idempotency_key
    cJSON *idempotency_key = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "idempotency_key");
    if (cJSON_IsNull(idempotency_key)) {
        idempotency_key = NULL;
    }
    if (idempotency_key) { 
    if(!cJSON_IsString(idempotency_key) && !cJSON_IsNull(idempotency_key))
    {
    goto end; //String
    }
    }

    // native_ingest_request->input
    cJSON *input = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "input");
    if (cJSON_IsNull(input)) {
        input = NULL;
    }
    if (input) { 
    input_local_nonprim = _parseFromJSON(input); //custom
    }

    // native_ingest_request->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "kind");
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

    // native_ingest_request->model
    cJSON *model = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "model");
    if (cJSON_IsNull(model)) {
        model = NULL;
    }
    if (model) { 
    model_local_nonprim = model_ref_parseFromJSON(model); //nonprimitive
    }

    // native_ingest_request->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "name");
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

    // native_ingest_request->output
    cJSON *output = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "output");
    if (cJSON_IsNull(output)) {
        output = NULL;
    }
    if (output) { 
    output_local_nonprim = _parseFromJSON(output); //custom
    }

    // native_ingest_request->parent_span_id
    cJSON *parent_span_id = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "parent_span_id");
    if (cJSON_IsNull(parent_span_id)) {
        parent_span_id = NULL;
    }
    if (parent_span_id) { 
    if(!cJSON_IsString(parent_span_id) && !cJSON_IsNull(parent_span_id))
    {
    goto end; //String
    }
    }

    // native_ingest_request->redaction_class
    cJSON *redaction_class = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "redaction_class");
    if (cJSON_IsNull(redaction_class)) {
        redaction_class = NULL;
    }
    if (!redaction_class) {
        goto end;
    }

    
    redaction_class_local_nonprim = redaction_class_parseFromJSON(redaction_class); //custom

    // native_ingest_request->scope
    cJSON *scope = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "scope");
    if (cJSON_IsNull(scope)) {
        scope = NULL;
    }
    if (!scope) {
        goto end;
    }

    
    scope_local_nonprim = tenant_scope_parseFromJSON(scope); //nonprimitive

    // native_ingest_request->seq
    cJSON *seq = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "seq");
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

    // native_ingest_request->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "span_id");
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

    // native_ingest_request->start_time
    cJSON *start_time = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "start_time");
    if (cJSON_IsNull(start_time)) {
        start_time = NULL;
    }
    if (start_time) { 
    if(!cJSON_IsString(start_time) && !cJSON_IsNull(start_time))
    {
    goto end; //DateTime
    }
    }

    // native_ingest_request->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "status");
    if (cJSON_IsNull(status)) {
        status = NULL;
    }
    if (!status) {
        goto end;
    }

    
    status_local_nonprim = span_status_parseFromJSON(status); //custom

    // native_ingest_request->tokens
    cJSON *tokens = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "tokens");
    if (cJSON_IsNull(tokens)) {
        tokens = NULL;
    }
    if (tokens) { 
    tokens_local_nonprim = token_counts_parseFromJSON(tokens); //nonprimitive
    }

    // native_ingest_request->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(native_ingest_requestJSON, "trace_id");
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


    native_ingest_request_local_var = native_ingest_request_create_internal (
        attributesList,
        auth_context ? auth_context_local_nonprim : NULL,
        cost ? cost_local_nonprim : NULL,
        end_time && !cJSON_IsNull(end_time) ? strdup(end_time->valuestring) : NULL,
        idempotency_key && !cJSON_IsNull(idempotency_key) ? strdup(idempotency_key->valuestring) : NULL,
        input ? input_local_nonprim : NULL,
        strdup(kind->valuestring),
        model ? model_local_nonprim : NULL,
        strdup(name->valuestring),
        output ? output_local_nonprim : NULL,
        parent_span_id && !cJSON_IsNull(parent_span_id) ? strdup(parent_span_id->valuestring) : NULL,
        redaction_class_local_nonprim,
        scope_local_nonprim,
        seq->valuedouble,
        strdup(span_id->valuestring),
        start_time && !cJSON_IsNull(start_time) ? strdup(start_time->valuestring) : NULL,
        status_local_nonprim,
        tokens ? tokens_local_nonprim : NULL,
        strdup(trace_id->valuestring)
        );

    return native_ingest_request_local_var;
end:
    if (attributesList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, attributesList) {
            keyValuePair_t *localKeyValue = listEntry->data;
            free(localKeyValue->key);
            localKeyValue->key = NULL;
            keyValuePair_free(localKeyValue);
            localKeyValue = NULL;
        }
        list_freeList(attributesList);
        attributesList = NULL;
    }
    if (auth_context_local_nonprim) {
        auth_context_free(auth_context_local_nonprim);
        auth_context_local_nonprim = NULL;
    }
    if (cost_local_nonprim) {
        money_free(cost_local_nonprim);
        cost_local_nonprim = NULL;
    }
    if (input_local_nonprim) {
        _free(input_local_nonprim);
        input_local_nonprim = NULL;
    }
    if (model_local_nonprim) {
        model_ref_free(model_local_nonprim);
        model_local_nonprim = NULL;
    }
    if (output_local_nonprim) {
        _free(output_local_nonprim);
        output_local_nonprim = NULL;
    }
    if (redaction_class_local_nonprim) {
        redaction_class_local_nonprim = 0;
    }
    if (scope_local_nonprim) {
        tenant_scope_free(scope_local_nonprim);
        scope_local_nonprim = NULL;
    }
    if (status_local_nonprim) {
        status_local_nonprim = 0;
    }
    if (tokens_local_nonprim) {
        token_counts_free(tokens_local_nonprim);
        tokens_local_nonprim = NULL;
    }
    return NULL;

}
