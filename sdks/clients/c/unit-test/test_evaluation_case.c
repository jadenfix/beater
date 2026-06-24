#ifndef evaluation_case_TEST
#define evaluation_case_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define evaluation_case_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/evaluation_case.h"
evaluation_case_t* instantiate_evaluation_case(int include_optional);



evaluation_case_t* instantiate_evaluation_case(int include_optional) {
  evaluation_case_t* evaluation_case = NULL;
  if (include_optional) {
    evaluation_case = evaluation_case_create(
      null,
      null,
      null,
      null
    );
  } else {
    evaluation_case = evaluation_case_create(
      null,
      null,
      null,
      null
    );
  }

  return evaluation_case;
}


#ifdef evaluation_case_MAIN

void test_evaluation_case(int include_optional) {
    evaluation_case_t* evaluation_case_1 = instantiate_evaluation_case(include_optional);

	cJSON* jsonevaluation_case_1 = evaluation_case_convertToJSON(evaluation_case_1);
	printf("evaluation_case :\n%s\n", cJSON_Print(jsonevaluation_case_1));
	evaluation_case_t* evaluation_case_2 = evaluation_case_parseFromJSON(jsonevaluation_case_1);
	cJSON* jsonevaluation_case_2 = evaluation_case_convertToJSON(evaluation_case_2);
	printf("repeating evaluation_case:\n%s\n", cJSON_Print(jsonevaluation_case_2));
}

int main() {
  test_evaluation_case(1);
  test_evaluation_case(0);

  printf("Hello world \n");
  return 0;
}

#endif // evaluation_case_MAIN
#endif // evaluation_case_TEST
