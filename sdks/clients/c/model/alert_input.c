#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alert_input.h"



static alert_input_t *alert_input_create_internal(
    double baseline_score,
    char *group_key,
    alert_links_t *links,
    char *now,
    char *project_id,
    double score,
    char *tenant_id,
    char *title,
    char *trace_id
    ) {
    alert_input_t *alert_input_local_var = malloc(sizeof(alert_input_t));
    if (!alert_input_local_var) {
        return NULL;
    }
    alert_input_local_var->baseline_score = baseline_score;
    alert_input_local_var->group_key = group_key;
    alert_input_local_var->links = links;
    alert_input_local_var->now = now;
    alert_input_local_var->project_id = project_id;
    alert_input_local_var->score = score;
    alert_input_local_var->tenant_id = tenant_id;
    alert_input_local_var->title = title;
    alert_input_local_var->trace_id = trace_id;

    alert_input_local_var->_library_owned = 1;
    return alert_input_local_var;
}

__attribute__((deprecated)) alert_input_t *alert_input_create(
    double baseline_score,
    char *group_key,
    alert_links_t *links,
    char *now,
    char *project_id,
    double score,
    char *tenant_id,
    char *title,
    char *trace_id
    ) {
    return alert_input_create_internal (
        baseline_score,
        group_key,
        links,
        now,
        project_id,
        score,
        tenant_id,
        title,
        trace_id
        );
}

void alert_input_free(alert_input_t *alert_input) {
    if(NULL == alert_input){
        return ;
    }
    if(alert_input->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "alert_input_free");
        return ;
    }
    listEntry_t *listEntry;
    if (alert_input->group_key) {
        free(alert_input->group_key);
        alert_input->group_key = NULL;
    }
    if (alert_input->links) {
        alert_links_free(alert_input->links);
        alert_input->links = NULL;
    }
    if (alert_input->now) {
        free(alert_input->now);
        alert_input->now = NULL;
    }
    if (alert_input->project_id) {
        free(alert_input->project_id);
        alert_input->project_id = NULL;
    }
    if (alert_input->tenant_id) {
        free(alert_input->tenant_id);
        alert_input->tenant_id = NULL;
    }
    if (alert_input->title) {
        free(alert_input->title);
        alert_input->title = NULL;
    }
    if (alert_input->trace_id) {
        free(alert_input->trace_id);
        alert_input->trace_id = NULL;
    }
    free(alert_input);
}

cJSON *alert_input_convertToJSON(alert_input_t *alert_input) {
    cJSON *item = cJSON_CreateObject();

    // alert_input->baseline_score
    if(alert_input->baseline_score) {
    if(cJSON_AddNumberToObject(item, "baseline_score", alert_input->baseline_score) == NULL) {
    goto fail; //Numeric
    }
    }


    // alert_input->group_key
    if (!alert_input->group_key) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "group_key", alert_input->group_key) == NULL) {
    goto fail; //String
    }


    // alert_input->links
    if (!alert_input->links) {
        goto fail;
    }
    cJSON *links_local_JSON = alert_links_convertToJSON(alert_input->links);
    if(links_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "links", links_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // alert_input->now
    if (!alert_input->now) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "now", alert_input->now) == NULL) {
    goto fail; //Date-Time
    }


    // alert_input->project_id
    if (!alert_input->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", alert_input->project_id) == NULL) {
    goto fail; //String
    }


    // alert_input->score
    if (!alert_input->score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "score", alert_input->score) == NULL) {
    goto fail; //Numeric
    }


    // alert_input->tenant_id
    if (!alert_input->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", alert_input->tenant_id) == NULL) {
    goto fail; //String
    }


    // alert_input->title
    if (!alert_input->title) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "title", alert_input->title) == NULL) {
    goto fail; //String
    }


    // alert_input->trace_id
    if (!alert_input->trace_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "trace_id", alert_input->trace_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

alert_input_t *alert_input_parseFromJSON(cJSON *alert_inputJSON){

    alert_input_t *alert_input_local_var = NULL;

    // define the local variable for alert_input->links
    alert_links_t *links_local_nonprim = NULL;

    // alert_input->baseline_score
    cJSON *baseline_score = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "baseline_score");
    if (cJSON_IsNull(baseline_score)) {
        baseline_score = NULL;
    }
    if (baseline_score) { 
    if(!cJSON_IsNumber(baseline_score))
    {
    goto end; //Numeric
    }
    }

    // alert_input->group_key
    cJSON *group_key = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "group_key");
    if (cJSON_IsNull(group_key)) {
        group_key = NULL;
    }
    if (!group_key) {
        goto end;
    }

    
    if(!cJSON_IsString(group_key))
    {
    goto end; //String
    }

    // alert_input->links
    cJSON *links = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "links");
    if (cJSON_IsNull(links)) {
        links = NULL;
    }
    if (!links) {
        goto end;
    }

    
    links_local_nonprim = alert_links_parseFromJSON(links); //nonprimitive

    // alert_input->now
    cJSON *now = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "now");
    if (cJSON_IsNull(now)) {
        now = NULL;
    }
    if (!now) {
        goto end;
    }

    
    if(!cJSON_IsString(now) && !cJSON_IsNull(now))
    {
    goto end; //DateTime
    }

    // alert_input->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "project_id");
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

    // alert_input->score
    cJSON *score = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "score");
    if (cJSON_IsNull(score)) {
        score = NULL;
    }
    if (!score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(score))
    {
    goto end; //Numeric
    }

    // alert_input->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "tenant_id");
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

    // alert_input->title
    cJSON *title = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "title");
    if (cJSON_IsNull(title)) {
        title = NULL;
    }
    if (!title) {
        goto end;
    }

    
    if(!cJSON_IsString(title))
    {
    goto end; //String
    }

    // alert_input->trace_id
    cJSON *trace_id = cJSON_GetObjectItemCaseSensitive(alert_inputJSON, "trace_id");
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


    alert_input_local_var = alert_input_create_internal (
        baseline_score ? baseline_score->valuedouble : 0,
        strdup(group_key->valuestring),
        links_local_nonprim,
        strdup(now->valuestring),
        strdup(project_id->valuestring),
        score->valuedouble,
        strdup(tenant_id->valuestring),
        strdup(title->valuestring),
        strdup(trace_id->valuestring)
        );

    return alert_input_local_var;
end:
    if (links_local_nonprim) {
        alert_links_free(links_local_nonprim);
        links_local_nonprim = NULL;
    }
    return NULL;

}
