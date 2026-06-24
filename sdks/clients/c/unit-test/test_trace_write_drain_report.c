#ifndef trace_write_drain_report_TEST
#define trace_write_drain_report_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define trace_write_drain_report_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/trace_write_drain_report.h"
trace_write_drain_report_t* instantiate_trace_write_drain_report(int include_optional);



trace_write_drain_report_t* instantiate_trace_write_drain_report(int include_optional) {
  trace_write_drain_report_t* trace_write_drain_report = NULL;
  if (include_optional) {
    trace_write_drain_report = trace_write_drain_report_create(
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      list_createList(),
      list_createList(),
      0,
      0
    );
  } else {
    trace_write_drain_report = trace_write_drain_report_create(
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      list_createList(),
      list_createList(),
      0,
      0
    );
  }

  return trace_write_drain_report;
}


#ifdef trace_write_drain_report_MAIN

void test_trace_write_drain_report(int include_optional) {
    trace_write_drain_report_t* trace_write_drain_report_1 = instantiate_trace_write_drain_report(include_optional);

	cJSON* jsontrace_write_drain_report_1 = trace_write_drain_report_convertToJSON(trace_write_drain_report_1);
	printf("trace_write_drain_report :\n%s\n", cJSON_Print(jsontrace_write_drain_report_1));
	trace_write_drain_report_t* trace_write_drain_report_2 = trace_write_drain_report_parseFromJSON(jsontrace_write_drain_report_1);
	cJSON* jsontrace_write_drain_report_2 = trace_write_drain_report_convertToJSON(trace_write_drain_report_2);
	printf("repeating trace_write_drain_report:\n%s\n", cJSON_Print(jsontrace_write_drain_report_2));
}

int main() {
  test_trace_write_drain_report(1);
  test_trace_write_drain_report(0);

  printf("Hello world \n");
  return 0;
}

#endif // trace_write_drain_report_MAIN
#endif // trace_write_drain_report_TEST
