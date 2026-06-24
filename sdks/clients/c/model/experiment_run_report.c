#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "experiment_run_report.h"



static experiment_run_report_t *experiment_run_report_create_internal(
    char *baseline_release_id,
    char *candidate_release_id,
    list_t *case_scores,
    experiment_comparison_t *comparison,
    char *created_at,
    char *dataset_id,
    char *dataset_version_id,
    beater_api_gate_decision__e decision,
    char *evaluator_version_id,
    char *experiment_run_id,
    gate_policy_t *gate_policy,
    char *project_id,
    char *tenant_id
    ) {
    experiment_run_report_t *experiment_run_report_local_var = malloc(sizeof(experiment_run_report_t));
    if (!experiment_run_report_local_var) {
        return NULL;
    }
    experiment_run_report_local_var->baseline_release_id = baseline_release_id;
    experiment_run_report_local_var->candidate_release_id = candidate_release_id;
    experiment_run_report_local_var->case_scores = case_scores;
    experiment_run_report_local_var->comparison = comparison;
    experiment_run_report_local_var->created_at = created_at;
    experiment_run_report_local_var->dataset_id = dataset_id;
    experiment_run_report_local_var->dataset_version_id = dataset_version_id;
    experiment_run_report_local_var->decision = decision;
    experiment_run_report_local_var->evaluator_version_id = evaluator_version_id;
    experiment_run_report_local_var->experiment_run_id = experiment_run_id;
    experiment_run_report_local_var->gate_policy = gate_policy;
    experiment_run_report_local_var->project_id = project_id;
    experiment_run_report_local_var->tenant_id = tenant_id;

    experiment_run_report_local_var->_library_owned = 1;
    return experiment_run_report_local_var;
}

__attribute__((deprecated)) experiment_run_report_t *experiment_run_report_create(
    char *baseline_release_id,
    char *candidate_release_id,
    list_t *case_scores,
    experiment_comparison_t *comparison,
    char *created_at,
    char *dataset_id,
    char *dataset_version_id,
    beater_api_gate_decision__e decision,
    char *evaluator_version_id,
    char *experiment_run_id,
    gate_policy_t *gate_policy,
    char *project_id,
    char *tenant_id
    ) {
    return experiment_run_report_create_internal (
        baseline_release_id,
        candidate_release_id,
        case_scores,
        comparison,
        created_at,
        dataset_id,
        dataset_version_id,
        decision,
        evaluator_version_id,
        experiment_run_id,
        gate_policy,
        project_id,
        tenant_id
        );
}

void experiment_run_report_free(experiment_run_report_t *experiment_run_report) {
    if(NULL == experiment_run_report){
        return ;
    }
    if(experiment_run_report->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "experiment_run_report_free");
        return ;
    }
    listEntry_t *listEntry;
    if (experiment_run_report->baseline_release_id) {
        free(experiment_run_report->baseline_release_id);
        experiment_run_report->baseline_release_id = NULL;
    }
    if (experiment_run_report->candidate_release_id) {
        free(experiment_run_report->candidate_release_id);
        experiment_run_report->candidate_release_id = NULL;
    }
    if (experiment_run_report->case_scores) {
        list_ForEach(listEntry, experiment_run_report->case_scores) {
            case_experiment_score_free(listEntry->data);
        }
        list_freeList(experiment_run_report->case_scores);
        experiment_run_report->case_scores = NULL;
    }
    if (experiment_run_report->comparison) {
        experiment_comparison_free(experiment_run_report->comparison);
        experiment_run_report->comparison = NULL;
    }
    if (experiment_run_report->created_at) {
        free(experiment_run_report->created_at);
        experiment_run_report->created_at = NULL;
    }
    if (experiment_run_report->dataset_id) {
        free(experiment_run_report->dataset_id);
        experiment_run_report->dataset_id = NULL;
    }
    if (experiment_run_report->dataset_version_id) {
        free(experiment_run_report->dataset_version_id);
        experiment_run_report->dataset_version_id = NULL;
    }
    if (experiment_run_report->evaluator_version_id) {
        free(experiment_run_report->evaluator_version_id);
        experiment_run_report->evaluator_version_id = NULL;
    }
    if (experiment_run_report->experiment_run_id) {
        free(experiment_run_report->experiment_run_id);
        experiment_run_report->experiment_run_id = NULL;
    }
    if (experiment_run_report->gate_policy) {
        gate_policy_free(experiment_run_report->gate_policy);
        experiment_run_report->gate_policy = NULL;
    }
    if (experiment_run_report->project_id) {
        free(experiment_run_report->project_id);
        experiment_run_report->project_id = NULL;
    }
    if (experiment_run_report->tenant_id) {
        free(experiment_run_report->tenant_id);
        experiment_run_report->tenant_id = NULL;
    }
    free(experiment_run_report);
}

