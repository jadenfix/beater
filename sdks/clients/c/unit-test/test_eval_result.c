#ifndef eval_result_TEST
#define eval_result_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define eval_result_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/eval_result.h"
eval_result_t* instantiate_eval_result(int include_optional);

#include "test_money.c"
#include "test_eval_reproducibility.c"
#include "test_token_counts.c"


eval_result_t* instantiate_eval_result(int include_optional) {
  eval_result_t* eval_result = NULL;
  if (include_optional) {
    eval_result = eval_result_create(
       // false, not to have infinite recursion
      instantiate_money(0),
      "2013-10-20T19:20:30+01:00",
      "0",
      null,
      "0",
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_eval_reproducibility(0),
      1.337,
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_token_counts(0),
      "0"
    );
  } else {
    eval_result = eval_result_create(
      NULL,
      "2013-10-20T19:20:30+01:00",
      "0",
      null,
      "0",
      "0",
      "0",
      NULL,
      1.337,
      "0",
      "0",
      NULL,
      "0"
    );
  }

  return eval_result;
}


#ifdef eval_result_MAIN

void test_eval_result(int include_optional) {
    eval_result_t* eval_result_1 = instantiate_eval_result(include_optional);

	cJSON* jsoneval_result_1 = eval_result_convertToJSON(eval_result_1);
	printf("eval_result :\n%s\n", cJSON_Print(jsoneval_result_1));
	eval_result_t* eval_result_2 = eval_result_parseFromJSON(jsoneval_result_1);
	cJSON* jsoneval_result_2 = eval_result_convertToJSON(eval_result_2);
	printf("repeating eval_result:\n%s\n", cJSON_Print(jsoneval_result_2));
}

int main() {
  test_eval_result(1);
  test_eval_result(0);

  printf("Hello world \n");
  return 0;
}

#endif // eval_result_MAIN
#endif // eval_result_TEST
