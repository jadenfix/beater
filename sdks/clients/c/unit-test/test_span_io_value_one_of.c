#ifndef span_io_value_one_of_TEST
#define span_io_value_one_of_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define span_io_value_one_of_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/span_io_value_one_of.h"
span_io_value_one_of_t* instantiate_span_io_value_one_of(int include_optional);



span_io_value_one_of_t* instantiate_span_io_value_one_of(int include_optional) {
  span_io_value_one_of_t* span_io_value_one_of = NULL;
  if (include_optional) {
    span_io_value_one_of = span_io_value_one_of_create(
      beater_api_span_io_value_one_of_KIND_inline,
      null
    );
  } else {
    span_io_value_one_of = span_io_value_one_of_create(
      beater_api_span_io_value_one_of_KIND_inline,
      null
    );
  }

  return span_io_value_one_of;
}


#ifdef span_io_value_one_of_MAIN

void test_span_io_value_one_of(int include_optional) {
    span_io_value_one_of_t* span_io_value_one_of_1 = instantiate_span_io_value_one_of(include_optional);

	cJSON* jsonspan_io_value_one_of_1 = span_io_value_one_of_convertToJSON(span_io_value_one_of_1);
	printf("span_io_value_one_of :\n%s\n", cJSON_Print(jsonspan_io_value_one_of_1));
	span_io_value_one_of_t* span_io_value_one_of_2 = span_io_value_one_of_parseFromJSON(jsonspan_io_value_one_of_1);
	cJSON* jsonspan_io_value_one_of_2 = span_io_value_one_of_convertToJSON(span_io_value_one_of_2);
	printf("repeating span_io_value_one_of:\n%s\n", cJSON_Print(jsonspan_io_value_one_of_2));
}

int main() {
  test_span_io_value_one_of(1);
  test_span_io_value_one_of(0);

  printf("Hello world \n");
  return 0;
}

#endif // span_io_value_one_of_MAIN
#endif // span_io_value_one_of_TEST
