#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alert_decision.h"



static alert_decision_t *alert_decision_create_internal(
    webhook_delivery_t *delivery,
    int emitted,
    char *suppressed_reason
    ) {
    alert_decision_t *alert_decision_local_var = malloc(sizeof(alert_decision_t));
    if (!alert_decision_local_var) {
        return NULL;
    }
    alert_decision_local_var->delivery = delivery;
    alert_decision_local_var->emitted = emitted;
    alert_decision_local_var->suppressed_reason = suppressed_reason;

    alert_decision_local_var->_library_owned = 1;
    return alert_decision_local_var;
}

__attribute__((deprecated)) alert_decision_t *alert_decision_create(
    webhook_delivery_t *delivery,
    int emitted,
    char *suppressed_reason
    ) {
    return alert_decision_create_internal (
        delivery,
        emitted,
        suppressed_reason
        );
}

void alert_decision_free(alert_decision_t *alert_decision) {
    if(NULL == alert_decision){
        return ;
    }
    if(alert_decision->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "alert_decision_free");
        return ;
    }
    listEntry_t *listEntry;
    if (alert_decision->delivery) {
        webhook_delivery_free(alert_decision->delivery);
        alert_decision->delivery = NULL;
    }
    if (alert_decision->suppressed_reason) {
        free(alert_decision->suppressed_reason);
        alert_decision->suppressed_reason = NULL;
    }
    free(alert_decision);
}

cJSON *alert_decision_convertToJSON(alert_decision_t *alert_decision) {
    cJSON *item = cJSON_CreateObject();

    // alert_decision->delivery
    if(alert_decision->delivery) {
    cJSON *delivery_local_JSON = webhook_delivery_convertToJSON(alert_decision->delivery);
    if(delivery_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "delivery", delivery_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // alert_decision->emitted
    if (!alert_decision->emitted) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "emitted", alert_decision->emitted) == NULL) {
    goto fail; //Bool
    }


    // alert_decision->suppressed_reason
    if(alert_decision->suppressed_reason) {
    if(cJSON_AddStringToObject(item, "suppressed_reason", alert_decision->suppressed_reason) == NULL) {
    goto fail; //String
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

alert_decision_t *alert_decision_parseFromJSON(cJSON *alert_decisionJSON){

    alert_decision_t *alert_decision_local_var = NULL;

    // define the local variable for alert_decision->delivery
    webhook_delivery_t *delivery_local_nonprim = NULL;

    // alert_decision->delivery
    cJSON *delivery = cJSON_GetObjectItemCaseSensitive(alert_decisionJSON, "delivery");
    if (cJSON_IsNull(delivery)) {
        delivery = NULL;
    }
    if (delivery) { 
    delivery_local_nonprim = webhook_delivery_parseFromJSON(delivery); //nonprimitive
    }

    // alert_decision->emitted
    cJSON *emitted = cJSON_GetObjectItemCaseSensitive(alert_decisionJSON, "emitted");
    if (cJSON_IsNull(emitted)) {
        emitted = NULL;
    }
    if (!emitted) {
        goto end;
    }

    
    if(!cJSON_IsBool(emitted))
    {
    goto end; //Bool
    }

    // alert_decision->suppressed_reason
    cJSON *suppressed_reason = cJSON_GetObjectItemCaseSensitive(alert_decisionJSON, "suppressed_reason");
    if (cJSON_IsNull(suppressed_reason)) {
        suppressed_reason = NULL;
    }
    if (suppressed_reason) { 
    if(!cJSON_IsString(suppressed_reason) && !cJSON_IsNull(suppressed_reason))
    {
    goto end; //String
    }
    }


    alert_decision_local_var = alert_decision_create_internal (
        delivery ? delivery_local_nonprim : NULL,
        emitted->valueint,
        suppressed_reason && !cJSON_IsNull(suppressed_reason) ? strdup(suppressed_reason->valuestring) : NULL
        );

    return alert_decision_local_var;
end:
    if (delivery_local_nonprim) {
        webhook_delivery_free(delivery_local_nonprim);
        delivery_local_nonprim = NULL;
    }
    return NULL;

}
