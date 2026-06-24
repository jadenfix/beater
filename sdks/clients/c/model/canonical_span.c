#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "canonical_span.h"



static canonical_span_t *canonical_span_create_internal(
    list_t* attributes,
    money_t *cost,
    char *end_time,
    char *environment_id,
    artifact_ref_t *input_ref,
    char *kind,
    model_ref_t *model,
    char *name,
    char *normalizer_version,
    artifact_ref_t *output_ref,
    char *parent_span_id,
    char *project_id,
    artifact_ref_t *raw_ref,
    int schema_version,
    long seq,
    char *span_id,
    char *start_time,
    beater_api_span_status__e status,
    char *tenant_id,
    token_counts_t *tokens,
    char *trace_id,
    any_type_t *unmapped_attrs
    ) {
    canonical_span_t *canonical_span_local_var = malloc(sizeof(canonical_span_t));
    if (!canonical_span_local_var) {
        return NULL;
    }
    canonical_span_local_var->attributes = attributes;
    canonical_span_local_var->cost = cost;
    canonical_span_local_var->end_time = end_time;
    canonical_span_local_var->environment_id = environment_id;
    canonical_span_local_var->input_ref = input_ref;
    canonical_span_local_var->kind = kind;
    canonical_span_local_var->model = model;
    canonical_span_local_var->name = name;
    canonical_span_local_var->normalizer_version = normalizer_version;
    canonical_span_local_var->output_ref = output_ref;
    canonical_span_local_var->parent_span_id = parent_span_id;
    canonical_span_local_var->project_id = project_id;
    canonical_span_local_var->raw_ref = raw_ref;
    canonical_span_local_var->schema_version = schema_version;
    canonical_span_local_var->seq = seq;
    canonical_span_local_var->span_id = span_id;
    canonical_span_local_var->start_time = start_time;
    canonical_span_local_var->status = status;
    canonical_span_local_var->tenant_id = tenant_id;
    canonical_span_local_var->tokens = tokens;
    canonical_span_local_var->trace_id = trace_id;
    canonical_span_local_var->unmapped_attrs = unmapped_attrs;

    canonical_span_local_var->_library_owned = 1;
    return canonical_span_local_var;
}

__attribute__((deprecated)) canonical_span_t *canonical_span_create(
    list_t* attributes,
    money_t *cost,
    char *end_time,
    char *environment_id,
    artifact_ref_t *input_ref,
    char *kind,
    model_ref_t *model,
    char *name,
    char *normalizer_version,
    artifact_ref_t *output_ref,
    char *parent_span_id,
    char *project_id,
    artifact_ref_t *raw_ref,
    int schema_version,
    long seq,
    char *span_id,
    char *start_time,
    beater_api_span_status__e status,
    char *tenant_id,
    token_counts_t *tokens,
    char *trace_id,
    any_type_t *unmapped_attrs
    ) {
    return canonical_span_create_internal (
        attributes,
        cost,
        end_time,
        environment_id,
        input_ref,
        kind,
        model,
        name,
        normalizer_version,
        output_ref,
        parent_span_id,
        project_id,
        raw_ref,
        schema_version,
        seq,
        span_id,
        start_time,
        status,
        tenant_id,
        tokens,
        trace_id,
        unmapped_attrs
        );
}

