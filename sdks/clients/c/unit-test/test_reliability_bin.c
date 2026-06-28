#ifndef reliability_bin_TEST
#define reliability_bin_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define reliability_bin_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/reliability_bin.h"
reliability_bin_t* instantiate_reliability_bin(int include_optional);



reliability_bin_t* instantiate_reliability_bin(int include_optional) {
  reliability_bin_t* reliability_bin = NULL;
  if (include_optional) {
    reliability_bin = reliability_bin_create(
      1.337,
      0,
      1.337,
      1.337,
      1.337,
      0,
      1.337
    );
  } else {
    reliability_bin = reliability_bin_create(
      1.337,
      0,
      1.337,
      1.337,
      1.337,
      0,
      1.337
    );
  }

  return reliability_bin;
}


#ifdef reliability_bin_MAIN

void test_reliability_bin(int include_optional) {
    reliability_bin_t* reliability_bin_1 = instantiate_reliability_bin(include_optional);

	cJSON* jsonreliability_bin_1 = reliability_bin_convertToJSON(reliability_bin_1);
	printf("reliability_bin :\n%s\n", cJSON_Print(jsonreliability_bin_1));
	reliability_bin_t* reliability_bin_2 = reliability_bin_parseFromJSON(jsonreliability_bin_1);
	cJSON* jsonreliability_bin_2 = reliability_bin_convertToJSON(reliability_bin_2);
	printf("repeating reliability_bin:\n%s\n", cJSON_Print(jsonreliability_bin_2));
}

int main() {
  test_reliability_bin(1);
  test_reliability_bin(0);

  printf("Hello world \n");
  return 0;
}

#endif // reliability_bin_MAIN
#endif // reliability_bin_TEST
