#ifndef trace_view_TEST
#define trace_view_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define trace_view_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/trace_view.h"
trace_view_t* instantiate_trace_view(int include_optional);



trace_view_t* instantiate_trace_view(int include_optional) {
  trace_view_t* trace_view = NULL;
  if (include_optional) {
    trace_view = trace_view_create(
      list_createList(),
      "0",
      "0"
    );
  } else {
    trace_view = trace_view_create(
      list_createList(),
      "0",
      "0"
    );
  }

  return trace_view;
}


#ifdef trace_view_MAIN

void test_trace_view(int include_optional) {
    trace_view_t* trace_view_1 = instantiate_trace_view(include_optional);

	cJSON* jsontrace_view_1 = trace_view_convertToJSON(trace_view_1);
	printf("trace_view :\n%s\n", cJSON_Print(jsontrace_view_1));
	trace_view_t* trace_view_2 = trace_view_parseFromJSON(jsontrace_view_1);
	cJSON* jsontrace_view_2 = trace_view_convertToJSON(trace_view_2);
	printf("repeating trace_view:\n%s\n", cJSON_Print(jsontrace_view_2));
}

int main() {
  test_trace_view(1);
  test_trace_view(0);

  printf("Hello world \n");
  return 0;
}

#endif // trace_view_MAIN
#endif // trace_view_TEST
