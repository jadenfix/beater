/*
 * calibration_report.h
 *
 * 
 */

#ifndef _calibration_report_H_
#define _calibration_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct calibration_report_t calibration_report_t;

#include "calibration_confusion.h"
#include "calibration_item.h"
#include "calibration_policy.h"



typedef struct calibration_report_t {
    char *calibration_report_id; // string
    double cohen_kappa; //numeric
    struct calibration_confusion_t *confusion; //model
    char *created_at; //date time
    char *dataset_id; // string
    char *dataset_version_id; // string
    char *eval_report_id; // string
    char *evaluator_version_id; // string
    double expected_agreement; //numeric
    list_t *items; //nonprimitive container
    double observed_agreement; //numeric
    struct calibration_policy_t *policy; //model
    char *project_id; // string
    int sample_count; //numeric
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} calibration_report_t;

__attribute__((deprecated)) calibration_report_t *calibration_report_create(
    char *calibration_report_id,
    double cohen_kappa,
    calibration_confusion_t *confusion,
    char *created_at,
    char *dataset_id,
    char *dataset_version_id,
    char *eval_report_id,
    char *evaluator_version_id,
    double expected_agreement,
    list_t *items,
    double observed_agreement,
    calibration_policy_t *policy,
    char *project_id,
    int sample_count,
    char *tenant_id
);

void calibration_report_free(calibration_report_t *calibration_report);

calibration_report_t *calibration_report_parseFromJSON(cJSON *calibration_reportJSON);

cJSON *calibration_report_convertToJSON(calibration_report_t *calibration_report);

#endif /* _calibration_report_H_ */

