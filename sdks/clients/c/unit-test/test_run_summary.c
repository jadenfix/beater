#ifndef run_summary_TEST
#define run_summary_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define run_summary_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/run_summary.h"
run_summary_t* instantiate_run_summary(int include_optional);

#include "test_money.c"
#include "test_rollup_estimate.c"


run_summary_t* instantiate_run_summary(int include_optional) {
  run_summary_t* run_summary = NULL;
  if (include_optional) {
    run_summary = run_summary_create(
      56,
      "2013-10-20T19:20:30+01:00",
      "0",
      list_createList(),
      "0",
      list_createList(),
      0,
      "2013-10-20T19:20:30+01:00",
      beater_api_run_summary__ok,
      "0",
       // false, not to have infinite recursion
      instantiate_money(0),
       // false, not to have infinite recursion
      instantiate_rollup_estimate(0),
      "0"
    );
  } else {
    run_summary = run_summary_create(
      56,
      "2013-10-20T19:20:30+01:00",
      "0",
      list_createList(),
      "0",
      list_createList(),
      0,
      "2013-10-20T19:20:30+01:00",
      beater_api_run_summary__ok,
      "0",
      NULL,
      NULL,
      "0"
    );
  }

  return run_summary;
}


#ifdef run_summary_MAIN

void test_run_summary(int include_optional) {
    run_summary_t* run_summary_1 = instantiate_run_summary(include_optional);

	cJSON* jsonrun_summary_1 = run_summary_convertToJSON(run_summary_1);
	printf("run_summary :\n%s\n", cJSON_Print(jsonrun_summary_1));
	run_summary_t* run_summary_2 = run_summary_parseFromJSON(jsonrun_summary_1);
	cJSON* jsonrun_summary_2 = run_summary_convertToJSON(run_summary_2);
	printf("repeating run_summary:\n%s\n", cJSON_Print(jsonrun_summary_2));
}

int main() {
  test_run_summary(1);
  test_run_summary(0);

  printf("Hello world \n");
  return 0;
}

#endif // run_summary_MAIN
#endif // run_summary_TEST
