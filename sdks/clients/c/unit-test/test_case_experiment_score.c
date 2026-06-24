#ifndef case_experiment_score_TEST
#define case_experiment_score_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define case_experiment_score_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/case_experiment_score.h"
case_experiment_score_t* instantiate_case_experiment_score(int include_optional);

#include "test_money.c"
#include "test_money.c"


case_experiment_score_t* instantiate_case_experiment_score(int include_optional) {
  case_experiment_score_t* case_experiment_score = NULL;
  if (include_optional) {
    case_experiment_score = case_experiment_score_create(
      1,
       // false, not to have infinite recursion
      instantiate_money(0),
      null,
      "0",
      null,
      1.337,
      null,
      1,
       // false, not to have infinite recursion
      instantiate_money(0),
      null,
      "0",
      null,
      1.337,
      null,
      "0",
      1.337,
      null
    );
  } else {
    case_experiment_score = case_experiment_score_create(
      1,
      NULL,
      null,
      "0",
      null,
      1.337,
      null,
      1,
      NULL,
      null,
      "0",
      null,
      1.337,
      null,
      "0",
      1.337,
      null
    );
  }

  return case_experiment_score;
}


#ifdef case_experiment_score_MAIN

void test_case_experiment_score(int include_optional) {
    case_experiment_score_t* case_experiment_score_1 = instantiate_case_experiment_score(include_optional);

	cJSON* jsoncase_experiment_score_1 = case_experiment_score_convertToJSON(case_experiment_score_1);
	printf("case_experiment_score :\n%s\n", cJSON_Print(jsoncase_experiment_score_1));
	case_experiment_score_t* case_experiment_score_2 = case_experiment_score_parseFromJSON(jsoncase_experiment_score_1);
	cJSON* jsoncase_experiment_score_2 = case_experiment_score_convertToJSON(case_experiment_score_2);
	printf("repeating case_experiment_score:\n%s\n", cJSON_Print(jsoncase_experiment_score_2));
}

int main() {
  test_case_experiment_score(1);
  test_case_experiment_score(0);

  printf("Hello world \n");
  return 0;
}

#endif // case_experiment_score_MAIN
#endif // case_experiment_score_TEST
