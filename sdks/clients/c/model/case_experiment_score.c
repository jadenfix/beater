#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "case_experiment_score.h"



static case_experiment_score_t *case_experiment_score_create_internal(
    int baseline_cached,
    money_t *baseline_cost,
    any_type_t *baseline_evidence,
    char *baseline_judge_call_id,
    any_type_t *baseline_output,
    double baseline_score,
    any_type_t *baseline_trace,
    int candidate_cached,
    money_t *candidate_cost,
    any_type_t *candidate_evidence,
    char *candidate_judge_call_id,
    any_type_t *candidate_output,
    double candidate_score,
    any_type_t *candidate_trace,
    char *case_id,
    double delta,
    any_type_t *reference
    ) {
    case_experiment_score_t *case_experiment_score_local_var = malloc(sizeof(case_experiment_score_t));
    if (!case_experiment_score_local_var) {
        return NULL;
    }
    case_experiment_score_local_var->baseline_cached = baseline_cached;
    case_experiment_score_local_var->baseline_cost = baseline_cost;
    case_experiment_score_local_var->baseline_evidence = baseline_evidence;
    case_experiment_score_local_var->baseline_judge_call_id = baseline_judge_call_id;
    case_experiment_score_local_var->baseline_output = baseline_output;
    case_experiment_score_local_var->baseline_score = baseline_score;
    case_experiment_score_local_var->baseline_trace = baseline_trace;
    case_experiment_score_local_var->candidate_cached = candidate_cached;
    case_experiment_score_local_var->candidate_cost = candidate_cost;
    case_experiment_score_local_var->candidate_evidence = candidate_evidence;
    case_experiment_score_local_var->candidate_judge_call_id = candidate_judge_call_id;
    case_experiment_score_local_var->candidate_output = candidate_output;
    case_experiment_score_local_var->candidate_score = candidate_score;
    case_experiment_score_local_var->candidate_trace = candidate_trace;
    case_experiment_score_local_var->case_id = case_id;
    case_experiment_score_local_var->delta = delta;
    case_experiment_score_local_var->reference = reference;

    case_experiment_score_local_var->_library_owned = 1;
    return case_experiment_score_local_var;
}

__attribute__((deprecated)) case_experiment_score_t *case_experiment_score_create(
    int baseline_cached,
    money_t *baseline_cost,
    any_type_t *baseline_evidence,
    char *baseline_judge_call_id,
    any_type_t *baseline_output,
    double baseline_score,
    any_type_t *baseline_trace,
    int candidate_cached,
    money_t *candidate_cost,
    any_type_t *candidate_evidence,
    char *candidate_judge_call_id,
    any_type_t *candidate_output,
    double candidate_score,
    any_type_t *candidate_trace,
    char *case_id,
    double delta,
    any_type_t *reference
    ) {
    return case_experiment_score_create_internal (
        baseline_cached,
        baseline_cost,
        baseline_evidence,
        baseline_judge_call_id,
        baseline_output,
        baseline_score,
        baseline_trace,
        candidate_cached,
        candidate_cost,
        candidate_evidence,
        candidate_judge_call_id,
        candidate_output,
        candidate_score,
        candidate_trace,
        case_id,
        delta,
        reference
        );
}

