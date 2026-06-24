#ifndef run_gate_request_TEST
#define run_gate_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define run_gate_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/run_gate_request.h"
run_gate_request_t* instantiate_run_gate_request(int include_optional);



run_gate_request_t* instantiate_run_gate_request(int include_optional) {
  run_gate_request_t* run_gate_request = NULL;
  if (include_optional) {
    run_gate_request = run_gate_request_create(
      "0"
    );
  } else {
    run_gate_request = run_gate_request_create(
      "0"
    );
  }

  return run_gate_request;
}


#ifdef run_gate_request_MAIN

void test_run_gate_request(int include_optional) {
    run_gate_request_t* run_gate_request_1 = instantiate_run_gate_request(include_optional);

	cJSON* jsonrun_gate_request_1 = run_gate_request_convertToJSON(run_gate_request_1);
	printf("run_gate_request :\n%s\n", cJSON_Print(jsonrun_gate_request_1));
	run_gate_request_t* run_gate_request_2 = run_gate_request_parseFromJSON(jsonrun_gate_request_1);
	cJSON* jsonrun_gate_request_2 = run_gate_request_convertToJSON(run_gate_request_2);
	printf("repeating run_gate_request:\n%s\n", cJSON_Print(jsonrun_gate_request_2));
}

int main() {
  test_run_gate_request(1);
  test_run_gate_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // run_gate_request_MAIN
#endif // run_gate_request_TEST
