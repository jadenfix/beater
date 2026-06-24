#ifndef score_result_TEST
#define score_result_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define score_result_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/score_result.h"
score_result_t* instantiate_score_result(int include_optional);



score_result_t* instantiate_score_result(int include_optional) {
  score_result_t* score_result = NULL;
  if (include_optional) {
    score_result = score_result_create(
      null,
      "0",
      1.337
    );
  } else {
    score_result = score_result_create(
      null,
      "0",
      1.337
    );
  }

  return score_result;
}


#ifdef score_result_MAIN

void test_score_result(int include_optional) {
    score_result_t* score_result_1 = instantiate_score_result(include_optional);

	cJSON* jsonscore_result_1 = score_result_convertToJSON(score_result_1);
	printf("score_result :\n%s\n", cJSON_Print(jsonscore_result_1));
	score_result_t* score_result_2 = score_result_parseFromJSON(jsonscore_result_1);
	cJSON* jsonscore_result_2 = score_result_convertToJSON(score_result_2);
	printf("repeating score_result:\n%s\n", cJSON_Print(jsonscore_result_2));
}

int main() {
  test_score_result(1);
  test_score_result(0);

  printf("Hello world \n");
  return 0;
}

#endif // score_result_MAIN
#endif // score_result_TEST
