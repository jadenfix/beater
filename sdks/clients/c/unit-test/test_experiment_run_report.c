#ifndef experiment_run_report_TEST
#define experiment_run_report_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define experiment_run_report_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/experiment_run_report.h"
experiment_run_report_t* instantiate_experiment_run_report(int include_optional);

#include "test_experiment_comparison.c"
#include "test_gate_policy.c"


experiment_run_report_t* instantiate_experiment_run_report(int include_optional) {
  experiment_run_report_t* experiment_run_report = NULL;
  if (include_optional) {
    experiment_run_report = experiment_run_report_create(
      "0",
      "0",
      list_createList(),
       // false, not to have infinite recursion
      instantiate_experiment_comparison(0),
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      beater_api_experiment_run_report__pass,
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_gate_policy(0),
      "0",
      "0"
    );
  } else {
    experiment_run_report = experiment_run_report_create(
      "0",
      "0",
      list_createList(),
      NULL,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      beater_api_experiment_run_report__pass,
      "0",
      "0",
      NULL,
      "0",
      "0"
    );
  }

  return experiment_run_report;
}


#ifdef experiment_run_report_MAIN

void test_experiment_run_report(int include_optional) {
    experiment_run_report_t* experiment_run_report_1 = instantiate_experiment_run_report(include_optional);

	cJSON* jsonexperiment_run_report_1 = experiment_run_report_convertToJSON(experiment_run_report_1);
	printf("experiment_run_report :\n%s\n", cJSON_Print(jsonexperiment_run_report_1));
	experiment_run_report_t* experiment_run_report_2 = experiment_run_report_parseFromJSON(jsonexperiment_run_report_1);
	cJSON* jsonexperiment_run_report_2 = experiment_run_report_convertToJSON(experiment_run_report_2);
	printf("repeating experiment_run_report:\n%s\n", cJSON_Print(jsonexperiment_run_report_2));
}

int main() {
  test_experiment_run_report(1);
  test_experiment_run_report(0);

  printf("Hello world \n");
  return 0;
}

#endif // experiment_run_report_MAIN
#endif // experiment_run_report_TEST
