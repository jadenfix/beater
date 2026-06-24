#ifndef calibration_item_TEST
#define calibration_item_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define calibration_item_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/calibration_item.h"
calibration_item_t* instantiate_calibration_item(int include_optional);



calibration_item_t* instantiate_calibration_item(int include_optional) {
  calibration_item_t* calibration_item = NULL;
  if (include_optional) {
    calibration_item = calibration_item_create(
      1,
      "0",
      null,
      beater_api_calibration_item__pass,
      beater_api_calibration_item__pass,
      "0",
      1.337
    );
  } else {
    calibration_item = calibration_item_create(
      1,
      "0",
      null,
      beater_api_calibration_item__pass,
      beater_api_calibration_item__pass,
      "0",
      1.337
    );
  }

  return calibration_item;
}


#ifdef calibration_item_MAIN

void test_calibration_item(int include_optional) {
    calibration_item_t* calibration_item_1 = instantiate_calibration_item(include_optional);

	cJSON* jsoncalibration_item_1 = calibration_item_convertToJSON(calibration_item_1);
	printf("calibration_item :\n%s\n", cJSON_Print(jsoncalibration_item_1));
	calibration_item_t* calibration_item_2 = calibration_item_parseFromJSON(jsoncalibration_item_1);
	cJSON* jsoncalibration_item_2 = calibration_item_convertToJSON(calibration_item_2);
	printf("repeating calibration_item:\n%s\n", cJSON_Print(jsoncalibration_item_2));
}

int main() {
  test_calibration_item(1);
  test_calibration_item(0);

  printf("Hello world \n");
  return 0;
}

#endif // calibration_item_MAIN
#endif // calibration_item_TEST
