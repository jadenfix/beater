#ifndef span_io_value_one_of_3_TEST
#define span_io_value_one_of_3_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define span_io_value_one_of_3_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/span_io_value_one_of_3.h"
span_io_value_one_of_3_t* instantiate_span_io_value_one_of_3(int include_optional);



span_io_value_one_of_3_t* instantiate_span_io_value_one_of_3(int include_optional) {
  span_io_value_one_of_3_t* span_io_value_one_of_3 = NULL;
  if (include_optional) {
    span_io_value_one_of_3 = span_io_value_one_of_3_create(
      beater_api_span_io_value_one_of_3_KIND_missing
    );
  } else {
    span_io_value_one_of_3 = span_io_value_one_of_3_create(
      beater_api_span_io_value_one_of_3_KIND_missing
    );
  }

  return span_io_value_one_of_3;
}


#ifdef span_io_value_one_of_3_MAIN

void test_span_io_value_one_of_3(int include_optional) {
    span_io_value_one_of_3_t* span_io_value_one_of_3_1 = instantiate_span_io_value_one_of_3(include_optional);

	cJSON* jsonspan_io_value_one_of_3_1 = span_io_value_one_of_3_convertToJSON(span_io_value_one_of_3_1);
	printf("span_io_value_one_of_3 :\n%s\n", cJSON_Print(jsonspan_io_value_one_of_3_1));
	span_io_value_one_of_3_t* span_io_value_one_of_3_2 = span_io_value_one_of_3_parseFromJSON(jsonspan_io_value_one_of_3_1);
	cJSON* jsonspan_io_value_one_of_3_2 = span_io_value_one_of_3_convertToJSON(span_io_value_one_of_3_2);
	printf("repeating span_io_value_one_of_3:\n%s\n", cJSON_Print(jsonspan_io_value_one_of_3_2));
}

int main() {
  test_span_io_value_one_of_3(1);
  test_span_io_value_one_of_3(0);

  printf("Hello world \n");
  return 0;
}

#endif // span_io_value_one_of_3_MAIN
#endif // span_io_value_one_of_3_TEST
