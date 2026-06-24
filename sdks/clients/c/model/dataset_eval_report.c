#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dataset_eval_report.h"



static dataset_eval_report_t *dataset_eval_report_create_internal(
    double aggregate_score,
    char *created_at,
    char *dataset_id,
    char *dataset_version_id,
    char *evaluator_version_id,
    char *project_id,
    char *report_id,
    int result_count,
    list_t *results,
    char *tenant_id
    ) {
    dataset_eval_report_t *dataset_eval_report_local_var = malloc(sizeof(dataset_eval_report_t));
    if (!dataset_eval_report_local_var) {
        return NULL;
    }
    dataset_eval_report_local_var->aggregate_score = aggregate_score;
    dataset_eval_report_local_var->created_at = created_at;
    dataset_eval_report_local_var->dataset_id = dataset_id;
    dataset_eval_report_local_var->dataset_version_id = dataset_version_id;
    dataset_eval_report_local_var->evaluator_version_id = evaluator_version_id;
    dataset_eval_report_local_var->project_id = project_id;
    dataset_eval_report_local_var->report_id = report_id;
    dataset_eval_report_local_var->result_count = result_count;
    dataset_eval_report_local_var->results = results;
    dataset_eval_report_local_var->tenant_id = tenant_id;

    dataset_eval_report_local_var->_library_owned = 1;
    return dataset_eval_report_local_var;
}

__attribute__((deprecated)) dataset_eval_report_t *dataset_eval_report_create(
    double aggregate_score,
    char *created_at,
    char *dataset_id,
    char *dataset_version_id,
    char *evaluator_version_id,
    char *project_id,
    char *report_id,
    int result_count,
    list_t *results,
    char *tenant_id
    ) {
    return dataset_eval_report_create_internal (
        aggregate_score,
        created_at,
        dataset_id,
        dataset_version_id,
        evaluator_version_id,
        project_id,
        report_id,
        result_count,
        results,
        tenant_id
        );
}

void dataset_eval_report_free(dataset_eval_report_t *dataset_eval_report) {
    if(NULL == dataset_eval_report){
        return ;
    }
    if(dataset_eval_report->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "dataset_eval_report_free");
        return ;
    }
    listEntry_t *listEntry;
    if (dataset_eval_report->created_at) {
        free(dataset_eval_report->created_at);
        dataset_eval_report->created_at = NULL;
    }
    if (dataset_eval_report->dataset_id) {
        free(dataset_eval_report->dataset_id);
        dataset_eval_report->dataset_id = NULL;
    }
    if (dataset_eval_report->dataset_version_id) {
        free(dataset_eval_report->dataset_version_id);
        dataset_eval_report->dataset_version_id = NULL;
    }
    if (dataset_eval_report->evaluator_version_id) {
        free(dataset_eval_report->evaluator_version_id);
        dataset_eval_report->evaluator_version_id = NULL;
    }
    if (dataset_eval_report->project_id) {
        free(dataset_eval_report->project_id);
        dataset_eval_report->project_id = NULL;
    }
    if (dataset_eval_report->report_id) {
        free(dataset_eval_report->report_id);
        dataset_eval_report->report_id = NULL;
    }
    if (dataset_eval_report->results) {
        list_ForEach(listEntry, dataset_eval_report->results) {
            eval_result_free(listEntry->data);
        }
        list_freeList(dataset_eval_report->results);
        dataset_eval_report->results = NULL;
    }
    if (dataset_eval_report->tenant_id) {
        free(dataset_eval_report->tenant_id);
        dataset_eval_report->tenant_id = NULL;
    }
    free(dataset_eval_report);
}