void case_experiment_score_free(case_experiment_score_t *case_experiment_score) {
    if(NULL == case_experiment_score){
        return ;
    }
    if(case_experiment_score->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "case_experiment_score_free");
        return ;
    }
    listEntry_t *listEntry;
    if (case_experiment_score->baseline_cost) {
        money_free(case_experiment_score->baseline_cost);
        case_experiment_score->baseline_cost = NULL;
    }
    if (case_experiment_score->baseline_evidence) {
        _free(case_experiment_score->baseline_evidence);
        case_experiment_score->baseline_evidence = NULL;
    }
    if (case_experiment_score->baseline_judge_call_id) {
        free(case_experiment_score->baseline_judge_call_id);
        case_experiment_score->baseline_judge_call_id = NULL;
    }
    if (case_experiment_score->baseline_output) {
        _free(case_experiment_score->baseline_output);
        case_experiment_score->baseline_output = NULL;
    }
    if (case_experiment_score->baseline_trace) {
        _free(case_experiment_score->baseline_trace);
        case_experiment_score->baseline_trace = NULL;
    }
    if (case_experiment_score->candidate_cost) {
        money_free(case_experiment_score->candidate_cost);
        case_experiment_score->candidate_cost = NULL;
    }
    if (case_experiment_score->candidate_evidence) {
        _free(case_experiment_score->candidate_evidence);
        case_experiment_score->candidate_evidence = NULL;
    }
    if (case_experiment_score->candidate_judge_call_id) {
        free(case_experiment_score->candidate_judge_call_id);
        case_experiment_score->candidate_judge_call_id = NULL;
    }
    if (case_experiment_score->candidate_output) {
        _free(case_experiment_score->candidate_output);
        case_experiment_score->candidate_output = NULL;
    }
    if (case_experiment_score->candidate_trace) {
        _free(case_experiment_score->candidate_trace);
        case_experiment_score->candidate_trace = NULL;
    }
    if (case_experiment_score->case_id) {
        free(case_experiment_score->case_id);
        case_experiment_score->case_id = NULL;
    }
    if (case_experiment_score->reference) {
        _free(case_experiment_score->reference);
        case_experiment_score->reference = NULL;
    }
    free(case_experiment_score);
}

