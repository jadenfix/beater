#ifndef run_judge_dataset_eval_request_TEST
#define run_judge_dataset_eval_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define run_judge_dataset_eval_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/run_judge_dataset_eval_request.h"
run_judge_dataset_eval_request_t* instantiate_run_judge_dataset_eval_request(int include_optional);

#include "test_evaluator_kind.c"


run_judge_dataset_eval_request_t* instantiate_run_judge_dataset_eval_request(int include_optional) {
  run_judge_dataset_eval_request_t* run_judge_dataset_eval_request = NULL;
  if (include_optional) {
    run_judge_dataset_eval_request = run_judge_dataset_eval_request_create(
      "0",
      "0",
      "0",
      "0",
      null,
      "0",
      "0"
    );
  } else {
    run_judge_dataset_eval_request = run_judge_dataset_eval_request_create(
      "0",
      "0",
      "0",
      "0",
      null,
      "0",
      "0"
    );
  }

  return run_judge_dataset_eval_request;
}


#ifdef run_judge_dataset_eval_request_MAIN

void test_run_judge_dataset_eval_request(int include_optional) {
    run_judge_dataset_eval_request_t* run_judge_dataset_eval_request_1 = instantiate_run_judge_dataset_eval_request(include_optional);

	cJSON* jsonrun_judge_dataset_eval_request_1 = run_judge_dataset_eval_request_convertToJSON(run_judge_dataset_eval_request_1);
	printf("run_judge_dataset_eval_request :\n%s\n", cJSON_Print(jsonrun_judge_dataset_eval_request_1));
	run_judge_dataset_eval_request_t* run_judge_dataset_eval_request_2 = run_judge_dataset_eval_request_parseFromJSON(jsonrun_judge_dataset_eval_request_1);
	cJSON* jsonrun_judge_dataset_eval_request_2 = run_judge_dataset_eval_request_convertToJSON(run_judge_dataset_eval_request_2);
	printf("repeating run_judge_dataset_eval_request:\n%s\n", cJSON_Print(jsonrun_judge_dataset_eval_request_2));
}

int main() {
  test_run_judge_dataset_eval_request(1);
  test_run_judge_dataset_eval_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // run_judge_dataset_eval_request_MAIN
#endif // run_judge_dataset_eval_request_TEST
