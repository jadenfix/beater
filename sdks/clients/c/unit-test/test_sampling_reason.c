#ifndef sampling_reason_TEST
#define sampling_reason_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define sampling_reason_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/sampling_reason.h"
sampling_reason_t* instantiate_sampling_reason(int include_optional);



sampling_reason_t* instantiate_sampling_reason(int include_optional) {
  sampling_reason_t* sampling_reason = NULL;
  if (include_optional) {
    sampling_reason = sampling_reason_create(
    );
  } else {
    sampling_reason = sampling_reason_create(
    );
  }

  return sampling_reason;
}


#ifdef sampling_reason_MAIN

void test_sampling_reason(int include_optional) {
    sampling_reason_t* sampling_reason_1 = instantiate_sampling_reason(include_optional);

	cJSON* jsonsampling_reason_1 = sampling_reason_convertToJSON(sampling_reason_1);
	printf("sampling_reason :\n%s\n", cJSON_Print(jsonsampling_reason_1));
	sampling_reason_t* sampling_reason_2 = sampling_reason_parseFromJSON(jsonsampling_reason_1);
	cJSON* jsonsampling_reason_2 = sampling_reason_convertToJSON(sampling_reason_2);
	printf("repeating sampling_reason:\n%s\n", cJSON_Print(jsonsampling_reason_2));
}

int main() {
  test_sampling_reason(1);
  test_sampling_reason(0);

  printf("Hello world \n");
  return 0;
}

#endif // sampling_reason_MAIN
#endif // sampling_reason_TEST