cJSON *case_experiment_score_convertToJSON(case_experiment_score_t *case_experiment_score) {
    cJSON *item = cJSON_CreateObject();

    // case_experiment_score->baseline_cached
    if(case_experiment_score->baseline_cached) {
    if(cJSON_AddBoolToObject(item, "baseline_cached", case_experiment_score->baseline_cached) == NULL) {
    goto fail; //Bool
    }
    }


    // case_experiment_score->baseline_cost
    if(case_experiment_score->baseline_cost) {
    cJSON *baseline_cost_local_JSON = money_convertToJSON(case_experiment_score->baseline_cost);
    if(baseline_cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "baseline_cost", baseline_cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // case_experiment_score->baseline_evidence
    if (!case_experiment_score->baseline_evidence) {
        goto fail;
    }
    cJSON *baseline_evidence_local_JSON = _convertToJSON(case_experiment_score->baseline_evidence);
    if(baseline_evidence_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "baseline_evidence", baseline_evidence_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // case_experiment_score->baseline_judge_call_id
    if(case_experiment_score->baseline_judge_call_id) {
    if(cJSON_AddStringToObject(item, "baseline_judge_call_id", case_experiment_score->baseline_judge_call_id) == NULL) {
    goto fail; //String
    }
    }


    // case_experiment_score->baseline_output
    if (!case_experiment_score->baseline_output) {
        goto fail;
    }
    cJSON *baseline_output_local_JSON = _convertToJSON(case_experiment_score->baseline_output);
    if(baseline_output_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "baseline_output", baseline_output_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // case_experiment_score->baseline_score
    if (!case_experiment_score->baseline_score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "baseline_score", case_experiment_score->baseline_score) == NULL) {
    goto fail; //Numeric
    }


    // case_experiment_score->baseline_trace
    if(case_experiment_score->baseline_trace) {
    cJSON *baseline_trace_local_JSON = _convertToJSON(case_experiment_score->baseline_trace);
    if(baseline_trace_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "baseline_trace", baseline_trace_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // case_experiment_score->candidate_cached
    if(case_experiment_score->candidate_cached) {
    if(cJSON_AddBoolToObject(item, "candidate_cached", case_experiment_score->candidate_cached) == NULL) {
    goto fail; //Bool
    }
    }


    // case_experiment_score->candidate_cost
    if(case_experiment_score->candidate_cost) {
    cJSON *candidate_cost_local_JSON = money_convertToJSON(case_experiment_score->candidate_cost);
    if(candidate_cost_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "candidate_cost", candidate_cost_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
    }


    // case_experiment_score->candidate_evidence
    if (!case_experiment_score->candidate_evidence) {
        goto fail;
    }
    cJSON *candidate_evidence_local_JSON = _convertToJSON(case_experiment_score->candidate_evidence);
    if(candidate_evidence_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "candidate_evidence", candidate_evidence_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // case_experiment_score->candidate_judge_call_id
    if(case_experiment_score->candidate_judge_call_id) {
    if(cJSON_AddStringToObject(item, "candidate_judge_call_id", case_experiment_score->candidate_judge_call_id) == NULL) {
    goto fail; //String
    }
    }


    // case_experiment_score->candidate_output
    if (!case_experiment_score->candidate_output) {
        goto fail;
    }
    cJSON *candidate_output_local_JSON = _convertToJSON(case_experiment_score->candidate_output);
    if(candidate_output_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "candidate_output", candidate_output_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // case_experiment_score->candidate_score
    if (!case_experiment_score->candidate_score) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "candidate_score", case_experiment_score->candidate_score) == NULL) {
    goto fail; //Numeric
    }


    // case_experiment_score->candidate_trace
    if(case_experiment_score->candidate_trace) {
    cJSON *candidate_trace_local_JSON = _convertToJSON(case_experiment_score->candidate_trace);
    if(candidate_trace_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "candidate_trace", candidate_trace_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }


    // case_experiment_score->case_id
    if (!case_experiment_score->case_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "case_id", case_experiment_score->case_id) == NULL) {
    goto fail; //String
    }


    // case_experiment_score->delta
    if (!case_experiment_score->delta) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "delta", case_experiment_score->delta) == NULL) {
    goto fail; //Numeric
    }


    // case_experiment_score->reference
    if(case_experiment_score->reference) {
    cJSON *reference_local_JSON = _convertToJSON(case_experiment_score->reference);
    if(reference_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "reference", reference_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

case_experiment_score_t *case_experiment_score_parseFromJSON(cJSON *case_experiment_scoreJSON){

    case_experiment_score_t *case_experiment_score_local_var = NULL;

    // define the local variable for case_experiment_score->baseline_cost
    money_t *baseline_cost_local_nonprim = NULL;

    // define the local variable for case_experiment_score->baseline_evidence
    _t *baseline_evidence_local_nonprim = NULL;

    // define the local variable for case_experiment_score->baseline_output
    _t *baseline_output_local_nonprim = NULL;

    // define the local variable for case_experiment_score->baseline_trace
    _t *baseline_trace_local_nonprim = NULL;

    // define the local variable for case_experiment_score->candidate_cost
    money_t *candidate_cost_local_nonprim = NULL;

    // define the local variable for case_experiment_score->candidate_evidence
    _t *candidate_evidence_local_nonprim = NULL;

    // define the local variable for case_experiment_score->candidate_output
    _t *candidate_output_local_nonprim = NULL;

    // define the local variable for case_experiment_score->candidate_trace
    _t *candidate_trace_local_nonprim = NULL;

    // define the local variable for case_experiment_score->reference
    _t *reference_local_nonprim = NULL;

    // case_experiment_score->baseline_cached
    cJSON *baseline_cached = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "baseline_cached");
    if (cJSON_IsNull(baseline_cached)) {
        baseline_cached = NULL;
    }
    if (baseline_cached) { 
    if(!cJSON_IsBool(baseline_cached))
    {
    goto end; //Bool
    }
    }

    // case_experiment_score->baseline_cost
    cJSON *baseline_cost = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "baseline_cost");
    if (cJSON_IsNull(baseline_cost)) {
        baseline_cost = NULL;
    }
    if (baseline_cost) { 
    baseline_cost_local_nonprim = money_parseFromJSON(baseline_cost); //nonprimitive
    }

    // case_experiment_score->baseline_evidence
    cJSON *baseline_evidence = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "baseline_evidence");
    if (cJSON_IsNull(baseline_evidence)) {
        baseline_evidence = NULL;
    }
    if (!baseline_evidence) {
        goto end;
    }

    
    baseline_evidence_local_nonprim = _parseFromJSON(baseline_evidence); //custom

    // case_experiment_score->baseline_judge_call_id
    cJSON *baseline_judge_call_id = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "baseline_judge_call_id");
    if (cJSON_IsNull(baseline_judge_call_id)) {
        baseline_judge_call_id = NULL;
    }
    if (baseline_judge_call_id) { 
    if(!cJSON_IsString(baseline_judge_call_id) && !cJSON_IsNull(baseline_judge_call_id))
    {
    goto end; //String
    }
    }

    // case_experiment_score->baseline_output
    cJSON *baseline_output = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "baseline_output");
    if (cJSON_IsNull(baseline_output)) {
        baseline_output = NULL;
    }
    if (!baseline_output) {
        goto end;
    }

    
    baseline_output_local_nonprim = _parseFromJSON(baseline_output); //custom

    // case_experiment_score->baseline_score
    cJSON *baseline_score = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "baseline_score");
    if (cJSON_IsNull(baseline_score)) {
        baseline_score = NULL;
    }
    if (!baseline_score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(baseline_score))
    {
    goto end; //Numeric
    }

    // case_experiment_score->baseline_trace
    cJSON *baseline_trace = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "baseline_trace");
    if (cJSON_IsNull(baseline_trace)) {
        baseline_trace = NULL;
    }
    if (baseline_trace) { 
    baseline_trace_local_nonprim = _parseFromJSON(baseline_trace); //custom
    }

    // case_experiment_score->candidate_cached
    cJSON *candidate_cached = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "candidate_cached");
    if (cJSON_IsNull(candidate_cached)) {
        candidate_cached = NULL;
    }
    if (candidate_cached) { 
    if(!cJSON_IsBool(candidate_cached))
    {
    goto end; //Bool
    }
    }

    // case_experiment_score->candidate_cost
    cJSON *candidate_cost = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "candidate_cost");
    if (cJSON_IsNull(candidate_cost)) {
        candidate_cost = NULL;
    }
    if (candidate_cost) { 
    candidate_cost_local_nonprim = money_parseFromJSON(candidate_cost); //nonprimitive
    }

    // case_experiment_score->candidate_evidence
    cJSON *candidate_evidence = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "candidate_evidence");
    if (cJSON_IsNull(candidate_evidence)) {
        candidate_evidence = NULL;
    }
    if (!candidate_evidence) {
        goto end;
    }

    
    candidate_evidence_local_nonprim = _parseFromJSON(candidate_evidence); //custom

    // case_experiment_score->candidate_judge_call_id
    cJSON *candidate_judge_call_id = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "candidate_judge_call_id");
    if (cJSON_IsNull(candidate_judge_call_id)) {
        candidate_judge_call_id = NULL;
    }
    if (candidate_judge_call_id) { 
    if(!cJSON_IsString(candidate_judge_call_id) && !cJSON_IsNull(candidate_judge_call_id))
    {
    goto end; //String
    }
    }

    // case_experiment_score->candidate_output
    cJSON *candidate_output = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "candidate_output");
    if (cJSON_IsNull(candidate_output)) {
        candidate_output = NULL;
    }
    if (!candidate_output) {
        goto end;
    }

    
    candidate_output_local_nonprim = _parseFromJSON(candidate_output); //custom

    // case_experiment_score->candidate_score
    cJSON *candidate_score = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "candidate_score");
    if (cJSON_IsNull(candidate_score)) {
        candidate_score = NULL;
    }
    if (!candidate_score) {
        goto end;
    }

    
    if(!cJSON_IsNumber(candidate_score))
    {
    goto end; //Numeric
    }

    // case_experiment_score->candidate_trace
    cJSON *candidate_trace = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "candidate_trace");
    if (cJSON_IsNull(candidate_trace)) {
        candidate_trace = NULL;
    }
    if (candidate_trace) { 
    candidate_trace_local_nonprim = _parseFromJSON(candidate_trace); //custom
    }

    // case_experiment_score->case_id
    cJSON *case_id = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "case_id");
    if (cJSON_IsNull(case_id)) {
        case_id = NULL;
    }
    if (!case_id) {
        goto end;
    }

    
    if(!cJSON_IsString(case_id))
    {
    goto end; //String
    }

    // case_experiment_score->delta
    cJSON *delta = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "delta");
    if (cJSON_IsNull(delta)) {
        delta = NULL;
    }
    if (!delta) {
        goto end;
    }

    
    if(!cJSON_IsNumber(delta))
    {
    goto end; //Numeric
    }

    // case_experiment_score->reference
    cJSON *reference = cJSON_GetObjectItemCaseSensitive(case_experiment_scoreJSON, "reference");
    if (cJSON_IsNull(reference)) {
        reference = NULL;
    }
    if (reference) { 
    reference_local_nonprim = _parseFromJSON(reference); //custom
    }


    case_experiment_score_local_var = case_experiment_score_create_internal (
        baseline_cached ? baseline_cached->valueint : 0,
        baseline_cost ? baseline_cost_local_nonprim : NULL,
        baseline_evidence_local_nonprim,
        baseline_judge_call_id && !cJSON_IsNull(baseline_judge_call_id) ? strdup(baseline_judge_call_id->valuestring) : NULL,
        baseline_output_local_nonprim,
        baseline_score->valuedouble,
        baseline_trace ? baseline_trace_local_nonprim : NULL,
        candidate_cached ? candidate_cached->valueint : 0,
        candidate_cost ? candidate_cost_local_nonprim : NULL,
        candidate_evidence_local_nonprim,
        candidate_judge_call_id && !cJSON_IsNull(candidate_judge_call_id) ? strdup(candidate_judge_call_id->valuestring) : NULL,
        candidate_output_local_nonprim,
        candidate_score->valuedouble,
        candidate_trace ? candidate_trace_local_nonprim : NULL,
        strdup(case_id->valuestring),
        delta->valuedouble,
        reference ? reference_local_nonprim : NULL
        );

    return case_experiment_score_local_var;
