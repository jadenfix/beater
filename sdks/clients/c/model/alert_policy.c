#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alert_policy.h"



static alert_policy_t *alert_policy_create_internal(
    long dedupe_window_seconds,
    char *endpoint_url,
    double fire_when_score_at_or_below,
    list_t *maintenance_windows,
    char *policy_id,
    beater_api_alert_severity__e severity,
    char *signing_secret
    ) {
    alert_policy_t *alert_policy_local_var = malloc(sizeof(alert_policy_t));
    if (!alert_policy_local_var) {
        return NULL;
    }
    alert_policy_local_var->dedupe_window_seconds = dedupe_window_seconds;
    alert_policy_local_var->endpoint_url = endpoint_url;
    alert_policy_local_var->fire_when_score_at_or_below = fire_when_score_at_or_below;
    alert_policy_local_var->maintenance_windows = maintenance_windows;
    alert_policy_local_var->policy_id = policy_id;
    alert_policy_local_var->severity = severity;
    alert_policy_local_var->signing_secret = signing_secret;

    alert_policy_local_var->_library_owned = 1;
    return alert_policy_local_var;
}

__attribute__((deprecated)) alert_policy_t *alert_policy_create(
    long dedupe_window_seconds,
    char *endpoint_url,
    double fire_when_score_at_or_below,
    list_t *maintenance_windows,
    char *policy_id,
    beater_api_alert_severity__e severity,
    char *signing_secret
    ) {
    return alert_policy_create_internal (
        dedupe_window_seconds,
        endpoint_url,
        fire_when_score_at_or_below,
        maintenance_windows,
        policy_id,
        severity,
        signing_secret
        );
}

void alert_policy_free(alert_policy_t *alert_policy) {
    if(NULL == alert_policy){
        return ;
    }
    if(alert_policy->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "alert_policy_free");
        return ;
    }
    listEntry_t *listEntry;
    if (alert_policy->endpoint_url) {
        free(alert_policy->endpoint_url);
        alert_policy->endpoint_url = NULL;
    }
    if (alert_policy->maintenance_windows) {
        list_ForEach(listEntry, alert_policy->maintenance_windows) {
            maintenance_window_free(listEntry->data);
        }
        list_freeList(alert_policy->maintenance_windows);
        alert_policy->maintenance_windows = NULL;
    }
    if (alert_policy->policy_id) {
        free(alert_policy->policy_id);
        alert_policy->policy_id = NULL;
    }
    if (alert_policy->signing_secret) {
        free(alert_policy->signing_secret);
        alert_policy->signing_secret = NULL;
    }
    free(alert_policy);
}

