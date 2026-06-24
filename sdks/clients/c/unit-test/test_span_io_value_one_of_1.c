#ifndef span_io_value_one_of_1_TEST
#define span_io_value_one_of_1_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define span_io_value_one_of_1_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/span_io_value_one_of_1.h"
span_io_value_one_of_1_t* instantiate_span_io_value_one_of_1(int include_optional);

#include "test_artifact_ref.c"


span_io_value_one_of_1_t* instantiate_span_io_value_one_of_1(int include_optional) {
  span_io_value_one_of_1_t* span_io_value_one_of_1 = NULL;
  if (include_optional) {
    span_io_value_one_of_1 = span_io_value_one_of_1_create(
       // false, not to have infinite recursion
      instantiate_artifact_ref(0),
      beater_api_span_io_value_one_of_1_KIND_artifact
    );
  } else {
    span_io_value_one_of_1 = span_io_value_one_of_1_create(
      NULL,
      beater_api_span_io_value_one_of_1_KIND_artifact
    );
  }

  return span_io_value_one_of_1;
}


#ifdef span_io_value_one_of_1_MAIN

void test_span_io_value_one_of_1(int include_optional) {
    span_io_value_one_of_1_t* span_io_value_one_of_1_1 = instantiate_span_io_value_one_of_1(include_optional);

	cJSON* jsonspan_io_value_one_of_1_1 = span_io_value_one_of_1_convertToJSON(span_io_value_one_of_1_1);
	printf("span_io_value_one_of_1 :\n%s\n", cJSON_Print(jsonspan_io_value_one_of_1_1));
	span_io_value_one_of_1_t* span_io_value_one_of_1_2 = span_io_value_one_of_1_parseFromJSON(jsonspan_io_value_one_of_1_1);
	cJSON* jsonspan_io_value_one_of_1_2 = span_io_value_one_of_1_convertToJSON(span_io_value_one_of_1_2);
	printf("repeating span_io_value_one_of_1:\n%s\n", cJSON_Print(jsonspan_io_value_one_of_1_2));
}

int main() {
  test_span_io_value_one_of_1(1);
  test_span_io_value_one_of_1(0);

  printf("Hello world \n");
  return 0;
}

#endif // span_io_value_one_of_1_MAIN
#endif // span_io_value_one_of_1_TEST
