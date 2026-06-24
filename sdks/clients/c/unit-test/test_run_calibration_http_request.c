#ifndef run_calibration_http_request_TEST
#define run_calibration_http_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define run_calibration_http_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/run_calibration_http_request.h"
run_calibration_http_request_t* instantiate_run_calibration_http_request(int include_optional);



run_calibration_http_request_t* instantiate_run_calibration_http_request(int include_optional) {
  run_calibration_http_request_t* run_calibration_http_request = NULL;
  if (include_optional) {
    run_calibration_http_request = run_calibration_http_request_create(
      "0",
      "0",
      1.337
    );
  } else {
    run_calibration_http_request = run_calibration_http_request_create(
      "0",
      "0",
      1.337
    );
  }

  return run_calibration_http_request;
}


#ifdef run_calibration_http_request_MAIN

void test_run_calibration_http_request(int include_optional) {
    run_calibration_http_request_t* run_calibration_http_request_1 = instantiate_run_calibration_http_request(include_optional);

	cJSON* jsonrun_calibration_http_request_1 = run_calibration_http_request_convertToJSON(run_calibration_http_request_1);
	printf("run_calibration_http_request :\n%s\n", cJSON_Print(jsonrun_calibration_http_request_1));
	run_calibration_http_request_t* run_calibration_http_request_2 = run_calibration_http_request_parseFromJSON(jsonrun_calibration_http_request_1);
	cJSON* jsonrun_calibration_http_request_2 = run_calibration_http_request_convertToJSON(run_calibration_http_request_2);
	printf("repeating run_calibration_http_request:\n%s\n", cJSON_Print(jsonrun_calibration_http_request_2));
}

int main() {
  test_run_calibration_http_request(1);
  test_run_calibration_http_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // run_calibration_http_request_MAIN
#endif // run_calibration_http_request_TEST
