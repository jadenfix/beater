#ifndef rollup_weighting_TEST
#define rollup_weighting_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define rollup_weighting_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/rollup_weighting.h"
rollup_weighting_t* instantiate_rollup_weighting(int include_optional);



rollup_weighting_t* instantiate_rollup_weighting(int include_optional) {
  rollup_weighting_t* rollup_weighting = NULL;
  if (include_optional) {
    rollup_weighting = rollup_weighting_create(
    );
  } else {
    rollup_weighting = rollup_weighting_create(
    );
  }

  return rollup_weighting;
}


#ifdef rollup_weighting_MAIN

void test_rollup_weighting(int include_optional) {
    rollup_weighting_t* rollup_weighting_1 = instantiate_rollup_weighting(include_optional);

	cJSON* jsonrollup_weighting_1 = rollup_weighting_convertToJSON(rollup_weighting_1);
	printf("rollup_weighting :\n%s\n", cJSON_Print(jsonrollup_weighting_1));
	rollup_weighting_t* rollup_weighting_2 = rollup_weighting_parseFromJSON(jsonrollup_weighting_1);
	cJSON* jsonrollup_weighting_2 = rollup_weighting_convertToJSON(rollup_weighting_2);
	printf("repeating rollup_weighting:\n%s\n", cJSON_Print(jsonrollup_weighting_2));
}

int main() {
  test_rollup_weighting(1);
  test_rollup_weighting(0);

  printf("Hello world \n");
  return 0;
}

#endif // rollup_weighting_MAIN
#endif // rollup_weighting_TEST
