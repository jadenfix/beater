#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bus_message.h"



static bus_message_t *bus_message_create_internal(
    int attempts,
    char *enqueued_at,
    char *idempotency_key,
    char *kind,
    int max_attempts,
    char *message_id,
    list_t *payload,
    char *project_id,
    char *tenant_id
    ) {
    bus_message_t *bus_message_local_var = malloc(sizeof(bus_message_t));
    if (!bus_message_local_var) {
        return NULL;
    }
    bus_message_local_var->attempts = attempts;
    bus_message_local_var->enqueued_at = enqueued_at;
    bus_message_local_var->idempotency_key = idempotency_key;
    bus_message_local_var->kind = kind;
    bus_message_local_var->max_attempts = max_attempts;
    bus_message_local_var->message_id = message_id;
    bus_message_local_var->payload = payload;
    bus_message_local_var->project_id = project_id;
    bus_message_local_var->tenant_id = tenant_id;

    bus_message_local_var->_library_owned = 1;
    return bus_message_local_var;
}

__attribute__((deprecated)) bus_message_t *bus_message_create(
    int attempts,
    char *enqueued_at,
    char *idempotency_key,
    char *kind,
    int max_attempts,
    char *message_id,
    list_t *payload,
    char *project_id,
    char *tenant_id
    ) {
    return bus_message_create_internal (
        attempts,
        enqueued_at,
        idempotency_key,
        kind,
        max_attempts,
        message_id,
        payload,
        project_id,
        tenant_id
        );
}

void bus_message_free(bus_message_t *bus_message) {
    if(NULL == bus_message){
        return ;
    }
    if(bus_message->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "bus_message_free");
        return ;
    }
    listEntry_t *listEntry;
    if (bus_message->enqueued_at) {
        free(bus_message->enqueued_at);
        bus_message->enqueued_at = NULL;
    }
    if (bus_message->idempotency_key) {
        free(bus_message->idempotency_key);
        bus_message->idempotency_key = NULL;
    }
    if (bus_message->kind) {
        free(bus_message->kind);
        bus_message->kind = NULL;
    }
    if (bus_message->message_id) {
        free(bus_message->message_id);
        bus_message->message_id = NULL;
    }
    if (bus_message->payload) {
        list_ForEach(listEntry, bus_message->payload) {
            free(listEntry->data);
        }
        list_freeList(bus_message->payload);
        bus_message->payload = NULL;
    }
    if (bus_message->project_id) {
        free(bus_message->project_id);
        bus_message->project_id = NULL;
    }
    if (bus_message->tenant_id) {
        free(bus_message->tenant_id);
        bus_message->tenant_id = NULL;
    }
    free(bus_message);
}

cJSON *bus_message_convertToJSON(bus_message_t *bus_message) {
    cJSON *item = cJSON_CreateObject();

    // bus_message->attempts
    if (!bus_message->attempts) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "attempts", bus_message->attempts) == NULL) {
    goto fail; //Numeric
    }


    // bus_message->enqueued_at
    if (!bus_message->enqueued_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "enqueued_at", bus_message->enqueued_at) == NULL) {
    goto fail; //Date-Time
    }


    // bus_message->idempotency_key
    if (!bus_message->idempotency_key) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "idempotency_key", bus_message->idempotency_key) == NULL) {
    goto fail; //String
    }


    // bus_message->kind
    if (!bus_message->kind) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "kind", bus_message->kind) == NULL) {
    goto fail; //String
    }


    // bus_message->max_attempts
    if (!bus_message->max_attempts) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "max_attempts", bus_message->max_attempts) == NULL) {
    goto fail; //Numeric
    }


    // bus_message->message_id
    if (!bus_message->message_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "message_id", bus_message->message_id) == NULL) {
    goto fail; //String
    }


    // bus_message->payload
    if (!bus_message->payload) {
        goto fail;
    }
    cJSON *payload = cJSON_AddArrayToObject(item, "payload");
    if(payload == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *payloadListEntry;
    list_ForEach(payloadListEntry, bus_message->payload) {
    if(cJSON_AddNumberToObject(payload, "", *(double *)payloadListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // bus_message->project_id
    if (!bus_message->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", bus_message->project_id) == NULL) {
    goto fail; //String
    }


    // bus_message->tenant_id
    if (!bus_message->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", bus_message->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

bus_message_t *bus_message_parseFromJSON(cJSON *bus_messageJSON){

    bus_message_t *bus_message_local_var = NULL;

    // define the local list for bus_message->payload
    list_t *payloadList = NULL;

    // bus_message->attempts
    cJSON *attempts = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "attempts");
    if (cJSON_IsNull(attempts)) {
        attempts = NULL;
    }
    if (!attempts) {
        goto end;
    }

    
    if(!cJSON_IsNumber(attempts))
    {
    goto end; //Numeric
    }

    // bus_message->enqueued_at
    cJSON *enqueued_at = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "enqueued_at");
    if (cJSON_IsNull(enqueued_at)) {
        enqueued_at = NULL;
    }
    if (!enqueued_at) {
        goto end;
    }

    
    if(!cJSON_IsString(enqueued_at) && !cJSON_IsNull(enqueued_at))
    {
    goto end; //DateTime
    }

    // bus_message->idempotency_key
    cJSON *idempotency_key = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "idempotency_key");
    if (cJSON_IsNull(idempotency_key)) {
        idempotency_key = NULL;
    }
    if (!idempotency_key) {
        goto end;
    }

    
    if(!cJSON_IsString(idempotency_key))
    {
    goto end; //String
    }

    // bus_message->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "kind");
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

    // bus_message->max_attempts
    cJSON *max_attempts = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "max_attempts");
    if (cJSON_IsNull(max_attempts)) {
        max_attempts = NULL;
    }
    if (!max_attempts) {
        goto end;
    }

    
    if(!cJSON_IsNumber(max_attempts))
    {
    goto end; //Numeric
    }

    // bus_message->message_id
    cJSON *message_id = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "message_id");
    if (cJSON_IsNull(message_id)) {
        message_id = NULL;
    }
    if (!message_id) {
        goto end;
    }

    
    if(!cJSON_IsString(message_id))
    {
    goto end; //String
    }

    // bus_message->payload
    cJSON *payload = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "payload");
    if (cJSON_IsNull(payload)) {
        payload = NULL;
    }
    if (!payload) {
        goto end;
    }

    
    cJSON *payload_local = NULL;
    if(!cJSON_IsArray(payload)) {
        goto end;//primitive container
    }
    payloadList = list_createList();

    cJSON_ArrayForEach(payload_local, payload)
    {
        if(!cJSON_IsNumber(payload_local))
        {
            goto end;
        }
        double *payload_local_value = calloc(1, sizeof(double));
        if(!payload_local_value)
        {
            goto end;
        }
        *payload_local_value = payload_local->valuedouble;
        list_addElement(payloadList , payload_local_value);
    }

    // bus_message->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "project_id");
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

    // bus_message->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(bus_messageJSON, "tenant_id");
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


    bus_message_local_var = bus_message_create_internal (
        attempts->valuedouble,
        strdup(enqueued_at->valuestring),
        strdup(idempotency_key->valuestring),
        strdup(kind->valuestring),
        max_attempts->valuedouble,
        strdup(message_id->valuestring),
        payloadList,
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring)
        );

    return bus_message_local_var;
end:
    if (payloadList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, payloadList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(payloadList);
        payloadList = NULL;
    }
    return NULL;

}
