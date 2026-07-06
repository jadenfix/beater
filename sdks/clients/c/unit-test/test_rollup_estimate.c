#ifndef rollup_estimate_TEST
#define rollup_estimate_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define rollup_estimate_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/rollup_estimate.h"
rollup_estimate_t* instantiate_rollup_estimate(int include_optional);



rollup_estimate_t* instantiate_rollup_estimate(int include_optional) {
  rollup_estimate_t* rollup_estimate = NULL;
  if (include_optional) {
    rollup_estimate = rollup_estimate_create(
      1.337,
      beater_api_rollup_estimate__horvitz_thompson
    );
  } else {
    rollup_estimate = rollup_estimate_create(
      1.337,
      beater_api_rollup_estimate__horvitz_thompson
    );
  }

  return rollup_estimate;
}


#ifdef rollup_estimate_MAIN

void test_rollup_estimate(int include_optional) {
    rollup_estimate_t* rollup_estimate_1 = instantiate_rollup_estimate(include_optional);

	cJSON* jsonrollup_estimate_1 = rollup_estimate_convertToJSON(rollup_estimate_1);
	printf("rollup_estimate :\n%s\n", cJSON_Print(jsonrollup_estimate_1));
	rollup_estimate_t* rollup_estimate_2 = rollup_estimate_parseFromJSON(jsonrollup_estimate_1);
	cJSON* jsonrollup_estimate_2 = rollup_estimate_convertToJSON(rollup_estimate_2);
	printf("repeating rollup_estimate:\n%s\n", cJSON_Print(jsonrollup_estimate_2));
}

int main() {
  test_rollup_estimate(1);
  test_rollup_estimate(0);

  printf("Hello world \n");
  return 0;
}

#endif // rollup_estimate_MAIN
#endif // rollup_estimate_TEST
