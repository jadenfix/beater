#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alert_links.h"



static alert_links_t *alert_links_create_internal(
    char *cluster_url,
    char *dataset_url,
    char *gate_url,
    char *trace_url
    ) {
    alert_links_t *alert_links_local_var = malloc(sizeof(alert_links_t));
    if (!alert_links_local_var) {
        return NULL;
    }
    alert_links_local_var->cluster_url = cluster_url;
    alert_links_local_var->dataset_url = dataset_url;
    alert_links_local_var->gate_url = gate_url;
    alert_links_local_var->trace_url = trace_url;

    alert_links_local_var->_library_owned = 1;
    return alert_links_local_var;
}

__attribute__((deprecated)) alert_links_t *alert_links_create(
    char *cluster_url,
    char *dataset_url,
    char *gate_url,
    char *trace_url
    ) {
    return alert_links_create_internal (
        cluster_url,
        dataset_url,
        gate_url,
        trace_url
        );
}

void alert_links_free(alert_links_t *alert_links) {
    if(NULL == alert_links){
        return ;
    }
    if(alert_links->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "alert_links_free");
        return ;
    }
    listEntry_t *listEntry;
    if (alert_links->cluster_url) {
        free(alert_links->cluster_url);
        alert_links->cluster_url = NULL;
    }
    if (alert_links->dataset_url) {
        free(alert_links->dataset_url);
        alert_links->dataset_url = NULL;
    }
    if (alert_links->gate_url) {
        free(alert_links->gate_url);
        alert_links->gate_url = NULL;
    }
    if (alert_links->trace_url) {
        free(alert_links->trace_url);
        alert_links->trace_url = NULL;
    }
    free(alert_links);
}

cJSON *alert_links_convertToJSON(alert_links_t *alert_links) {
    cJSON *item = cJSON_CreateObject();

    // alert_links->cluster_url
    if(alert_links->cluster_url) {
    if(cJSON_AddStringToObject(item, "cluster_url", alert_links->cluster_url) == NULL) {
    goto fail; //String
    }
    }


    // alert_links->dataset_url
    if(alert_links->dataset_url) {
    if(cJSON_AddStringToObject(item, "dataset_url", alert_links->dataset_url) == NULL) {
    goto fail; //String
    }
    }


    // alert_links->gate_url
    if(alert_links->gate_url) {
    if(cJSON_AddStringToObject(item, "gate_url", alert_links->gate_url) == NULL) {
    goto fail; //String
    }
    }


    // alert_links->trace_url
    if (!alert_links->trace_url) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_url", alert_links->trace_url) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

alert_links_t *alert_links_parseFromJSON(cJSON *alert_linksJSON){

    alert_links_t *alert_links_local_var = NULL;

    // alert_links->cluster_url
    cJSON *cluster_url = cJSON_GetObjectItemCaseSensitive(alert_linksJSON, "cluster_url");
    if (cJSON_IsNull(cluster_url)) {
        cluster_url = NULL;
    }
    if (cluster_url) { 
    if(!cJSON_IsString(cluster_url) && !cJSON_IsNull(cluster_url))
    {
    goto end; //String
    }
    }

    // alert_links->dataset_url
    cJSON *dataset_url = cJSON_GetObjectItemCaseSensitive(alert_linksJSON, "dataset_url");
    if (cJSON_IsNull(dataset_url)) {
        dataset_url = NULL;
    }
    if (dataset_url) { 
    if(!cJSON_IsString(dataset_url) && !cJSON_IsNull(dataset_url))
    {
    goto end; //String
    }
    }

    // alert_links->gate_url
    cJSON *gate_url = cJSON_GetObjectItemCaseSensitive(alert_linksJSON, "gate_url");
    if (cJSON_IsNull(gate_url)) {
        gate_url = NULL;
    }
    if (gate_url) { 
    if(!cJSON_IsString(gate_url) && !cJSON_IsNull(gate_url))
    {
    goto end; //String
    }
    }

    // alert_links->trace_url
    cJSON *trace_url = cJSON_GetObjectItemCaseSensitive(alert_linksJSON, "trace_url");
    if (cJSON_IsNull(trace_url)) {
        trace_url = NULL;
    }
    if (!trace_url) {
        goto end;
    }

    
    if(!cJSON_IsString(trace_url))
    {
    goto end; //String
    }


    alert_links_local_var = alert_links_create_internal (
        cluster_url && !cJSON_IsNull(cluster_url) ? strdup(cluster_url->valuestring) : NULL,
        dataset_url && !cJSON_IsNull(dataset_url) ? strdup(dataset_url->valuestring) : NULL,
        gate_url && !cJSON_IsNull(gate_url) ? strdup(gate_url->valuestring) : NULL,
        strdup(trace_url->valuestring)
        );

    return alert_links_local_var;
end:
    return NULL;

}
