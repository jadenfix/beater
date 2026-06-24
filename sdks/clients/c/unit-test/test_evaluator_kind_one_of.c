#ifndef evaluator_kind_one_of_TEST
#define evaluator_kind_one_of_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define evaluator_kind_one_of_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/evaluator_kind_one_of.h"
evaluator_kind_one_of_t* instantiate_evaluator_kind_one_of(int include_optional);



evaluator_kind_one_of_t* instantiate_evaluator_kind_one_of(int include_optional) {
  evaluator_kind_one_of_t* evaluator_kind_one_of = NULL;
  if (include_optional) {
    evaluator_kind_one_of = evaluator_kind_one_of_create(
      beater_api_evaluator_kind_one_of_TYPE_exact_match
    );
  } else {
    evaluator_kind_one_of = evaluator_kind_one_of_create(
      beater_api_evaluator_kind_one_of_TYPE_exact_match
    );
  }

  return evaluator_kind_one_of;
}


#ifdef evaluator_kind_one_of_MAIN

void test_evaluator_kind_one_of(int include_optional) {
    evaluator_kind_one_of_t* evaluator_kind_one_of_1 = instantiate_evaluator_kind_one_of(include_optional);

	cJSON* jsonevaluator_kind_one_of_1 = evaluator_kind_one_of_convertToJSON(evaluator_kind_one_of_1);
	printf("evaluator_kind_one_of :\n%s\n", cJSON_Print(jsonevaluator_kind_one_of_1));
	evaluator_kind_one_of_t* evaluator_kind_one_of_2 = evaluator_kind_one_of_parseFromJSON(jsonevaluator_kind_one_of_1);
	cJSON* jsonevaluator_kind_one_of_2 = evaluator_kind_one_of_convertToJSON(evaluator_kind_one_of_2);
	printf("repeating evaluator_kind_one_of:\n%s\n", cJSON_Print(jsonevaluator_kind_one_of_2));
}

int main() {
  test_evaluator_kind_one_of(1);
  test_evaluator_kind_one_of(0);

  printf("Hello world \n");
  return 0;
}

#endif // evaluator_kind_one_of_MAIN
#endif // evaluator_kind_one_of_TEST
