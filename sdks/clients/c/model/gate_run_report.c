#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gate_run_report.h"



static gate_run_report_t *gate_run_report_create_internal(
    char *baseline_release_id,
    char *candidate_release_id,
    experiment_comparison_t *comparison,
    char *created_at,
    char *dataset_id,
    char *evaluator_version_id,
    char *experiment_created_at,
    beater_api_gate_decision__e experiment_decision,
    gate_policy_t *experiment_gate_policy,
    char *experiment_run_id,
    char *gate_dataset_id,
    char *gate_evaluator_version_id,
    char *gate_id,
    char *gate_name,
    char *gate_run_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    int passed,
    char *project_id,
    char *reason,
    char *tenant_id
    ) {
    gate_run_report_t *gate_run_report_local_var = malloc(sizeof(gate_run_report_t));
    if (!gate_run_report_local_var) {
        return NULL;
    }
    gate_run_report_local_var->baseline_release_id = baseline_release_id;
    gate_run_report_local_var->candidate_release_id = candidate_release_id;
    gate_run_report_local_var->comparison = comparison;
    gate_run_report_local_var->created_at = created_at;
    gate_run_report_local_var->dataset_id = dataset_id;
    gate_run_report_local_var->evaluator_version_id = evaluator_version_id;
    gate_run_report_local_var->experiment_created_at = experiment_created_at;
    gate_run_report_local_var->experiment_decision = experiment_decision;
    gate_run_report_local_var->experiment_gate_policy = experiment_gate_policy;
    gate_run_report_local_var->experiment_run_id = experiment_run_id;
    gate_run_report_local_var->gate_dataset_id = gate_dataset_id;
    gate_run_report_local_var->gate_evaluator_version_id = gate_evaluator_version_id;
    gate_run_report_local_var->gate_id = gate_id;
    gate_run_report_local_var->gate_name = gate_name;
    gate_run_report_local_var->gate_run_id = gate_run_id;
    gate_run_report_local_var->inconclusive_policy = inconclusive_policy;
    gate_run_report_local_var->passed = passed;
    gate_run_report_local_var->project_id = project_id;
    gate_run_report_local_var->reason = reason;
    gate_run_report_local_var->tenant_id = tenant_id;

    gate_run_report_local_var->_library_owned = 1;
    return gate_run_report_local_var;
}

__attribute__((deprecated)) gate_run_report_t *gate_run_report_create(
    char *baseline_release_id,
    char *candidate_release_id,
    experiment_comparison_t *comparison,
    char *created_at,
    char *dataset_id,
    char *evaluator_version_id,
    char *experiment_created_at,
    beater_api_gate_decision__e experiment_decision,
    gate_policy_t *experiment_gate_policy,
    char *experiment_run_id,
    char *gate_dataset_id,
    char *gate_evaluator_version_id,
    char *gate_id,
    char *gate_name,
    char *gate_run_id,
    beater_api_inconclusive_policy__e inconclusive_policy,
    int passed,
    char *project_id,
    char *reason,
    char *tenant_id
    ) {
    return gate_run_report_create_internal (
        baseline_release_id,
        candidate_release_id,
        comparison,
        created_at,
        dataset_id,
        evaluator_version_id,
        experiment_created_at,
        experiment_decision,
        experiment_gate_policy,
        experiment_run_id,
        gate_dataset_id,
        gate_evaluator_version_id,
        gate_id,
        gate_name,
        gate_run_id,
        inconclusive_policy,
        passed,
        project_id,
        reason,
        tenant_id
        );
}

