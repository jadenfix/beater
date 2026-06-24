#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "webhook_delivery.h"



static webhook_delivery_t *webhook_delivery_create_internal(
    any_type_t *body,
    char *endpoint_url,
    list_t* headers
    ) {
    webhook_delivery_t *webhook_delivery_local_var = malloc(sizeof(webhook_delivery_t));
    if (!webhook_delivery_local_var) {
        return NULL;
    }
    webhook_delivery_local_var->body = body;
    webhook_delivery_local_var->endpoint_url = endpoint_url;
    webhook_delivery_local_var->headers = headers;

    webhook_delivery_local_var->_library_owned = 1;
    return webhook_delivery_local_var;
}

__attribute__((deprecated)) webhook_delivery_t *webhook_delivery_create(
    any_type_t *body,
    char *endpoint_url,
    list_t* headers
    ) {
    return webhook_delivery_create_internal (
        body,
        endpoint_url,
        headers
        );
}

void webhook_delivery_free(webhook_delivery_t *webhook_delivery) {
    if(NULL == webhook_delivery){
        return ;
    }
    if(webhook_delivery->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "webhook_delivery_free");
        return ;
    }
    listEntry_t *listEntry;
    if (webhook_delivery->body) {
        _free(webhook_delivery->body);
        webhook_delivery->body = NULL;
    }
    if (webhook_delivery->endpoint_url) {
        free(webhook_delivery->endpoint_url);
        webhook_delivery->endpoint_url = NULL;
    }
    if (webhook_delivery->headers) {
        list_ForEach(listEntry, webhook_delivery->headers) {
            keyValuePair_t *localKeyValue = listEntry->data;
            free (localKeyValue->key);
            free (localKeyValue->value);
            keyValuePair_free(localKeyValue);
        }
        list_freeList(webhook_delivery->headers);
        webhook_delivery->headers = NULL;
    }
    free(webhook_delivery);
}

cJSON *webhook_delivery_convertToJSON(webhook_delivery_t *webhook_delivery) {
    cJSON *item = cJSON_CreateObject();

    // webhook_delivery->body
    if (!webhook_delivery->body) {
        goto fail;
    }
    cJSON *body_local_JSON = _convertToJSON(webhook_delivery->body);
    if(body_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "body", body_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // webhook_delivery->endpoint_url
    if (!webhook_delivery->endpoint_url) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "endpoint_url", webhook_delivery->endpoint_url) == NULL) {
    goto fail; //String
    }


    // webhook_delivery->headers
    if (!webhook_delivery->headers) {
        goto fail;
    }
    cJSON *headers = cJSON_AddObjectToObject(item, "headers");
    if(headers == NULL) {
        goto fail; //primitive map container
    }
    cJSON *localMapObject = headers;
    listEntry_t *headersListEntry;
    if (webhook_delivery->headers) {
    list_ForEach(headersListEntry, webhook_delivery->headers) {
        keyValuePair_t *localKeyValue = headersListEntry->data;
        if(cJSON_AddStringToObject(localMapObject, localKeyValue->key, localKeyValue->value) == NULL)
        {
            goto fail;
        }
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

webhook_delivery_t *webhook_delivery_parseFromJSON(cJSON *webhook_deliveryJSON){

    webhook_delivery_t *webhook_delivery_local_var = NULL;

    // define the local variable for webhook_delivery->body
    _t *body_local_nonprim = NULL;

    // define the local map for webhook_delivery->headers
    list_t *headersList = NULL;

    // webhook_delivery->body
    cJSON *body = cJSON_GetObjectItemCaseSensitive(webhook_deliveryJSON, "body");
    if (cJSON_IsNull(body)) {
        body = NULL;
    }
    if (!body) {
        goto end;
    }

    
    body_local_nonprim = _parseFromJSON(body); //custom

    // webhook_delivery->endpoint_url
    cJSON *endpoint_url = cJSON_GetObjectItemCaseSensitive(webhook_deliveryJSON, "endpoint_url");
    if (cJSON_IsNull(endpoint_url)) {
        endpoint_url = NULL;
    }
    if (!endpoint_url) {
        goto end;
    }

    
    if(!cJSON_IsString(endpoint_url))
    {
    goto end; //String
    }

    // webhook_delivery->headers
    cJSON *headers = cJSON_GetObjectItemCaseSensitive(webhook_deliveryJSON, "headers");
    if (cJSON_IsNull(headers)) {
        headers = NULL;
    }
    if (!headers) {
        goto end;
    }

    
    cJSON *headers_local_map = NULL;
    if(!cJSON_IsObject(headers) && !cJSON_IsNull(headers))
    {
        goto end;//primitive map container
    }
    if(cJSON_IsObject(headers))
    {
        headersList = list_createList();
        keyValuePair_t *localMapKeyPair;
        cJSON_ArrayForEach(headers_local_map, headers)
        {
            cJSON *localMapObject = headers_local_map;
            if(!cJSON_IsString(localMapObject))
            {
                goto end;
            }
            localMapKeyPair = keyValuePair_create(strdup(localMapObject->string),strdup(localMapObject->valuestring));
            list_addElement(headersList , localMapKeyPair);
        }
    }


    webhook_delivery_local_var = webhook_delivery_create_internal (
        body_local_nonprim,
        strdup(endpoint_url->valuestring),
        headersList
        );

    return webhook_delivery_local_var;
end:
    if (body_local_nonprim) {
        _free(body_local_nonprim);
        body_local_nonprim = NULL;
    }
    if (headersList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, headersList) {
            keyValuePair_t *localKeyValue = listEntry->data;
            free(localKeyValue->key);
            localKeyValue->key = NULL;
            free(localKeyValue->value);
            localKeyValue->value = NULL;
            keyValuePair_free(localKeyValue);
            localKeyValue = NULL;
        }
        list_freeList(headersList);
        headersList = NULL;
    }
    return NULL;

}