void canonical_span_free(canonical_span_t *canonical_span) {
    if(NULL == canonical_span){
        return ;
    }
    if(canonical_span->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "canonical_span_free");
        return ;
    }
    listEntry_t *listEntry;
    if (canonical_span->attributes) {
        list_ForEach(listEntry, canonical_span->attributes) {
            keyValuePair_t *localKeyValue = listEntry->data;
            free (localKeyValue->key);
            free (localKeyValue->value);
            keyValuePair_free(localKeyValue);
        }
        list_freeList(canonical_span->attributes);
        canonical_span->attributes = NULL;
    }
    if (canonical_span->cost) {
        money_free(canonical_span->cost);
        canonical_span->cost = NULL;
    }
    if (canonical_span->end_time) {
        free(canonical_span->end_time);
        canonical_span->end_time = NULL;
    }
    if (canonical_span->environment_id) {
        free(canonical_span->environment_id);
        canonical_span->environment_id = NULL;
    }
    if (canonical_span->input_ref) {
        artifact_ref_free(canonical_span->input_ref);
        canonical_span->input_ref = NULL;
    }
    if (canonical_span->kind) {
        free(canonical_span->kind);
        canonical_span->kind = NULL;
    }
    if (canonical_span->model) {
        model_ref_free(canonical_span->model);
        canonical_span->model = NULL;
    }
    if (canonical_span->name) {
        free(canonical_span->name);
        canonical_span->name = NULL;
    }
    if (canonical_span->normalizer_version) {
        free(canonical_span->normalizer_version);
        canonical_span->normalizer_version = NULL;
    }
    if (canonical_span->output_ref) {
        artifact_ref_free(canonical_span->output_ref);
        canonical_span->output_ref = NULL;
    }
    if (canonical_span->parent_span_id) {
        free(canonical_span->parent_span_id);
        canonical_span->parent_span_id = NULL;
    }
    if (canonical_span->project_id) {
        free(canonical_span->project_id);
        canonical_span->project_id = NULL;
    }
    if (canonical_span->raw_ref) {
        artifact_ref_free(canonical_span->raw_ref);
        canonical_span->raw_ref = NULL;
    }
    if (canonical_span->span_id) {
        free(canonical_span->span_id);
        canonical_span->span_id = NULL;
    }
    if (canonical_span->start_time) {
        free(canonical_span->start_time);
        canonical_span->start_time = NULL;
    }
    if (canonical_span->tenant_id) {
        free(canonical_span->tenant_id);
        canonical_span->tenant_id = NULL;
    }
    if (canonical_span->tokens) {
        token_counts_free(canonical_span->tokens);
        canonical_span->tokens = NULL;
    }
    if (canonical_span->trace_id) {
        free(canonical_span->trace_id);
        canonical_span->trace_id = NULL;
    }
    if (canonical_span->unmapped_attrs) {
        _free(canonical_span->unmapped_attrs);
        canonical_span->unmapped_attrs = NULL;
    }
    free(canonical_span);
}