end:
    if (baseline_cost_local_nonprim) {
        money_free(baseline_cost_local_nonprim);
        baseline_cost_local_nonprim = NULL;
    }
    if (baseline_evidence_local_nonprim) {
        _free(baseline_evidence_local_nonprim);
        baseline_evidence_local_nonprim = NULL;
    }
    if (baseline_output_local_nonprim) {
        _free(baseline_output_local_nonprim);
        baseline_output_local_nonprim = NULL;
    }
    if (baseline_trace_local_nonprim) {
        _free(baseline_trace_local_nonprim);
        baseline_trace_local_nonprim = NULL;
    }
    if (candidate_cost_local_nonprim) {
        money_free(candidate_cost_local_nonprim);
        candidate_cost_local_nonprim = NULL;
    }
    if (candidate_evidence_local_nonprim) {
        _free(candidate_evidence_local_nonprim);
        candidate_evidence_local_nonprim = NULL;
    }
    if (candidate_output_local_nonprim) {
        _free(candidate_output_local_nonprim);
        candidate_output_local_nonprim = NULL;
    }
    if (candidate_trace_local_nonprim) {
        _free(candidate_trace_local_nonprim);
        candidate_trace_local_nonprim = NULL;
    }
    if (reference_local_nonprim) {
        _free(reference_local_nonprim);
        reference_local_nonprim = NULL;
    }
    return NULL;

}
