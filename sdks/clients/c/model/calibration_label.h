/*
 * calibration_label.h
 *
 * 
 */

#ifndef _calibration_label_H_
#define _calibration_label_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct calibration_label_t calibration_label_t;


// Enum  for calibration_label

typedef enum { beater_api_calibration_label__NULL = 0, beater_api_calibration_label__pass, beater_api_calibration_label__fail } beater_api_calibration_label__e;

char* calibration_label_calibration_label_ToString(beater_api_calibration_label__e calibration_label);

beater_api_calibration_label__e calibration_label_calibration_label_FromString(char* calibration_label);

cJSON *calibration_label_convertToJSON(beater_api_calibration_label__e calibration_label);

beater_api_calibration_label__e calibration_label_parseFromJSON(cJSON *calibration_labelJSON);

#endif /* _calibration_label_H_ */

