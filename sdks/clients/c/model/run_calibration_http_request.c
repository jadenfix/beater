#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "run_calibration_http_request.h"



static run_calibration_http_request_t *run_calibration_http_request_create_internal(
    char *eval_report_id,
    char *evaluator_version_id,
    double pass_threshold
    ) {
    run_calibration_http_request_t *run_calibration_http_request_local_var = malloc(sizeof(run_calibration_http_request_t));
    if (!run_calibration_http_request_local_var) {
        return NULL;
    }
    run_calibration_http_request_local_var->eval_report_id = eval_report_id;
    run_calibration_http_request_local_var->evaluator_version_id = evaluator_version_id;
    run_calibration_http_request_local_var->pass_threshold = pass_threshold;

    run_calibration_http_request_local_var->_library_owned = 1;
    return run_calibration_http_request_local_var;
}

__attribute__((deprecated)) run_calibration_http_request_t *run_calibration_http_request_create(
    char *eval_report_id,
    char *evaluator_version_id,
    double pass_threshold
    ) {
    return run_calibration_http_request_create_internal (
        eval_report_id,
        evaluator_version_id,
        pass_threshold
        );
}

void run_calibration_http_request_free(run_calibration_http_request_t *run_calibration_http_request) {
    if(NULL == run_calibration_http_request){
        return ;
    }
    if(run_calibration_http_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "run_calibration_http_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (run_calibration_http_request->eval_report_id) {
        free(run_calibration_http_request->eval_report_id);
        run_calibration_http_request->eval_report_id = NULL;
    }
    if (run_calibration_http_request->evaluator_version_id) {
        free(run_calibration_http_request->evaluator_version_id);
        run_calibration_http_request->evaluator_version_id = NULL;
    }
    free(run_calibration_http_request);
}

cJSON *run_calibration_http_request_convertToJSON(run_calibration_http_request_t *run_calibration_http_request) {
    cJSON *item = cJSON_CreateObject();

    // run_calibration_http_request->eval_report_id
    if(run_calibration_http_request->eval_report_id) {
    if(cJSON_AddStringToObject(item, "eval_report_id", run_calibration_http_request->eval_report_id) == NULL) {
    goto fail; //String
    }
    }


    // run_calibration_http_request->evaluator_version_id
    if(run_calibration_http_request->evaluator_version_id) {
    if(cJSON_AddStringToObject(item, "evaluator_version_id", run_calibration_http_request->evaluator_version_id) == NULL) {
    goto fail; //String
    }
    }


    // run_calibration_http_request->pass_threshold
    if(run_calibration_http_request->pass_threshold) {
    if(cJSON_AddNumberToObject(item, "pass_threshold", run_calibration_http_request->pass_threshold) == NULL) {
    goto fail; //Numeric
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

run_calibration_http_request_t *run_calibration_http_request_parseFromJSON(cJSON *run_calibration_http_requestJSON){

    run_calibration_http_request_t *run_calibration_http_request_local_var = NULL;

    // run_calibration_http_request->eval_report_id
    cJSON *eval_report_id = cJSON_GetObjectItemCaseSensitive(run_calibration_http_requestJSON, "eval_report_id");
    if (cJSON_IsNull(eval_report_id)) {
        eval_report_id = NULL;
    }
    if (eval_report_id) { 
    if(!cJSON_IsString(eval_report_id) && !cJSON_IsNull(eval_report_id))
    {
    goto end; //String
    }
    }

    // run_calibration_http_request->evaluator_version_id
    cJSON *evaluator_version_id = cJSON_GetObjectItemCaseSensitive(run_calibration_http_requestJSON, "evaluator_version_id");
    if (cJSON_IsNull(evaluator_version_id)) {
        evaluator_version_id = NULL;
    }
    if (evaluator_version_id) { 
    if(!cJSON_IsString(evaluator_version_id) && !cJSON_IsNull(evaluator_version_id))
    {
    goto end; //String
    }
    }

    // run_calibration_http_request->pass_threshold
    cJSON *pass_threshold = cJSON_GetObjectItemCaseSensitive(run_calibration_http_requestJSON, "pass_threshold");
    if (cJSON_IsNull(pass_threshold)) {
        pass_threshold = NULL;
    }
    if (pass_threshold) { 
    if(!cJSON_IsNumber(pass_threshold))
    {
    goto end; //Numeric
    }
    }


    run_calibration_http_request_local_var = run_calibration_http_request_create_internal (
        eval_report_id && !cJSON_IsNull(eval_report_id) ? strdup(eval_report_id->valuestring) : NULL,
        evaluator_version_id && !cJSON_IsNull(evaluator_version_id) ? strdup(evaluator_version_id->valuestring) : NULL,
        pass_threshold ? pass_threshold->valuedouble : 0
        );

    return run_calibration_http_request_local_var;
end:
    return NULL;

}
