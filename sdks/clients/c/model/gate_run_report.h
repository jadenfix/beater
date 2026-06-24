/*
 * gate_run_report.h
 *
 * 
 */

#ifndef _gate_run_report_H_
#define _gate_run_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct gate_run_report_t gate_run_report_t;

#include "experiment_comparison.h"
#include "gate_decision.h"
#include "gate_policy.h"
#include "inconclusive_policy.h"



typedef struct gate_run_report_t {
    char *baseline_release_id; // string
    char *candidate_release_id; // string
    struct experiment_comparison_t *comparison; //model
    char *created_at; //date time
    char *dataset_id; // string
    char *evaluator_version_id; // string
    char *experiment_created_at; //date time
    beater_api_gate_decision__e experiment_decision; //referenced enum
    struct gate_policy_t *experiment_gate_policy; //model
    char *experiment_run_id; // string
    char *gate_dataset_id; // string
    char *gate_evaluator_version_id; // string
    char *gate_id; // string
    char *gate_name; // string
    char *gate_run_id; // string
    beater_api_inconclusive_policy__e inconclusive_policy; //referenced enum
    int passed; //boolean
    char *project_id; // string
    char *reason; // string
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} gate_run_report_t;

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
);

void gate_run_report_free(gate_run_report_t *gate_run_report);

gate_run_report_t *gate_run_report_parseFromJSON(cJSON *gate_run_reportJSON);

cJSON *gate_run_report_convertToJSON(gate_run_report_t *gate_run_report);

#endif /* _gate_run_report_H_ */

