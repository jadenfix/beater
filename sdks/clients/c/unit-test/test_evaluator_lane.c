#ifndef evaluator_lane_TEST
#define evaluator_lane_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define evaluator_lane_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/evaluator_lane.h"
evaluator_lane_t* instantiate_evaluator_lane(int include_optional);



evaluator_lane_t* instantiate_evaluator_lane(int include_optional) {
  evaluator_lane_t* evaluator_lane = NULL;
  if (include_optional) {
    evaluator_lane = evaluator_lane_create(
    );
  } else {
    evaluator_lane = evaluator_lane_create(
    );
  }

  return evaluator_lane;
}


#ifdef evaluator_lane_MAIN

void test_evaluator_lane(int include_optional) {
    evaluator_lane_t* evaluator_lane_1 = instantiate_evaluator_lane(include_optional);

	cJSON* jsonevaluator_lane_1 = evaluator_lane_convertToJSON(evaluator_lane_1);
	printf("evaluator_lane :\n%s\n", cJSON_Print(jsonevaluator_lane_1));
	evaluator_lane_t* evaluator_lane_2 = evaluator_lane_parseFromJSON(jsonevaluator_lane_1);
	cJSON* jsonevaluator_lane_2 = evaluator_lane_convertToJSON(evaluator_lane_2);
	printf("repeating evaluator_lane:\n%s\n", cJSON_Print(jsonevaluator_lane_2));
}

int main() {
  test_evaluator_lane(1);
  test_evaluator_lane(0);

  printf("Hello world \n");
  return 0;
}

#endif // evaluator_lane_MAIN
#endif // evaluator_lane_TEST
