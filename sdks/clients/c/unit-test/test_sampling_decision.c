#ifndef sampling_decision_TEST
#define sampling_decision_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define sampling_decision_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/sampling_decision.h"
sampling_decision_t* instantiate_sampling_decision(int include_optional);



sampling_decision_t* instantiate_sampling_decision(int include_optional) {
  sampling_decision_t* sampling_decision = NULL;
  if (include_optional) {
    sampling_decision = sampling_decision_create(
      beater_api_sampling_decision__error_trace,
      1,
      0
    );
  } else {
    sampling_decision = sampling_decision_create(
      beater_api_sampling_decision__error_trace,
      1,
      0
    );
  }

  return sampling_decision;
}


#ifdef sampling_decision_MAIN

void test_sampling_decision(int include_optional) {
    sampling_decision_t* sampling_decision_1 = instantiate_sampling_decision(include_optional);

	cJSON* jsonsampling_decision_1 = sampling_decision_convertToJSON(sampling_decision_1);
	printf("sampling_decision :\n%s\n", cJSON_Print(jsonsampling_decision_1));
	sampling_decision_t* sampling_decision_2 = sampling_decision_parseFromJSON(jsonsampling_decision_1);
	cJSON* jsonsampling_decision_2 = sampling_decision_convertToJSON(sampling_decision_2);
	printf("repeating sampling_decision:\n%s\n", cJSON_Print(jsonsampling_decision_2));
}

int main() {
  test_sampling_decision(1);
  test_sampling_decision(0);

  printf("Hello world \n");
  return 0;
}

#endif // sampling_decision_MAIN
#endif // sampling_decision_TEST