cJSON *canonical_span_convertToJSON(canonical_span_t *canonical_span) {
    cJSON *item = cJSON_CreateObject();

    // canonical_span->attributes
    if (!canonical_span->attributes) {
        goto fail;
    }
    cJSON *attributes = cJSON_AddObjectToObject(item, "attributes");
    if(attributes == NULL) {
        goto fail; //primitive map container
    }
    cJSON *localMapObject = attributes;
    listEntry_t *attributesListEntry;
    if (canonical_span->attributes) {
    list_ForEach(attributesListEntry, canonical_span->attributes) {
        keyValuePair_t *localKeyValue = attributesListEntry->data;
    }
    }


    // canonical_span->cost
    if(canonical_span->cost) {
    cJSON *cost_local_JSON = money_convertToJSON(canonical_span->cost);
    if(cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "cost", cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // canonical_span->end_time
    if(canonical_span->end_time) {
    if(cJSON_AddStringToObject(item, "end_time", canonical_span->end_time) == NULL) {
    goto fail; //Date-Time
    }
    }


    // canonical_span->environment_id
    if (!canonical_span->environment_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "environment_id", canonical_span->environment_id) == NULL) {
    goto fail; //String
    }


    // canonical_span->input_ref
    if(canonical_span->input_ref) {
    cJSON *input_ref_local_JSON = artifact_ref_convertToJSON(canonical_span->input_ref);
    if(input_ref_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "input_ref", input_ref_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // canonical_span->kind
    if (!canonical_span->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", canonical_span->kind) == NULL) {
    goto fail; //String
    }


    // canonical_span->model
    if(canonical_span->model) {
    cJSON *model_local_JSON = model_ref_convertToJSON(canonical_span->model);
    if(model_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "model", model_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // canonical_span->name
    if (!canonical_span->name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "name", canonical_span->name) == NULL) {
    goto fail; //String
    }


    // canonical_span->normalizer_version
    if (!canonical_span->normalizer_version) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "normalizer_version", canonical_span->normalizer_version) == NULL) {
    goto fail; //String
    }


    // canonical_span->output_ref
    if(canonical_span->output_ref) {
    cJSON *output_ref_local_JSON = artifact_ref_convertToJSON(canonical_span->output_ref);
    if(output_ref_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "output_ref", output_ref_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // canonical_span->parent_span_id
    if(canonical_span->parent_span_id) {
    if(cJSON_AddStringToObject(item, "parent_span_id", canonical_span->parent_span_id) == NULL) {
    goto fail; //String
    }
    }


    // canonical_span->project_id
    if (!canonical_span->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", canonical_span->project_id) == NULL) {
    goto fail; //String
    }


    // canonical_span->raw_ref
    if (!canonical_span->raw_ref) {
        goto fail;
    }
    cJSON *raw_ref_local_JSON = artifact_ref_convertToJSON(canonical_span->raw_ref);
    if(raw_ref_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "raw_ref", raw_ref_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // canonical_span->schema_version
    if (!canonical_span->schema_version) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "schema_version", canonical_span->schema_version) == NULL) {
    goto fail; //Numeric
    }


    // canonical_span->seq
    if (!canonical_span->seq) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "seq", canonical_span->seq) == NULL) {
    goto fail; //Numeric
    }


    // canonical_span->span_id
    if (!canonical_span->span_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "span_id", canonical_span->span_id) == NULL) {
    goto fail; //String
    }


    // canonical_span->start_time
    if (!canonical_span->start_time) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "start_time", canonical_span->start_time) == NULL) {
    goto fail; //Date-Time
    }


    // canonical_span->status
    if (beater_api_span_status__NULL == canonical_span->status) {
        goto fail;
    }
    cJSON *status_local_JSON = span_status_convertToJSON(canonical_span->status);
    if(status_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "status", status_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // canonical_span->tenant_id
    if (!canonical_span->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", canonical_span->tenant_id) == NULL) {
    goto fail; //String
    }


    // canonical_span->tokens
    if(canonical_span->tokens) {
    cJSON *tokens_local_JSON = token_counts_convertToJSON(canonical_span->tokens);
    if(tokens_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "tokens", tokens_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // canonical_span->trace_id
    if (!canonical_span->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", canonical_span->trace_id) == NULL) {
    goto fail; //String
    }


    // canonical_span->unmapped_attrs
    if (!canonical_span->unmapped_attrs) {
        goto fail;
    }
    cJSON *unmapped_attrs_local_JSON = _convertToJSON(canonical_span->unmapped_attrs);
    if(unmapped_attrs_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "unmapped_attrs", unmapped_attrs_local_JSON);
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

canonical_span_t *canonical_span_parseFromJSON(cJSON *canonical_spanJSON){

    canonical_span_t *canonical_span_local_var = NULL;

    // define the local map for canonical_span->attributes
    list_t *attributesList = NULL;

    // define the local variable for canonical_span->cost
    money_t *cost_local_nonprim = NULL;

    // define the local variable for canonical_span->input_ref
    artifact_ref_t *input_ref_local_nonprim = NULL;

    // define the local variable for canonical_span->model
    model_ref_t *model_local_nonprim = NULL;

    // define the local variable for canonical_span->output_ref
    artifact_ref_t *output_ref_local_nonprim = NULL;

    // define the local variable for canonical_span->raw_ref
    artifact_ref_t *raw_ref_local_nonprim = NULL;

    // define the local variable for canonical_span->status
    beater_api_span_status__e status_local_nonprim = 0;

    // define the local variable for canonical_span->tokens
    token_counts_t *tokens_local_nonprim = NULL;

    // define the local variable for canonical_span->unmapped_attrs
    _t *unmapped_attrs_local_nonprim = NULL;

    // canonical_span->attributes
    cJSON *attributes = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "attributes");
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

    // canonical_span->cost
    cJSON *cost = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "cost");
    if (cJSON_IsNull(cost)) {
        cost = NULL;
    }
    if (cost) { 
    cost_local_nonprim = money_parseFromJSON(cost); //nonprimitive
    }

    // canonical_span->end_time
    cJSON *end_time = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "end_time");
    if (cJSON_IsNull(end_time)) {
        end_time = NULL;
    }
    if (end_time) { 
    if(!cJSON_IsString(end_time) && !cJSON_IsNull(end_time))
    {
    goto end; //DateTime
    }
    }

    // canonical_span->environment_id
    cJSON *environment_id = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "environment_id");
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

    // canonical_span->input_ref
    cJSON *input_ref = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "input_ref");
    if (cJSON_IsNull(input_ref)) {
        input_ref = NULL;
    }
    if (input_ref) { 
    input_ref_local_nonprim = artifact_ref_parseFromJSON(input_ref); //nonprimitive
    }

    // canonical_span->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "kind");
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

    // canonical_span->model
    cJSON *model = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "model");
    if (cJSON_IsNull(model)) {
        model = NULL;
    }
    if (model) { 
    model_local_nonprim = model_ref_parseFromJSON(model); //nonprimitive
    }

    // canonical_span->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "name");
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

    // canonical_span->normalizer_version
    cJSON *normalizer_version = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "normalizer_version");
    if (cJSON_IsNull(normalizer_version)) {
        normalizer_version = NULL;
    }
    if (!normalizer_version) {
        goto end;
    }

    
    if(!cJSON_IsString(normalizer_version))
    {
    goto end; //String
    }

    // canonical_span->output_ref
    cJSON *output_ref = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "output_ref");
    if (cJSON_IsNull(output_ref)) {
        output_ref = NULL;
    }
    if (output_ref) { 
    output_ref_local_nonprim = artifact_ref_parseFromJSON(output_ref); //nonprimitive
    }

    // canonical_span->parent_span_id
    cJSON *parent_span_id = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "parent_span_id");
    if (cJSON_IsNull(parent_span_id)) {
        parent_span_id = NULL;
    }
    if (parent_span_id) { 
    if(!cJSON_IsString(parent_span_id) && !cJSON_IsNull(parent_span_id))
    {
    goto end; //String
    }
    }

    // canonical_span->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "project_id");
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

    // canonical_span->raw_ref
    cJSON *raw_ref = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "raw_ref");
    if (cJSON_IsNull(raw_ref)) {
        raw_ref = NULL;
    }
    if (!raw_ref) {
        goto end;
    }

    
    raw_ref_local_nonprim = artifact_ref_parseFromJSON(raw_ref); //nonprimitive

    // canonical_span->schema_version
    cJSON *schema_version = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "schema_version");
    if (cJSON_IsNull(schema_version)) {
        schema_version = NULL;
    }
    if (!schema_version) {
        goto end;
    }

    
    if(!cJSON_IsNumber(schema_version))
    {
    goto end; //Numeric
    }

    // canonical_span->seq
    cJSON *seq = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "seq");
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

    // canonical_span->span_id
    cJSON *span_id = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "span_id");
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

    // canonical_span->start_time
    cJSON *start_time = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "start_time");
    if (cJSON_IsNull(start_time)) {
        start_time = NULL;
    }
    if (!start_time) {
        goto end;
    }

    
    if(!cJSON_IsString(start_time) && !cJSON_IsNull(start_time))
    {
    goto end; //DateTime
    }

    // canonical_span->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "status");
    if (cJSON_IsNull(status)) {
        status = NULL;
    }
    if (!status) {
        goto end;
    }

    
    status_local_nonprim = span_status_parseFromJSON(status); //custom

    // canonical_span->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "tenant_id");
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

    // canonical_span->tokens
    cJSON *tokens = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "tokens");
    if (cJSON_IsNull(tokens)) {
        tokens = NULL;
    }
    if (tokens) { 
    tokens_local_nonprim = token_counts_parseFromJSON(tokens); //nonprimitive
    }

    // canonical_span->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "trace_id");
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

    // canonical_span->unmapped_attrs
    cJSON *unmapped_attrs = cJSON_GetObjectItemCaseSensitive(canonical_spanJSON, "unmapped_attrs");
    if (cJSON_IsNull(unmapped_attrs)) {
        unmapped_attrs = NULL;
    }
    if (!unmapped_attrs) {
        goto end;
    }

    
    unmapped_attrs_local_nonprim = _parseFromJSON(unmapped_attrs); //custom


    canonical_span_local_var = canonical_span_create_internal (
        attributesList,
        cost ? cost_local_nonprim : NULL,
        end_time && !cJSON_IsNull(end_time) ? strdup(end_time->valuestring) : NULL,
        strdup(environment_id->valuestring),
        input_ref ? input_ref_local_nonprim : NULL,
        strdup(kind->valuestring),
        model ? model_local_nonprim : NULL,
        strdup(name->valuestring),
        strdup(normalizer_version->valuestring),
        output_ref ? output_ref_local_nonprim : NULL,
        parent_span_id && !cJSON_IsNull(parent_span_id) ? strdup(parent_span_id->valuestring) : NULL,
        strdup(project_id->valuestring),
        raw_ref_local_nonprim,
        schema_version->valuedouble,
        seq->valuedouble,
        strdup(span_id->valuestring),
        strdup(start_time->valuestring),
        status_local_nonprim,
        strdup(tenant_id->valuestring),
        tokens ? tokens_local_nonprim : NULL,
        strdup(trace_id->valuestring),
        unmapped_attrs_local_nonprim
        );

    return canonical_span_local_var;
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
    if (cost_local_nonprim) {
        money_free(cost_local_nonprim);
        cost_local_nonprim = NULL;
    }
    if (input_ref_local_nonprim) {
        artifact_ref_free(input_ref_local_nonprim);
        input_ref_local_nonprim = NULL;
    }
    if (model_local_nonprim) {
        model_ref_free(model_local_nonprim);
        model_local_nonprim = NULL;
    }
    if (output_ref_local_nonprim) {
        artifact_ref_free(output_ref_local_nonprim);
        output_ref_local_nonprim = NULL;
    }
    if (raw_ref_local_nonprim) {
        artifact_ref_free(raw_ref_local_nonprim);
        raw_ref_local_nonprim = NULL;
    }
    if (status_local_nonprim) {
        status_local_nonprim = 0;
    }
    if (tokens_local_nonprim) {
        token_counts_free(tokens_local_nonprim);
        tokens_local_nonprim = NULL;
    }
    if (unmapped_attrs_local_nonprim) {
        _free(unmapped_attrs_local_nonprim);
        unmapped_attrs_local_nonprim = NULL;
    }
    return NULL;

}
