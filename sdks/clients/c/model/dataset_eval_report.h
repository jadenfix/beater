/*
 * dataset_eval_report.h
 *
 * 
 */

#ifndef _dataset_eval_report_H_
#define _dataset_eval_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct dataset_eval_report_t dataset_eval_report_t;

#include "eval_result.h"



typedef struct dataset_eval_report_t {
    double aggregate_score; //numeric
    char *created_at; //date time
    char *dataset_id; // string
    char *dataset_version_id; // string
    char *evaluator_version_id; // string
    char *project_id; // string
    char *report_id; // string
    int result_count; //numeric
    list_t *results; //nonprimitive container
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} dataset_eval_report_t;

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
);

void dataset_eval_report_free(dataset_eval_report_t *dataset_eval_report);

dataset_eval_report_t *dataset_eval_report_parseFromJSON(cJSON *dataset_eval_reportJSON);

cJSON *dataset_eval_report_convertToJSON(dataset_eval_report_t *dataset_eval_report);

#endif /* _dataset_eval_report_H_ */