void gate_run_report_free(gate_run_report_t *gate_run_report) {
    if(NULL == gate_run_report){
        return ;
    }
    if(gate_run_report->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "gate_run_report_free");
        return ;
    }
    listEntry_t *listEntry;
    if (gate_run_report->baseline_release_id) {
        free(gate_run_report->baseline_release_id);
        gate_run_report->baseline_release_id = NULL;
    }
    if (gate_run_report->candidate_release_id) {
        free(gate_run_report->candidate_release_id);
        gate_run_report->candidate_release_id = NULL;
    }
    if (gate_run_report->comparison) {
        experiment_comparison_free(gate_run_report->comparison);
        gate_run_report->comparison = NULL;
    }
    if (gate_run_report->created_at) {
        free(gate_run_report->created_at);
        gate_run_report->created_at = NULL;
    }
    if (gate_run_report->dataset_id) {
        free(gate_run_report->dataset_id);
        gate_run_report->dataset_id = NULL;
    }
    if (gate_run_report->evaluator_version_id) {
        free(gate_run_report->evaluator_version_id);
        gate_run_report->evaluator_version_id = NULL;
    }
    if (gate_run_report->experiment_created_at) {
        free(gate_run_report->experiment_created_at);
        gate_run_report->experiment_created_at = NULL;
    }
    if (gate_run_report->experiment_gate_policy) {
        gate_policy_free(gate_run_report->experiment_gate_policy);
        gate_run_report->experiment_gate_policy = NULL;
    }
    if (gate_run_report->experiment_run_id) {
        free(gate_run_report->experiment_run_id);
        gate_run_report->experiment_run_id = NULL;
    }
    if (gate_run_report->gate_dataset_id) {
        free(gate_run_report->gate_dataset_id);
        gate_run_report->gate_dataset_id = NULL;
    }
    if (gate_run_report->gate_evaluator_version_id) {
        free(gate_run_report->gate_evaluator_version_id);
        gate_run_report->gate_evaluator_version_id = NULL;
    }
    if (gate_run_report->gate_id) {
        free(gate_run_report->gate_id);
        gate_run_report->gate_id = NULL;
    }
    if (gate_run_report->gate_name) {
        free(gate_run_report->gate_name);
        gate_run_report->gate_name = NULL;
    }
    if (gate_run_report->gate_run_id) {
        free(gate_run_report->gate_run_id);
        gate_run_report->gate_run_id = NULL;
    }
    if (gate_run_report->project_id) {
        free(gate_run_report->project_id);
        gate_run_report->project_id = NULL;
    }
    if (gate_run_report->reason) {
        free(gate_run_report->reason);
        gate_run_report->reason = NULL;
    }
    if (gate_run_report->tenant_id) {
        free(gate_run_report->tenant_id);
        gate_run_report->tenant_id = NULL;
    }
    free(gate_run_report);
}

