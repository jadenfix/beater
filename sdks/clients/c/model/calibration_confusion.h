/*
 * calibration_confusion.h
 *
 * 
 */

#ifndef _calibration_confusion_H_
#define _calibration_confusion_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct calibration_confusion_t calibration_confusion_t;




typedef struct calibration_confusion_t {
    int human_fail_judge_fail; //numeric
    int human_fail_judge_pass; //numeric
    int human_pass_judge_fail; //numeric
    int human_pass_judge_pass; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} calibration_confusion_t;

__attribute__((deprecated)) calibration_confusion_t *calibration_confusion_create(
    int human_fail_judge_fail,
    int human_fail_judge_pass,
    int human_pass_judge_fail,
    int human_pass_judge_pass
);

void calibration_confusion_free(calibration_confusion_t *calibration_confusion);

calibration_confusion_t *calibration_confusion_parseFromJSON(cJSON *calibration_confusionJSON);

cJSON *calibration_confusion_convertToJSON(calibration_confusion_t *calibration_confusion);

#endif /* _calibration_confusion_H_ */

