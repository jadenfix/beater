#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "token_counts.h"



static token_counts_t *token_counts_create_internal(
    long cache_read,
    long input,
    long output,
    long reasoning
    ) {
    token_counts_t *token_counts_local_var = malloc(sizeof(token_counts_t));
    if (!token_counts_local_var) {
        return NULL;
    }
    token_counts_local_var->cache_read = cache_read;
    token_counts_local_var->input = input;
    token_counts_local_var->output = output;
    token_counts_local_var->reasoning = reasoning;

    token_counts_local_var->_library_owned = 1;
    return token_counts_local_var;
}

__attribute__((deprecated)) token_counts_t *token_counts_create(
    long cache_read,
    long input,
    long output,
    long reasoning
    ) {
    return token_counts_create_internal (
        cache_read,
        input,
        output,
        reasoning
        );
}

void token_counts_free(token_counts_t *token_counts) {
    if(NULL == token_counts){
        return ;
    }
    if(token_counts->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "token_counts_free");
        return ;
    }
    listEntry_t *listEntry;
    free(token_counts);
}

cJSON *token_counts_convertToJSON(token_counts_t *token_counts) {
    cJSON *item = cJSON_CreateObject();

    // token_counts->cache_read
    if (!token_counts->cache_read) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "cache_read", token_counts->cache_read) == NULL) {
    goto fail; //Numeric
    }


    // token_counts->input
    if (!token_counts->input) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "input", token_counts->input) == NULL) {
    goto fail; //Numeric
    }


    // token_counts->output
    if (!token_counts->output) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "output", token_counts->output) == NULL) {
    goto fail; //Numeric
    }


    // token_counts->reasoning
    if (!token_counts->reasoning) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "reasoning", token_counts->reasoning) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

token_counts_t *token_counts_parseFromJSON(cJSON *token_countsJSON){

    token_counts_t *token_counts_local_var = NULL;

    // token_counts->cache_read
    cJSON *cache_read = cJSON_GetObjectItemCaseSensitive(token_countsJSON, "cache_read");
    if (cJSON_IsNull(cache_read)) {
        cache_read = NULL;
    }
    if (!cache_read) {
        goto end;
    }

    
    if(!cJSON_IsNumber(cache_read))
    {
    goto end; //Numeric
    }

    // token_counts->input
    cJSON *input = cJSON_GetObjectItemCaseSensitive(token_countsJSON, "input");
    if (cJSON_IsNull(input)) {
        input = NULL;
    }
    if (!input) {
        goto end;
    }

    
    if(!cJSON_IsNumber(input))
    {
    goto end; //Numeric
    }

    // token_counts->output
    cJSON *output = cJSON_GetObjectItemCaseSensitive(token_countsJSON, "output");
    if (cJSON_IsNull(output)) {
        output = NULL;
    }
    if (!output) {
        goto end;
    }

    
    if(!cJSON_IsNumber(output))
    {
    goto end; //Numeric
    }

    // token_counts->reasoning
    cJSON *reasoning = cJSON_GetObjectItemCaseSensitive(token_countsJSON, "reasoning");
    if (cJSON_IsNull(reasoning)) {
        reasoning = NULL;
    }
    if (!reasoning) {
        goto end;
    }

    
    if(!cJSON_IsNumber(reasoning))
    {
    goto end; //Numeric
    }


    token_counts_local_var = token_counts_create_internal (
        cache_read->valuedouble,
        input->valuedouble,
        output->valuedouble,
        reasoning->valuedouble
        );

    return token_counts_local_var;
end:
    return NULL;

}
