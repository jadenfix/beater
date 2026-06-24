#ifndef calibration_policy_TEST
#define calibration_policy_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define calibration_policy_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/calibration_policy.h"
calibration_policy_t* instantiate_calibration_policy(int include_optional);



calibration_policy_t* instantiate_calibration_policy(int include_optional) {
  calibration_policy_t* calibration_policy = NULL;
  if (include_optional) {
    calibration_policy = calibration_policy_create(
      1.337
    );
  } else {
    calibration_policy = calibration_policy_create(
      1.337
    );
  }

  return calibration_policy;
}


#ifdef calibration_policy_MAIN

void test_calibration_policy(int include_optional) {
    calibration_policy_t* calibration_policy_1 = instantiate_calibration_policy(include_optional);

	cJSON* jsoncalibration_policy_1 = calibration_policy_convertToJSON(calibration_policy_1);
	printf("calibration_policy :\n%s\n", cJSON_Print(jsoncalibration_policy_1));
	calibration_policy_t* calibration_policy_2 = calibration_policy_parseFromJSON(jsoncalibration_policy_1);
	cJSON* jsoncalibration_policy_2 = calibration_policy_convertToJSON(calibration_policy_2);
	printf("repeating calibration_policy:\n%s\n", cJSON_Print(jsoncalibration_policy_2));
}

int main() {
  test_calibration_policy(1);
  test_calibration_policy(0);

  printf("Hello world \n");
  return 0;
}

#endif // calibration_policy_MAIN
#endif // calibration_policy_TEST
