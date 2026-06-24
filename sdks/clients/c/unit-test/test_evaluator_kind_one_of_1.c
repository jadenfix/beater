#ifndef evaluator_kind_one_of_1_TEST
#define evaluator_kind_one_of_1_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define evaluator_kind_one_of_1_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/evaluator_kind_one_of_1.h"
evaluator_kind_one_of_1_t* instantiate_evaluator_kind_one_of_1(int include_optional);



evaluator_kind_one_of_1_t* instantiate_evaluator_kind_one_of_1(int include_optional) {
  evaluator_kind_one_of_1_t* evaluator_kind_one_of_1 = NULL;
  if (include_optional) {
    evaluator_kind_one_of_1 = evaluator_kind_one_of_1_create(
      "0",
      beater_api_evaluator_kind_one_of_1_TYPE_regex_match
    );
  } else {
    evaluator_kind_one_of_1 = evaluator_kind_one_of_1_create(
      "0",
      beater_api_evaluator_kind_one_of_1_TYPE_regex_match
    );
  }

  return evaluator_kind_one_of_1;
}


#ifdef evaluator_kind_one_of_1_MAIN

void test_evaluator_kind_one_of_1(int include_optional) {
    evaluator_kind_one_of_1_t* evaluator_kind_one_of_1_1 = instantiate_evaluator_kind_one_of_1(include_optional);

	cJSON* jsonevaluator_kind_one_of_1_1 = evaluator_kind_one_of_1_convertToJSON(evaluator_kind_one_of_1_1);
	printf("evaluator_kind_one_of_1 :\n%s\n", cJSON_Print(jsonevaluator_kind_one_of_1_1));
	evaluator_kind_one_of_1_t* evaluator_kind_one_of_1_2 = evaluator_kind_one_of_1_parseFromJSON(jsonevaluator_kind_one_of_1_1);
	cJSON* jsonevaluator_kind_one_of_1_2 = evaluator_kind_one_of_1_convertToJSON(evaluator_kind_one_of_1_2);
	printf("repeating evaluator_kind_one_of_1:\n%s\n", cJSON_Print(jsonevaluator_kind_one_of_1_2));
}

int main() {
  test_evaluator_kind_one_of_1(1);
  test_evaluator_kind_one_of_1(0);

  printf("Hello world \n");
  return 0;
}

#endif // evaluator_kind_one_of_1_MAIN
#endif // evaluator_kind_one_of_1_TEST