cJSON *experiment_run_report_convertToJSON(experiment_run_report_t *experiment_run_report) {
    cJSON *item = cJSON_CreateObject();

    // experiment_run_report->baseline_release_id
    if (!experiment_run_report->baseline_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "baseline_release_id", experiment_run_report->baseline_release_id) == NULL) {
    goto fail; //String
    }


    // experiment_run_report->candidate_release_id
    if (!experiment_run_report->candidate_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "candidate_release_id", experiment_run_report->candidate_release_id) == NULL) {
    goto fail; //String
    }


    // experiment_run_report->case_scores
    if (!experiment_run_report->case_scores) {
        goto fail;
    }
    cJSON *case_scores = cJSON_AddArrayToObject(item, "case_scores");
    if(case_scores == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *case_scoresListEntry;
    if (experiment_run_report->case_scores) {
    list_ForEach(case_scoresListEntry, experiment_run_report->case_scores) {
    cJSON *itemLocal = case_experiment_score_convertToJSON(case_scoresListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(case_scores, itemLocal);
    }
    }


    // experiment_run_report->comparison
    if (!experiment_run_report->comparison) {
        goto fail;
    }
    cJSON *comparison_local_JSON = experiment_comparison_convertToJSON(experiment_run_report->comparison);
    if(comparison_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "comparison", comparison_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // experiment_run_report->created_at
    if (!experiment_run_report->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", experiment_run_report->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // experiment_run_report->dataset_id
    if (!experiment_run_report->dataset_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_id", experiment_run_report->dataset_id) == NULL) {
    goto fail; //String
    }


    // experiment_run_report->dataset_version_id
    if (!experiment_run_report->dataset_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_version_id", experiment_run_report->dataset_version_id) == NULL) {
    goto fail; //String
    }


    // experiment_run_report->decision
    if (beater_api_gate_decision__NULL == experiment_run_report->decision) {
        goto fail;
    }
    cJSON *decision_local_JSON = gate_decision_convertToJSON(experiment_run_report->decision);
    if(decision_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "decision", decision_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // experiment_run_report->evaluator_version_id
    if (!experiment_run_report->evaluator_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_version_id", experiment_run_report->evaluator_version_id) == NULL) {
    goto fail; //String
    }


    // experiment_run_report->experiment_run_id
    if (!experiment_run_report->experiment_run_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "experiment_run_id", experiment_run_report->experiment_run_id) == NULL) {
    goto fail; //String
    }


    // experiment_run_report->gate_policy
    if(experiment_run_report->gate_policy) {
    cJSON *gate_policy_local_JSON = gate_policy_convertToJSON(experiment_run_report->gate_policy);
    if(gate_policy_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "gate_policy", gate_policy_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // experiment_run_report->project_id
    if (!experiment_run_report->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", experiment_run_report->project_id) == NULL) {
    goto fail; //String
    }


    // experiment_run_report->tenant_id
    if (!experiment_run_report->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", experiment_run_report->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

experiment_run_report_t *experiment_run_report_parseFromJSON(cJSON *experiment_run_reportJSON){

    experiment_run_report_t *experiment_run_report_local_var = NULL;

    // define the local list for experiment_run_report->case_scores
    list_t *case_scoresList = NULL;

    // define the local variable for experiment_run_report->comparison
    experiment_comparison_t *comparison_local_nonprim = NULL;

    // define the local variable for experiment_run_report->decision
    beater_api_gate_decision__e decision_local_nonprim = 0;

    // define the local variable for experiment_run_report->gate_policy
    gate_policy_t *gate_policy_local_nonprim = NULL;

    // experiment_run_report->baseline_release_id
    cJSON *baseline_release_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "baseline_release_id");
    if (cJSON_IsNull(baseline_release_id)) {
        baseline_release_id = NULL;
    }
    if (!baseline_release_id) {
        goto end;
    }

    
    if(!cJSON_IsString(baseline_release_id))
    {
    goto end; //String
    }

    // experiment_run_report->candidate_release_id
    cJSON *candidate_release_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "candidate_release_id");
    if (cJSON_IsNull(candidate_release_id)) {
        candidate_release_id = NULL;
    }
    if (!candidate_release_id) {
        goto end;
    }

    
    if(!cJSON_IsString(candidate_release_id))
    {
    goto end; //String
    }

    // experiment_run_report->case_scores
    cJSON *case_scores = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "case_scores");
    if (cJSON_IsNull(case_scores)) {
        case_scores = NULL;
    }
    if (!case_scores) {
        goto end;
    }

    
    cJSON *case_scores_local_nonprimitive = NULL;
    if(!cJSON_IsArray(case_scores)){
        goto end; //nonprimitive container
    }

    case_scoresList = list_createList();

    cJSON_ArrayForEach(case_scores_local_nonprimitive,case_scores )
    {
        if(!cJSON_IsObject(case_scores_local_nonprimitive)){
            goto end;
        }
        case_experiment_score_t *case_scoresItem = case_experiment_score_parseFromJSON(case_scores_local_nonprimitive);

        list_addElement(case_scoresList, case_scoresItem);
    }

    // experiment_run_report->comparison
    cJSON *comparison = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "comparison");
    if (cJSON_IsNull(comparison)) {
        comparison = NULL;
    }
    if (!comparison) {
        goto end;
    }

    
    comparison_local_nonprim = experiment_comparison_parseFromJSON(comparison); //nonprimitive

    // experiment_run_report->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "created_at");
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

    // experiment_run_report->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "dataset_id");
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

    // experiment_run_report->dataset_version_id
    cJSON *dataset_version_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "dataset_version_id");
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

    // experiment_run_report->decision
    cJSON *decision = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "decision");
    if (cJSON_IsNull(decision)) {
        decision = NULL;
    }
    if (!decision) {
        goto end;
    }

    
    decision_local_nonprim = gate_decision_parseFromJSON(decision); //custom

    // experiment_run_report->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "evaluator_version_id");
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

    // experiment_run_report->experiment_run_id
    cJSON *experiment_run_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "experiment_run_id");
    if (cJSON_IsNull(experiment_run_id)) {
        experiment_run_id = NULL;
    }
    if (!experiment_run_id) {
        goto end;
    }

    
    if(!cJSON_IsString(experiment_run_id))
    {
    goto end; //String
    }

    // experiment_run_report->gate_policy
    cJSON *gate_policy = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "gate_policy");
    if (cJSON_IsNull(gate_policy)) {
        gate_policy = NULL;
    }
    if (gate_policy) { 
    gate_policy_local_nonprim = gate_policy_parseFromJSON(gate_policy); //nonprimitive
    }

    // experiment_run_report->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "project_id");
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

    // experiment_run_report->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(experiment_run_reportJSON, "tenant_id");
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


    experiment_run_report_local_var = experiment_run_report_create_internal (
        strdup(baseline_release_id->valuestring),
        strdup(candidate_release_id->valuestring),
        case_scoresList,
        comparison_local_nonprim,
        strdup(created_at->valuestring),
        strdup(dataset_id->valuestring),
        strdup(dataset_version_id->valuestring),
        decision_local_nonprim,
        strdup(evaluator_version_id->valuestring),
        strdup(experiment_run_id->valuestring),
        gate_policy ? gate_policy_local_nonprim : NULL,
        strdup(project_id->valuestring),
        strdup(tenant_id->valuestring)
        );

    return experiment_run_report_local_var;
end:
    if (case_scoresList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, case_scoresList) {
            case_experiment_score_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(case_scoresList);
        case_scoresList = NULL;
    }
    if (comparison_local_nonprim) {
        experiment_comparison_free(comparison_local_nonprim);
        comparison_local_nonprim = NULL;
    }
    if (decision_local_nonprim) {
        decision_local_nonprim = 0;
    }
    if (gate_policy_local_nonprim) {
        gate_policy_free(gate_policy_local_nonprim);
        gate_policy_local_nonprim = NULL;
    }
    return NULL;

}