cJSON *alert_policy_convertToJSON(alert_policy_t *alert_policy) {
    cJSON *item = cJSON_CreateObject();

    // alert_policy->dedupe_window_seconds
    if (!alert_policy->dedupe_window_seconds) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "dedupe_window_seconds", alert_policy->dedupe_window_seconds) == NULL) {
    goto fail; //Numeric
    }


    // alert_policy->endpoint_url
    if (!alert_policy->endpoint_url) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "endpoint_url", alert_policy->endpoint_url) == NULL) {
    goto fail; //String
    }


    // alert_policy->fire_when_score_at_or_below
    if (!alert_policy->fire_when_score_at_or_below) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "fire_when_score_at_or_below", alert_policy->fire_when_score_at_or_below) == NULL) {
    goto fail; //Numeric
    }


    // alert_policy->maintenance_windows
    if (!alert_policy->maintenance_windows) {
        goto fail;
    }
    cJSON *maintenance_windows = cJSON_AddArrayToObject(item, "maintenance_windows");
    if(maintenance_windows == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *maintenance_windowsListEntry;
    if (alert_policy->maintenance_windows) {
    list_ForEach(maintenance_windowsListEntry, alert_policy->maintenance_windows) {
    cJSON *itemLocal = maintenance_window_convertToJSON(maintenance_windowsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(maintenance_windows, itemLocal);
    }
    }


    // alert_policy->policy_id
    if (!alert_policy->policy_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "policy_id", alert_policy->policy_id) == NULL) {
    goto fail; //String
    }


    // alert_policy->severity
    if (beater_api_alert_severity__NULL == alert_policy->severity) {
        goto fail;
    }
    cJSON *severity_local_JSON = alert_severity_convertToJSON(alert_policy->severity);
    if(severity_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "severity", severity_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // alert_policy->signing_secret
    if (!alert_policy->signing_secret) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "signing_secret", alert_policy->signing_secret) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

alert_policy_t *alert_policy_parseFromJSON(cJSON *alert_policyJSON){

    alert_policy_t *alert_policy_local_var = NULL;

    // define the local list for alert_policy->maintenance_windows
    list_t *maintenance_windowsList = NULL;

    // define the local variable for alert_policy->severity
    beater_api_alert_severity__e severity_local_nonprim = 0;

    // alert_policy->dedupe_window_seconds
    cJSON *dedupe_window_seconds = cJSON_GetObjectItemCaseSensitive(alert_policyJSON, "dedupe_window_seconds");
    if (cJSON_IsNull(dedupe_window_seconds)) {
        dedupe_window_seconds = NULL;
    }
    if (!dedupe_window_seconds) {
        goto end;
    }

    
    if(!cJSON_IsNumber(dedupe_window_seconds))
    {
    goto end; //Numeric
    }

    // alert_policy->endpoint_url
    cJSON *endpoint_url = cJSON_GetObjectItemCaseSensitive(alert_policyJSON, "endpoint_url");
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

    // alert_policy->fire_when_score_at_or_below
    cJSON *fire_when_score_at_or_below = cJSON_GetObjectItemCaseSensitive(alert_policyJSON, "fire_when_score_at_or_below");
    if (cJSON_IsNull(fire_when_score_at_or_below)) {
        fire_when_score_at_or_below = NULL;
    }
    if (!fire_when_score_at_or_below) {
        goto end;
    }

    
    if(!cJSON_IsNumber(fire_when_score_at_or_below))
    {
    goto end; //Numeric
    }

    // alert_policy->maintenance_windows
    cJSON *maintenance_windows = cJSON_GetObjectItemCaseSensitive(alert_policyJSON, "maintenance_windows");
    if (cJSON_IsNull(maintenance_windows)) {
        maintenance_windows = NULL;
    }
    if (!maintenance_windows) {
        goto end;
    }

    
    cJSON *maintenance_windows_local_nonprimitive = NULL;
    if(!cJSON_IsArray(maintenance_windows)){
        goto end; //nonprimitive container
    }

    maintenance_windowsList = list_createList();

    cJSON_ArrayForEach(maintenance_windows_local_nonprimitive,maintenance_windows )
    {
        if(!cJSON_IsObject(maintenance_windows_local_nonprimitive)){
            goto end;
        }
        maintenance_window_t *maintenance_windowsItem = maintenance_window_parseFromJSON(maintenance_windows_local_nonprimitive);

        list_addElement(maintenance_windowsList, maintenance_windowsItem);
    }

    // alert_policy->policy_id
    cJSON *policy_id = cJSON_GetObjectItemCaseSensitive(alert_policyJSON, "policy_id");
    if (cJSON_IsNull(policy_id)) {
        policy_id = NULL;
    }
    if (!policy_id) {
        goto end;
    }

    
    if(!cJSON_IsString(policy_id))
    {
    goto end; //String
    }

    // alert_policy->severity
    cJSON *severity = cJSON_GetObjectItemCaseSensitive(alert_policyJSON, "severity");
    if (cJSON_IsNull(severity)) {
        severity = NULL;
    }
    if (!severity) {
        goto end;
    }

    
    severity_local_nonprim = alert_severity_parseFromJSON(severity); //custom

    // alert_policy->signing_secret
    cJSON *signing_secret = cJSON_GetObjectItemCaseSensitive(alert_policyJSON, "signing_secret");
    if (cJSON_IsNull(signing_secret)) {
        signing_secret = NULL;
    }
    if (!signing_secret) {
        goto end;
    }

    
    if(!cJSON_IsString(signing_secret))
    {
    goto end; //String
    }


    alert_policy_local_var = alert_policy_create_internal (
        dedupe_window_seconds->valuedouble,
        strdup(endpoint_url->valuestring),
        fire_when_score_at_or_below->valuedouble,
        maintenance_windowsList,
        strdup(policy_id->valuestring),
        severity_local_nonprim,
        strdup(signing_secret->valuestring)
        );

    return alert_policy_local_var;
end:
    if (maintenance_windowsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, maintenance_windowsList) {
            maintenance_window_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(maintenance_windowsList);
        maintenance_windowsList = NULL;
    }
    if (severity_local_nonprim) {
        severity_local_nonprim = 0;
    }
    return NULL;

}