cJSON *dataset_eval_report_convertToJSON(dataset_eval_report_t *dataset_eval_report) {
    cJSON *item = cJSON_CreateObject();

    // dataset_eval_report->aggregate_score
    if (!dataset_eval_report->aggregate_score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "aggregate_score", dataset_eval_report->aggregate_score) == NULL) {
    goto fail; //Numeric
    }


    // dataset_eval_report->created_at
    if (!dataset_eval_report->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", dataset_eval_report->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // dataset_eval_report->dataset_id
    if (!dataset_eval_report->dataset_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_id", dataset_eval_report->dataset_id) == NULL) {
    goto fail; //String
    }


    // dataset_eval_report->dataset_version_id
    if (!dataset_eval_report->dataset_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_version_id", dataset_eval_report->dataset_version_id) == NULL) {
    goto fail; //String
    }


    // dataset_eval_report->evaluator_version_id
    if (!dataset_eval_report->evaluator_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_version_id", dataset_eval_report->evaluator_version_id) == NULL) {
    goto fail; //String
    }


    // dataset_eval_report->project_id
    if (!dataset_eval_report->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", dataset_eval_report->project_id) == NULL) {
    goto fail; //String
    }


    // dataset_eval_report->report_id
    if (!dataset_eval_report->report_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "report_id", dataset_eval_report->report_id) == NULL) {
    goto fail; //String
    }


    // dataset_eval_report->result_count
    if (!dataset_eval_report->result_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "result_count", dataset_eval_report->result_count) == NULL) {
    goto fail; //Numeric
    }


    // dataset_eval_report->results
    if (!dataset_eval_report->results) {
        goto fail;
    }
    cJSON *results = cJSON_AddArrayToObject(item, "results");
    if(results == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *resultsListEntry;
    if (dataset_eval_report->results) {
    list_ForEach(resultsListEntry, dataset_eval_report->results) {
    cJSON *itemLocal = eval_result_convertToJSON(resultsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(results, itemLocal);
    }
    }


    // dataset_eval_report->tenant_id
    if (!dataset_eval_report->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", dataset_eval_report->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

dataset_eval_report_t *dataset_eval_report_parseFromJSON(cJSON *dataset_eval_reportJSON){

    dataset_eval_report_t *dataset_eval_report_local_var = NULL;

    // define the local list for dataset_eval_report->results
    list_t *resultsList = NULL;

    // dataset_eval_report->aggregate_score
    cJSON *aggregate_score = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "aggregate_score");
    if (cJSON_IsNull(aggregate_score)) {
        aggregate_score = NULL;
    }
    if (!aggregate_score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(aggregate_score))
    {
    goto end; //Numeric
    }

    // dataset_eval_report->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "created_at");
    if (cJSON_IsNull(created_at)) {
        created_at = NULL;
    }
    if (!created_at) {
        goto end;
    }

    
    if(!cJSON_IsString(created_at) && !cJSON_IsNull(created_at))
    {
    goto end; //DateTime
    }

    // dataset_eval_report->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "dataset_id");
    if (cJSON_IsNull(dataset_id)) {
        dataset_id = NULL;
    }
    if (!dataset_id) {
        goto end;
    }

    
    if(!cJSON_IsString(dataset_id))
    {
    goto end; //String
    }

    // dataset_eval_report->dataset_version_id
    cJSON *dataset_version_id = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "dataset_version_id");
    if (cJSON_IsNull(dataset_version_id)) {
        dataset_version_id = NULL;
    }
    if (!dataset_version_id) {
        goto end;
    }

    
    if(!cJSON_IsString(dataset_version_id))
    {
    goto end; //String
    }

    // dataset_eval_report->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "evaluator_version_id");
    if (cJSON_IsNull(evaluator_version_id)) {
        evaluator_version_id = NULL;
    }
    if (!evaluator_version_id) {
        goto end;
    }

    
    if(!cJSON_IsString(evaluator_version_id))
    {
    goto end; //String
    }

    // dataset_eval_report->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "project_id");
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

    // dataset_eval_report->report_id
    cJSON *report_id = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "report_id");
    if (cJSON_IsNull(report_id)) {
        report_id = NULL;
    }
    if (!report_id) {
        goto end;
    }

    
    if(!cJSON_IsString(report_id))
    {
    goto end; //String
    }

    // dataset_eval_report->result_count
    cJSON *result_count = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "result_count");
    if (cJSON_IsNull(result_count)) {
        result_count = NULL;
    }
    if (!result_count) {
        goto end;
    }

    
    if(!cJSON_IsNumber(result_count))
    {
    goto end; //Numeric
    }

    // dataset_eval_report->results
    cJSON *results = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "results");
    if (cJSON_IsNull(results)) {
        results = NULL;
    }
    if (!results) {
        goto end;
    }

    
    cJSON *results_local_nonprimitive = NULL;
    if(!cJSON_IsArray(results)){
        goto end; //nonprimitive container
    }

    resultsList = list_createList();

    cJSON_ArrayForEach(results_local_nonprimitive,results )
    {
        if(!cJSON_IsObject(results_local_nonprimitive)){
            goto end;
        }
        eval_result_t *resultsItem = eval_result_parseFromJSON(results_local_nonprimitive);

        list_addElement(resultsList, resultsItem);
    }

    // dataset_eval_report->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(dataset_eval_reportJSON, "tenant_id");
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


    dataset_eval_report_local_var = dataset_eval_report_create_internal (
        aggregate_score->valuedouble,
        strdup(created_at->valuestring),
        strdup(dataset_id->valuestring),
        strdup(dataset_version_id->valuestring),
        strdup(evaluator_version_id->valuestring),
        strdup(project_id->valuestring),
        strdup(report_id->valuestring),
        result_count->valuedouble,
        resultsList,
        strdup(tenant_id->valuestring)
        );

    return dataset_eval_report_local_var;
end:
    if (resultsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, resultsList) {
            eval_result_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(resultsList);
        resultsList = NULL;
    }
    return NULL;

}
