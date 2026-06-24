#ifndef trace_ingested_reconcile_report_TEST
#define trace_ingested_reconcile_report_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define trace_ingested_reconcile_report_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/trace_ingested_reconcile_report.h"
trace_ingested_reconcile_report_t* instantiate_trace_ingested_reconcile_report(int include_optional);



trace_ingested_reconcile_report_t* instantiate_trace_ingested_reconcile_report(int include_optional) {
  trace_ingested_reconcile_report_t* trace_ingested_reconcile_report = NULL;
  if (include_optional) {
    trace_ingested_reconcile_report = trace_ingested_reconcile_report_create(
      0,
      0,
      1,
      "0",
      0,
      "0",
      "0"
    );
  } else {
    trace_ingested_reconcile_report = trace_ingested_reconcile_report_create(
      0,
      0,
      1,
      "0",
      0,
      "0",
      "0"
    );
  }

  return trace_ingested_reconcile_report;
}


#ifdef trace_ingested_reconcile_report_MAIN

void test_trace_ingested_reconcile_report(int include_optional) {
    trace_ingested_reconcile_report_t* trace_ingested_reconcile_report_1 = instantiate_trace_ingested_reconcile_report(include_optional);

	cJSON* jsontrace_ingested_reconcile_report_1 = trace_ingested_reconcile_report_convertToJSON(trace_ingested_reconcile_report_1);
	printf("trace_ingested_reconcile_report :\n%s\n", cJSON_Print(jsontrace_ingested_reconcile_report_1));
	trace_ingested_reconcile_report_t* trace_ingested_reconcile_report_2 = trace_ingested_reconcile_report_parseFromJSON(jsontrace_ingested_reconcile_report_1);
	cJSON* jsontrace_ingested_reconcile_report_2 = trace_ingested_reconcile_report_convertToJSON(trace_ingested_reconcile_report_2);
	printf("repeating trace_ingested_reconcile_report:\n%s\n", cJSON_Print(jsontrace_ingested_reconcile_report_2));
}

int main() {
  test_trace_ingested_reconcile_report(1);
  test_trace_ingested_reconcile_report(0);

  printf("Hello world \n");
  return 0;
}

#endif // trace_ingested_reconcile_report_MAIN
#endif // trace_ingested_reconcile_report_TEST