cJSON *gate_run_report_convertToJSON(gate_run_report_t *gate_run_report) {
    cJSON *item = cJSON_CreateObject();

    // gate_run_report->baseline_release_id
    if (!gate_run_report->baseline_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "baseline_release_id", gate_run_report->baseline_release_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->candidate_release_id
    if (!gate_run_report->candidate_release_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "candidate_release_id", gate_run_report->candidate_release_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->comparison
    if (!gate_run_report->comparison) {
        goto fail;
    }
    cJSON *comparison_local_JSON = experiment_comparison_convertToJSON(gate_run_report->comparison);
    if(comparison_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "comparison", comparison_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // gate_run_report->created_at
    if (!gate_run_report->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "created_at", gate_run_report->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // gate_run_report->dataset_id
    if (!gate_run_report->dataset_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "dataset_id", gate_run_report->dataset_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->evaluator_version_id
    if (!gate_run_report->evaluator_version_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "evaluator_version_id", gate_run_report->evaluator_version_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->experiment_created_at
    if (!gate_run_report->experiment_created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "experiment_created_at", gate_run_report->experiment_created_at) == NULL) {
    goto fail; //Date-Time
    }


    // gate_run_report->experiment_decision
    if (beater_api_gate_decision__NULL == gate_run_report->experiment_decision) {
        goto fail;
    }
    cJSON *experiment_decision_local_JSON = gate_decision_convertToJSON(gate_run_report->experiment_decision);
    if(experiment_decision_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "experiment_decision", experiment_decision_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // gate_run_report->experiment_gate_policy
    if (!gate_run_report->experiment_gate_policy) {
        goto fail;
    }
    cJSON *experiment_gate_policy_local_JSON = gate_policy_convertToJSON(gate_run_report->experiment_gate_policy);
    if(experiment_gate_policy_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "experiment_gate_policy", experiment_gate_policy_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // gate_run_report->experiment_run_id
    if (!gate_run_report->experiment_run_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "experiment_run_id", gate_run_report->experiment_run_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->gate_dataset_id
    if(gate_run_report->gate_dataset_id) {
    if(cJSON_AddStringToObject(item, "gate_dataset_id", gate_run_report->gate_dataset_id) == NULL) {
    goto fail; //String
    }
    }


    // gate_run_report->gate_evaluator_version_id
    if(gate_run_report->gate_evaluator_version_id) {
    if(cJSON_AddStringToObject(item, "gate_evaluator_version_id", gate_run_report->gate_evaluator_version_id) == NULL) {
    goto fail; //String
    }
    }


    // gate_run_report->gate_id
    if (!gate_run_report->gate_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "gate_id", gate_run_report->gate_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->gate_name
    if (!gate_run_report->gate_name) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "gate_name", gate_run_report->gate_name) == NULL) {
    goto fail; //String
    }


    // gate_run_report->gate_run_id
    if (!gate_run_report->gate_run_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "gate_run_id", gate_run_report->gate_run_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->inconclusive_policy
    if (beater_api_inconclusive_policy__NULL == gate_run_report->inconclusive_policy) {
        goto fail;
    }
    cJSON *inconclusive_policy_local_JSON = inconclusive_policy_convertToJSON(gate_run_report->inconclusive_policy);
    if(inconclusive_policy_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "inconclusive_policy", inconclusive_policy_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // gate_run_report->passed
    if (!gate_run_report->passed) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "passed", gate_run_report->passed) == NULL) {
    goto fail; //Bool
    }


    // gate_run_report->project_id
    if (!gate_run_report->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", gate_run_report->project_id) == NULL) {
    goto fail; //String
    }


    // gate_run_report->reason
    if (!gate_run_report->reason) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "reason", gate_run_report->reason) == NULL) {
    goto fail; //String
    }


    // gate_run_report->tenant_id
    if (!gate_run_report->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", gate_run_report->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

gate_run_report_t *gate_run_report_parseFromJSON(cJSON *gate_run_reportJSON){

    gate_run_report_t *gate_run_report_local_var = NULL;

    // define the local variable for gate_run_report->comparison
    experiment_comparison_t *comparison_local_nonprim = NULL;

    // define the local variable for gate_run_report->experiment_decision
    beater_api_gate_decision__e experiment_decision_local_nonprim = 0;

    // define the local variable for gate_run_report->experiment_gate_policy
    gate_policy_t *experiment_gate_policy_local_nonprim = NULL;

    // define the local variable for gate_run_report->inconclusive_policy
    beater_api_inconclusive_policy__e inconclusive_policy_local_nonprim = 0;

    // gate_run_report->baseline_release_id
    cJSON *baseline_release_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "baseline_release_id");
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

    // gate_run_report->candidate_release_id
    cJSON *candidate_release_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "candidate_release_id");
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

    // gate_run_report->comparison
    cJSON *comparison = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "comparison");
    if (cJSON_IsNull(comparison)) {
        comparison = NULL;
    }
    if (!comparison) {
        goto end;
    }

    
    comparison_local_nonprim = experiment_comparison_parseFromJSON(comparison); //nonprimitive

    // gate_run_report->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "created_at");
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

    // gate_run_report->dataset_id
    cJSON *dataset_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "dataset_id");
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

    // gate_run_report->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "evaluator_version_id");
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

    // gate_run_report->experiment_created_at
    cJSON *experiment_created_at = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "experiment_created_at");
    if (cJSON_IsNull(experiment_created_at)) {
        experiment_created_at = NULL;
    }
    if (!experiment_created_at) {
        goto end;
    }

    
    if(!cJSON_IsString(experiment_created_at) && !cJSON_IsNull(experiment_created_at))
    {
    goto end; //DateTime
    }

    // gate_run_report->experiment_decision
    cJSON *experiment_decision = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "experiment_decision");
    if (cJSON_IsNull(experiment_decision)) {
        experiment_decision = NULL;
    }
    if (!experiment_decision) {
        goto end;
    }

    
    experiment_decision_local_nonprim = gate_decision_parseFromJSON(experiment_decision); //custom

    // gate_run_report->experiment_gate_policy
    cJSON *experiment_gate_policy = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "experiment_gate_policy");
    if (cJSON_IsNull(experiment_gate_policy)) {
        experiment_gate_policy = NULL;
    }
    if (!experiment_gate_policy) {
        goto end;
    }

    
    experiment_gate_policy_local_nonprim = gate_policy_parseFromJSON(experiment_gate_policy); //nonprimitive

    // gate_run_report->experiment_run_id
    cJSON *experiment_run_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "experiment_run_id");
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

    // gate_run_report->gate_dataset_id
    cJSON *gate_dataset_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "gate_dataset_id");
    if (cJSON_IsNull(gate_dataset_id)) {
        gate_dataset_id = NULL;
    }
    if (gate_dataset_id) { 
    if(!cJSON_IsString(gate_dataset_id) && !cJSON_IsNull(gate_dataset_id))
    {
    goto end; //String
    }
    }

    // gate_run_report->gate_evaluator_version_id
    cJSON *gate_evaluator_version_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "gate_evaluator_version_id");
    if (cJSON_IsNull(gate_evaluator_version_id)) {
        gate_evaluator_version_id = NULL;
    }
    if (gate_evaluator_version_id) { 
    if(!cJSON_IsString(gate_evaluator_version_id) && !cJSON_IsNull(gate_evaluator_version_id))
    {
    goto end; //String
    }
    }

    // gate_run_report->gate_id
    cJSON *gate_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "gate_id");
    if (cJSON_IsNull(gate_id)) {
        gate_id = NULL;
    }
    if (!gate_id) {
        goto end;
    }

    
    if(!cJSON_IsString(gate_id))
    {
    goto end; //String
    }

    // gate_run_report->gate_name
    cJSON *gate_name = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "gate_name");
    if (cJSON_IsNull(gate_name)) {
        gate_name = NULL;
    }
    if (!gate_name) {
        goto end;
    }

    
    if(!cJSON_IsString(gate_name))
    {
    goto end; //String
    }

    // gate_run_report->gate_run_id
    cJSON *gate_run_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "gate_run_id");
    if (cJSON_IsNull(gate_run_id)) {
        gate_run_id = NULL;
    }
    if (!gate_run_id) {
        goto end;
    }

    
    if(!cJSON_IsString(gate_run_id))
    {
    goto end; //String
    }

    // gate_run_report->inconclusive_policy
    cJSON *inconclusive_policy = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "inconclusive_policy");
    if (cJSON_IsNull(inconclusive_policy)) {
        inconclusive_policy = NULL;
    }
    if (!inconclusive_policy) {
        goto end;
    }

    
    inconclusive_policy_local_nonprim = inconclusive_policy_parseFromJSON(inconclusive_policy); //custom

    // gate_run_report->passed
    cJSON *passed = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "passed");
    if (cJSON_IsNull(passed)) {
        passed = NULL;
    }
    if (!passed) {
        goto end;
    }

    
    if(!cJSON_IsBool(passed))
    {
    goto end; //Bool
    }

    // gate_run_report->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "project_id");
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

    // gate_run_report->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "reason");
    if (cJSON_IsNull(reason)) {
        reason = NULL;
    }
    if (!reason) {
        goto end;
    }

    
    if(!cJSON_IsString(reason))
    {
    goto end; //String
    }

    // gate_run_report->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(gate_run_reportJSON, "tenant_id");
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


    gate_run_report_local_var = gate_run_report_create_internal (
        strdup(baseline_release_id->valuestring),
        strdup(candidate_release_id->valuestring),
        comparison_local_nonprim,
        strdup(created_at->valuestring),
        strdup(dataset_id->valuestring),
        strdup(evaluator_version_id->valuestring),
        strdup(experiment_created_at->valuestring),
        experiment_decision_local_nonprim,
        experiment_gate_policy_local_nonprim,
        strdup(experiment_run_id->valuestring),
        gate_dataset_id && !cJSON_IsNull(gate_dataset_id) ? strdup(gate_dataset_id->valuestring) : NULL,
        gate_evaluator_version_id && !cJSON_IsNull(gate_evaluator_version_id) ? strdup(gate_evaluator_version_id->valuestring) : NULL,
        strdup(gate_id->valuestring),
        strdup(gate_name->valuestring),
        strdup(gate_run_id->valuestring),
        inconclusive_policy_local_nonprim,
        passed->valueint,
        strdup(project_id->valuestring),
        strdup(reason->valuestring),
        strdup(tenant_id->valuestring)
        );

    return gate_run_report_local_var;
end:
    if (comparison_local_nonprim) {
        experiment_comparison_free(comparison_local_nonprim);
        comparison_local_nonprim = NULL;
    }
    if (experiment_decision_local_nonprim) {
        experiment_decision_local_nonprim = 0;
    }
    if (experiment_gate_policy_local_nonprim) {
        gate_policy_free(experiment_gate_policy_local_nonprim);
        experiment_gate_policy_local_nonprim = NULL;
    }
    if (inconclusive_policy_local_nonprim) {
        inconclusive_policy_local_nonprim = 0;
    }
    return NULL;

}
