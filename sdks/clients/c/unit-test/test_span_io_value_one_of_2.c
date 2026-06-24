#ifndef span_io_value_one_of_2_TEST
#define span_io_value_one_of_2_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define span_io_value_one_of_2_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/span_io_value_one_of_2.h"
span_io_value_one_of_2_t* instantiate_span_io_value_one_of_2(int include_optional);



span_io_value_one_of_2_t* instantiate_span_io_value_one_of_2(int include_optional) {
  span_io_value_one_of_2_t* span_io_value_one_of_2 = NULL;
  if (include_optional) {
    span_io_value_one_of_2 = span_io_value_one_of_2_create(
      beater_api_span_io_value_one_of_2_KIND_redacted,
      "0"
    );
  } else {
    span_io_value_one_of_2 = span_io_value_one_of_2_create(
      beater_api_span_io_value_one_of_2_KIND_redacted,
      "0"
    );
  }

  return span_io_value_one_of_2;
}


#ifdef span_io_value_one_of_2_MAIN

void test_span_io_value_one_of_2(int include_optional) {
    span_io_value_one_of_2_t* span_io_value_one_of_2_1 = instantiate_span_io_value_one_of_2(include_optional);

	cJSON* jsonspan_io_value_one_of_2_1 = span_io_value_one_of_2_convertToJSON(span_io_value_one_of_2_1);
	printf("span_io_value_one_of_2 :\n%s\n", cJSON_Print(jsonspan_io_value_one_of_2_1));
	span_io_value_one_of_2_t* span_io_value_one_of_2_2 = span_io_value_one_of_2_parseFromJSON(jsonspan_io_value_one_of_2_1);
	cJSON* jsonspan_io_value_one_of_2_2 = span_io_value_one_of_2_convertToJSON(span_io_value_one_of_2_2);
	printf("repeating span_io_value_one_of_2:\n%s\n", cJSON_Print(jsonspan_io_value_one_of_2_2));
}

int main() {
  test_span_io_value_one_of_2(1);
  test_span_io_value_one_of_2(0);

  printf("Hello world \n");
  return 0;
}

#endif // span_io_value_one_of_2_MAIN
#endif // span_io_value_one_of_2_TEST
