#ifndef span_io_response_TEST
#define span_io_response_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define span_io_response_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/span_io_response.h"
span_io_response_t* instantiate_span_io_response(int include_optional);

#include "test_span_io_value.c"
#include "test_span_io_value.c"


span_io_response_t* instantiate_span_io_response(int include_optional) {
  span_io_response_t* span_io_response = NULL;
  if (include_optional) {
    span_io_response = span_io_response_create(
      null,
      null,
      "0",
      "0",
      "0"
    );
  } else {
    span_io_response = span_io_response_create(
      null,
      null,
      "0",
      "0",
      "0"
    );
  }

  return span_io_response;
}


#ifdef span_io_response_MAIN

void test_span_io_response(int include_optional) {
    span_io_response_t* span_io_response_1 = instantiate_span_io_response(include_optional);

	cJSON* jsonspan_io_response_1 = span_io_response_convertToJSON(span_io_response_1);
	printf("span_io_response :\n%s\n", cJSON_Print(jsonspan_io_response_1));
	span_io_response_t* span_io_response_2 = span_io_response_parseFromJSON(jsonspan_io_response_1);
	cJSON* jsonspan_io_response_2 = span_io_response_convertToJSON(span_io_response_2);
	printf("repeating span_io_response:\n%s\n", cJSON_Print(jsonspan_io_response_2));
}

int main() {
  test_span_io_response(1);
  test_span_io_response(0);

  printf("Hello world \n");
  return 0;
}

#endif // span_io_response_MAIN
#endif // span_io_response_TEST
