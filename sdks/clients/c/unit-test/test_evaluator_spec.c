#ifndef evaluator_spec_TEST
#define evaluator_spec_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define evaluator_spec_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/evaluator_spec.h"
evaluator_spec_t* instantiate_evaluator_spec(int include_optional);

#include "test_evaluator_kind.c"


evaluator_spec_t* instantiate_evaluator_spec(int include_optional) {
  evaluator_spec_t* evaluator_spec = NULL;
  if (include_optional) {
    evaluator_spec = evaluator_spec_create(
      "0",
      null,
      beater_api_evaluator_spec__deterministic_wasi
    );
  } else {
    evaluator_spec = evaluator_spec_create(
      "0",
      null,
      beater_api_evaluator_spec__deterministic_wasi
    );
  }

  return evaluator_spec;
}


#ifdef evaluator_spec_MAIN

void test_evaluator_spec(int include_optional) {
    evaluator_spec_t* evaluator_spec_1 = instantiate_evaluator_spec(include_optional);

	cJSON* jsonevaluator_spec_1 = evaluator_spec_convertToJSON(evaluator_spec_1);
	printf("evaluator_spec :\n%s\n", cJSON_Print(jsonevaluator_spec_1));
	evaluator_spec_t* evaluator_spec_2 = evaluator_spec_parseFromJSON(jsonevaluator_spec_1);
	cJSON* jsonevaluator_spec_2 = evaluator_spec_convertToJSON(evaluator_spec_2);
	printf("repeating evaluator_spec:\n%s\n", cJSON_Print(jsonevaluator_spec_2));
}

int main() {
  test_evaluator_spec(1);
  test_evaluator_spec(0);

  printf("Hello world \n");
  return 0;
}

#endif // evaluator_spec_MAIN
#endif // evaluator_spec_TEST
