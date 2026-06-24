/*
 * experiment_run_report.h
 *
 * 
 */

#ifndef _experiment_run_report_H_
#define _experiment_run_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct experiment_run_report_t experiment_run_report_t;

#include "case_experiment_score.h"
#include "experiment_comparison.h"
#include "gate_decision.h"
#include "gate_policy.h"



typedef struct experiment_run_report_t {
    char *baseline_release_id; // string
    char *candidate_release_id; // string
    list_t *case_scores; //nonprimitive container
    struct experiment_comparison_t *comparison; //model
    char *created_at; //date time
    char *dataset_id; // string
    char *dataset_version_id; // string
    beater_api_gate_decision__e decision; //referenced enum
    char *evaluator_version_id; // string
    char *experiment_run_id; // string
    struct gate_policy_t *gate_policy; //model
    char *project_id; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} experiment_run_report_t;

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
);

void experiment_run_report_free(experiment_run_report_t *experiment_run_report);

experiment_run_report_t *experiment_run_report_parseFromJSON(cJSON *experiment_run_reportJSON);

cJSON *experiment_run_report_convertToJSON(experiment_run_report_t *experiment_run_report);

#endif /* _experiment_run_report_H_ */

