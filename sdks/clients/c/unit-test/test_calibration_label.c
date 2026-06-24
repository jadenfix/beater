#ifndef calibration_label_TEST
#define calibration_label_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define calibration_label_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/calibration_label.h"
calibration_label_t* instantiate_calibration_label(int include_optional);



calibration_label_t* instantiate_calibration_label(int include_optional) {
  calibration_label_t* calibration_label = NULL;
  if (include_optional) {
    calibration_label = calibration_label_create(
    );
  } else {
    calibration_label = calibration_label_create(
    );
  }

  return calibration_label;
}


#ifdef calibration_label_MAIN

void test_calibration_label(int include_optional) {
    calibration_label_t* calibration_label_1 = instantiate_calibration_label(include_optional);

	cJSON* jsoncalibration_label_1 = calibration_label_convertToJSON(calibration_label_1);
	printf("calibration_label :\n%s\n", cJSON_Print(jsoncalibration_label_1));
	calibration_label_t* calibration_label_2 = calibration_label_parseFromJSON(jsoncalibration_label_1);
	cJSON* jsoncalibration_label_2 = calibration_label_convertToJSON(calibration_label_2);
	printf("repeating calibration_label:\n%s\n", cJSON_Print(jsoncalibration_label_2));
}

int main() {
  test_calibration_label(1);
  test_calibration_label(0);

  printf("Hello world \n");
  return 0;
}

#endif // calibration_label_MAIN
#endif // calibration_label_TEST
