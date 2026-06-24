#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "otlp_ingest_outcome.h"



static otlp_ingest_outcome_t *otlp_ingest_outcome_create_internal(
    int accepted_raw,
    int accepted_spans,
    int downstream_queued,
    int duplicate_raw,
    int duplicate_spans
    ) {
    otlp_ingest_outcome_t *otlp_ingest_outcome_local_var = malloc(sizeof(otlp_ingest_outcome_t));
    if (!otlp_ingest_outcome_local_var) {
        return NULL;
    }
    otlp_ingest_outcome_local_var->accepted_raw = accepted_raw;
    otlp_ingest_outcome_local_var->accepted_spans = accepted_spans;
    otlp_ingest_outcome_local_var->downstream_queued = downstream_queued;
    otlp_ingest_outcome_local_var->duplicate_raw = duplicate_raw;
    otlp_ingest_outcome_local_var->duplicate_spans = duplicate_spans;

    otlp_ingest_outcome_local_var->_library_owned = 1;
    return otlp_ingest_outcome_local_var;
}

__attribute__((deprecated)) otlp_ingest_outcome_t *otlp_ingest_outcome_create(
    int accepted_raw,
    int accepted_spans,
    int downstream_queued,
    int duplicate_raw,
    int duplicate_spans
    ) {
    return otlp_ingest_outcome_create_internal (
        accepted_raw,
        accepted_spans,
        downstream_queued,
        duplicate_raw,
        duplicate_spans
        );
}

void otlp_ingest_outcome_free(otlp_ingest_outcome_t *otlp_ingest_outcome) {
    if(NULL == otlp_ingest_outcome){
        return ;
    }
    if(otlp_ingest_outcome->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "otlp_ingest_outcome_free");
        return ;
    }
    listEntry_t *listEntry;
    free(otlp_ingest_outcome);
}

cJSON *otlp_ingest_outcome_convertToJSON(otlp_ingest_outcome_t *otlp_ingest_outcome) {
    cJSON *item = cJSON_CreateObject();

    // otlp_ingest_outcome->accepted_raw
    if (!otlp_ingest_outcome->accepted_raw) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "accepted_raw", otlp_ingest_outcome->accepted_raw) == NULL) {
    goto fail; //Numeric
    }


    // otlp_ingest_outcome->accepted_spans
    if (!otlp_ingest_outcome->accepted_spans) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "accepted_spans", otlp_ingest_outcome->accepted_spans) == NULL) {
    goto fail; //Numeric
    }


    // otlp_ingest_outcome->downstream_queued
    if (!otlp_ingest_outcome->downstream_queued) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "downstream_queued", otlp_ingest_outcome->downstream_queued) == NULL) {
    goto fail; //Bool
    }


    // otlp_ingest_outcome->duplicate_raw
    if (!otlp_ingest_outcome->duplicate_raw) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "duplicate_raw", otlp_ingest_outcome->duplicate_raw) == NULL) {
    goto fail; //Numeric
    }


    // otlp_ingest_outcome->duplicate_spans
    if (!otlp_ingest_outcome->duplicate_spans) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "duplicate_spans", otlp_ingest_outcome->duplicate_spans) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

otlp_ingest_outcome_t *otlp_ingest_outcome_parseFromJSON(cJSON *otlp_ingest_outcomeJSON){

    otlp_ingest_outcome_t *otlp_ingest_outcome_local_var = NULL;

    // otlp_ingest_outcome->accepted_raw
    cJSON *accepted_raw = cJSON_GetObjectItemCaseSensitive(otlp_ingest_outcomeJSON, "accepted_raw");
    if (cJSON_IsNull(accepted_raw)) {
        accepted_raw = NULL;
    }
    if (!accepted_raw) {
        goto end;
    }

    
    if(!cJSON_IsNumber(accepted_raw))
    {
    goto end; //Numeric
    }

    // otlp_ingest_outcome->accepted_spans
    cJSON *accepted_spans = cJSON_GetObjectItemCaseSensitive(otlp_ingest_outcomeJSON, "accepted_spans");
    if (cJSON_IsNull(accepted_spans)) {
        accepted_spans = NULL;
    }
    if (!accepted_spans) {
        goto end;
    }

    
    if(!cJSON_IsNumber(accepted_spans))
    {
    goto end; //Numeric
    }

    // otlp_ingest_outcome->downstream_queued
    cJSON *downstream_queued = cJSON_GetObjectItemCaseSensitive(otlp_ingest_outcomeJSON, "downstream_queued");
    if (cJSON_IsNull(downstream_queued)) {
        downstream_queued = NULL;
    }
    if (!downstream_queued) {
        goto end;
    }

    
    if(!cJSON_IsBool(downstream_queued))
    {
    goto end; //Bool
    }

    // otlp_ingest_outcome->duplicate_raw
    cJSON *duplicate_raw = cJSON_GetObjectItemCaseSensitive(otlp_ingest_outcomeJSON, "duplicate_raw");
    if (cJSON_IsNull(duplicate_raw)) {
        duplicate_raw = NULL;
    }
    if (!duplicate_raw) {
        goto end;
    }

    
    if(!cJSON_IsNumber(duplicate_raw))
    {
    goto end; //Numeric
    }

    // otlp_ingest_outcome->duplicate_spans
    cJSON *duplicate_spans = cJSON_GetObjectItemCaseSensitive(otlp_ingest_outcomeJSON, "duplicate_spans");
    if (cJSON_IsNull(duplicate_spans)) {
        duplicate_spans = NULL;
    }
    if (!duplicate_spans) {
        goto end;
    }

    
    if(!cJSON_IsNumber(duplicate_spans))
    {
    goto end; //Numeric
    }


    otlp_ingest_outcome_local_var = otlp_ingest_outcome_create_internal (
        accepted_raw->valuedouble,
        accepted_spans->valuedouble,
        downstream_queued->valueint,
        duplicate_raw->valuedouble,
        duplicate_spans->valuedouble
        );

    return otlp_ingest_outcome_local_var;
end:
    return NULL;

}
