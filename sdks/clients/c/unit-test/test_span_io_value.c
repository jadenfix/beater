#ifndef span_io_value_TEST
#define span_io_value_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define span_io_value_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/span_io_value.h"
span_io_value_t* instantiate_span_io_value(int include_optional);

#include "test_artifact_ref.c"


span_io_value_t* instantiate_span_io_value(int include_optional) {
  span_io_value_t* span_io_value = NULL;
  if (include_optional) {
    span_io_value = span_io_value_create(
      beater_api_span_io_value_KIND_missing,
      null,
       // false, not to have infinite recursion
      instantiate_artifact_ref(0),
      "0"
    );
  } else {
    span_io_value = span_io_value_create(
      beater_api_span_io_value_KIND_missing,
      null,
      NULL,
      "0"
    );
  }

  return span_io_value;
}


#ifdef span_io_value_MAIN

void test_span_io_value(int include_optional) {
    span_io_value_t* span_io_value_1 = instantiate_span_io_value(include_optional);

	cJSON* jsonspan_io_value_1 = span_io_value_convertToJSON(span_io_value_1);
	printf("span_io_value :\n%s\n", cJSON_Print(jsonspan_io_value_1));
	span_io_value_t* span_io_value_2 = span_io_value_parseFromJSON(jsonspan_io_value_1);
	cJSON* jsonspan_io_value_2 = span_io_value_convertToJSON(span_io_value_2);
	printf("repeating span_io_value:\n%s\n", cJSON_Print(jsonspan_io_value_2));
}

int main() {
  test_span_io_value(1);
  test_span_io_value(0);

  printf("Hello world \n");
  return 0;
}

#endif // span_io_value_MAIN
#endif // span_io_value_TEST
