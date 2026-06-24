#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ingest_outcome.h"



static ingest_outcome_t *ingest_outcome_create_internal(
    write_ack_t *ack,
    int downstream_queued
    ) {
    ingest_outcome_t *ingest_outcome_local_var = malloc(sizeof(ingest_outcome_t));
    if (!ingest_outcome_local_var) {
        return NULL;
    }
    ingest_outcome_local_var->ack = ack;
    ingest_outcome_local_var->downstream_queued = downstream_queued;

    ingest_outcome_local_var->_library_owned = 1;
    return ingest_outcome_local_var;
}

__attribute__((deprecated)) ingest_outcome_t *ingest_outcome_create(
    write_ack_t *ack,
    int downstream_queued
    ) {
    return ingest_outcome_create_internal (
        ack,
        downstream_queued
        );
}

void ingest_outcome_free(ingest_outcome_t *ingest_outcome) {
    if(NULL == ingest_outcome){
        return ;
    }
    if(ingest_outcome->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "ingest_outcome_free");
        return ;
    }
    listEntry_t *listEntry;
    if (ingest_outcome->ack) {
        write_ack_free(ingest_outcome->ack);
        ingest_outcome->ack = NULL;
    }
    free(ingest_outcome);
}

cJSON *ingest_outcome_convertToJSON(ingest_outcome_t *ingest_outcome) {
    cJSON *item = cJSON_CreateObject();

    // ingest_outcome->ack
    if (!ingest_outcome->ack) {
        goto fail;
    }
    cJSON *ack_local_JSON = write_ack_convertToJSON(ingest_outcome->ack);
    if(ack_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "ack", ack_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // ingest_outcome->downstream_queued
    if (!ingest_outcome->downstream_queued) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "downstream_queued", ingest_outcome->downstream_queued) == NULL) {
    goto fail; //Bool
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ingest_outcome_t *ingest_outcome_parseFromJSON(cJSON *ingest_outcomeJSON){

    ingest_outcome_t *ingest_outcome_local_var = NULL;

    // define the local variable for ingest_outcome->ack
    write_ack_t *ack_local_nonprim = NULL;

    // ingest_outcome->ack
    cJSON *ack = cJSON_GetObjectItemCaseSensitive(ingest_outcomeJSON, "ack");
    if (cJSON_IsNull(ack)) {
        ack = NULL;
    }
    if (!ack) {
        goto end;
    }

    
    ack_local_nonprim = write_ack_parseFromJSON(ack); //nonprimitive

    // ingest_outcome->downstream_queued
    cJSON *downstream_queued = cJSON_GetObjectItemCaseSensitive(ingest_outcomeJSON, "downstream_queued");
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


    ingest_outcome_local_var = ingest_outcome_create_internal (
        ack_local_nonprim,
        downstream_queued->valueint
        );

    return ingest_outcome_local_var;
end:
    if (ack_local_nonprim) {
        write_ack_free(ack_local_nonprim);
        ack_local_nonprim = NULL;
    }
    return NULL;

}
