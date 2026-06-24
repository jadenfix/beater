#ifndef gate_run_report_TEST
#define gate_run_report_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_run_report_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_run_report.h"
gate_run_report_t* instantiate_gate_run_report(int include_optional);

#include "test_experiment_comparison.c"
#include "test_gate_policy.c"


gate_run_report_t* instantiate_gate_run_report(int include_optional) {
  gate_run_report_t* gate_run_report = NULL;
  if (include_optional) {
    gate_run_report = gate_run_report_create(
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_experiment_comparison(0),
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "2013-10-20T19:20:30+01:00",
      beater_api_gate_run_report__pass,
       // false, not to have infinite recursion
      instantiate_gate_policy(0),
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      beater_api_gate_run_report__pass,
      1,
      "0",
      "0",
      "0"
    );
  } else {
    gate_run_report = gate_run_report_create(
      "0",
      "0",
      NULL,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "2013-10-20T19:20:30+01:00",
      beater_api_gate_run_report__pass,
      NULL,
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      beater_api_gate_run_report__pass,
      1,
      "0",
      "0",
      "0"
    );
  }

  return gate_run_report;
}


#ifdef gate_run_report_MAIN

void test_gate_run_report(int include_optional) {
    gate_run_report_t* gate_run_report_1 = instantiate_gate_run_report(include_optional);

	cJSON* jsongate_run_report_1 = gate_run_report_convertToJSON(gate_run_report_1);
	printf("gate_run_report :\n%s\n", cJSON_Print(jsongate_run_report_1));
	gate_run_report_t* gate_run_report_2 = gate_run_report_parseFromJSON(jsongate_run_report_1);
	cJSON* jsongate_run_report_2 = gate_run_report_convertToJSON(gate_run_report_2);
	printf("repeating gate_run_report:\n%s\n", cJSON_Print(jsongate_run_report_2));
}

int main() {
  test_gate_run_report(1);
  test_gate_run_report(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_run_report_MAIN
#endif // gate_run_report_TEST
