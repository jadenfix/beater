#ifndef span_status_TEST
#define span_status_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define span_status_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/span_status.h"
span_status_t* instantiate_span_status(int include_optional);



span_status_t* instantiate_span_status(int include_optional) {
  span_status_t* span_status = NULL;
  if (include_optional) {
    span_status = span_status_create(
    );
  } else {
    span_status = span_status_create(
    );
  }

  return span_status;
}


#ifdef span_status_MAIN

void test_span_status(int include_optional) {
    span_status_t* span_status_1 = instantiate_span_status(include_optional);

	cJSON* jsonspan_status_1 = span_status_convertToJSON(span_status_1);
	printf("span_status :\n%s\n", cJSON_Print(jsonspan_status_1));
	span_status_t* span_status_2 = span_status_parseFromJSON(jsonspan_status_1);
	cJSON* jsonspan_status_2 = span_status_convertToJSON(span_status_2);
	printf("repeating span_status:\n%s\n", cJSON_Print(jsonspan_status_2));
}

int main() {
  test_span_status(1);
  test_span_status(0);

  printf("Hello world \n");
  return 0;
}

#endif // span_status_MAIN
#endif // span_status_TEST
