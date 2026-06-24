/*
 * calibration_item.h
 *
 * 
 */

#ifndef _calibration_item_H_
#define _calibration_item_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct calibration_item_t calibration_item_t;

#include "any_type.h"
#include "calibration_label.h"



typedef struct calibration_item_t {
    int agreed; //boolean
    char *dataset_case_id; // string
    any_type_t *evidence; // custom
    beater_api_calibration_label__e human_label; //referenced enum
    beater_api_calibration_label__e judge_label; //referenced enum
    char *judge_result_label; // string
    double judge_score; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} calibration_item_t;

__attribute__((deprecated)) calibration_item_t *calibration_item_create(
    int agreed,
    char *dataset_case_id,
    any_type_t *evidence,
    beater_api_calibration_label__e human_label,
    beater_api_calibration_label__e judge_label,
    char *judge_result_label,
    double judge_score
);

void calibration_item_free(calibration_item_t *calibration_item);

calibration_item_t *calibration_item_parseFromJSON(cJSON *calibration_itemJSON);

cJSON *calibration_item_convertToJSON(calibration_item_t *calibration_item);

#endif /* _calibration_item_H_ */

