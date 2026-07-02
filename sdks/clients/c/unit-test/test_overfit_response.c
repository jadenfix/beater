#ifndef overfit_response_TEST
#define overfit_response_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define overfit_response_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/overfit_response.h"
overfit_response_t* instantiate_overfit_response(int include_optional);



overfit_response_t* instantiate_overfit_response(int include_optional) {
  overfit_response_t* overfit_response = NULL;
  if (include_optional) {
    overfit_response = overfit_response_create(
      1.337,
      1.337,
      1.337,
      1.337,
      1.337,
      1
    );
  } else {
    overfit_response = overfit_response_create(
      1.337,
      1.337,
      1.337,
      1.337,
      1.337,
      1
    );
  }

  return overfit_response;
}


#ifdef overfit_response_MAIN

void test_overfit_response(int include_optional) {
    overfit_response_t* overfit_response_1 = instantiate_overfit_response(include_optional);

	cJSON* jsonoverfit_response_1 = overfit_response_convertToJSON(overfit_response_1);
	printf("overfit_response :\n%s\n", cJSON_Print(jsonoverfit_response_1));
	overfit_response_t* overfit_response_2 = overfit_response_parseFromJSON(jsonoverfit_response_1);
	cJSON* jsonoverfit_response_2 = overfit_response_convertToJSON(overfit_response_2);
	printf("repeating overfit_response:\n%s\n", cJSON_Print(jsonoverfit_response_2));
}

int main() {
  test_overfit_response(1);
  test_overfit_response(0);

  printf("Hello world \n");
  return 0;
}

#endif // overfit_response_MAIN
#endif // overfit_response_TEST
