#ifndef calibration_confusion_TEST
#define calibration_confusion_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define calibration_confusion_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/calibration_confusion.h"
calibration_confusion_t* instantiate_calibration_confusion(int include_optional);



calibration_confusion_t* instantiate_calibration_confusion(int include_optional) {
  calibration_confusion_t* calibration_confusion = NULL;
  if (include_optional) {
    calibration_confusion = calibration_confusion_create(
      0,
      0,
      0,
      0
    );
  } else {
    calibration_confusion = calibration_confusion_create(
      0,
      0,
      0,
      0
    );
  }

  return calibration_confusion;
}


#ifdef calibration_confusion_MAIN

void test_calibration_confusion(int include_optional) {
    calibration_confusion_t* calibration_confusion_1 = instantiate_calibration_confusion(include_optional);

	cJSON* jsoncalibration_confusion_1 = calibration_confusion_convertToJSON(calibration_confusion_1);
	printf("calibration_confusion :\n%s\n", cJSON_Print(jsoncalibration_confusion_1));
	calibration_confusion_t* calibration_confusion_2 = calibration_confusion_parseFromJSON(jsoncalibration_confusion_1);
	cJSON* jsoncalibration_confusion_2 = calibration_confusion_convertToJSON(calibration_confusion_2);
	printf("repeating calibration_confusion:\n%s\n", cJSON_Print(jsoncalibration_confusion_2));
}

int main() {
  test_calibration_confusion(1);
  test_calibration_confusion(0);

  printf("Hello world \n");
  return 0;
}

#endif // calibration_confusion_MAIN
#endif // calibration_confusion_TEST
