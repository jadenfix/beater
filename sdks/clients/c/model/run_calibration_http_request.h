/*
 * run_calibration_http_request.h
 *
 * 
 */

#ifndef _run_calibration_http_request_H_
#define _run_calibration_http_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct run_calibration_http_request_t run_calibration_http_request_t;




typedef struct run_calibration_http_request_t {
    char *eval_report_id; // string
    char *evaluator_version_id; // string
    double pass_threshold; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} run_calibration_http_request_t;

__attribute__((deprecated)) run_calibration_http_request_t *run_calibration_http_request_create(
    char *eval_report_id,
    char *evaluator_version_id,
    double pass_threshold
);

void run_calibration_http_request_free(run_calibration_http_request_t *run_calibration_http_request);

run_calibration_http_request_t *run_calibration_http_request_parseFromJSON(cJSON *run_calibration_http_requestJSON);

cJSON *run_calibration_http_request_convertToJSON(run_calibration_http_request_t *run_calibration_http_request);

#endif /* _run_calibration_http_request_H_ */

