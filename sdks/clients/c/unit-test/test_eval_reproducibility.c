#ifndef eval_reproducibility_TEST
#define eval_reproducibility_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define eval_reproducibility_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/eval_reproducibility.h"
eval_reproducibility_t* instantiate_eval_reproducibility(int include_optional);



eval_reproducibility_t* instantiate_eval_reproducibility(int include_optional) {
  eval_reproducibility_t* eval_reproducibility = NULL;
  if (include_optional) {
    eval_reproducibility = eval_reproducibility_create(
      "0",
      "0",
      "0",
      "0",
      "0",
      list_createList(),
      "0",
      null,
      "0",
      "0",
      0,
      "0",
      "0",
      0,
      "0",
      "0"
    );
  } else {
    eval_reproducibility = eval_reproducibility_create(
      "0",
      "0",
      "0",
      "0",
      "0",
      list_createList(),
      "0",
      null,
      "0",
      "0",
      0,
      "0",
      "0",
      0,
      "0",
      "0"
    );
  }

  return eval_reproducibility;
}


#ifdef eval_reproducibility_MAIN

void test_eval_reproducibility(int include_optional) {
    eval_reproducibility_t* eval_reproducibility_1 = instantiate_eval_reproducibility(include_optional);

	cJSON* jsoneval_reproducibility_1 = eval_reproducibility_convertToJSON(eval_reproducibility_1);
	printf("eval_reproducibility :\n%s\n", cJSON_Print(jsoneval_reproducibility_1));
	eval_reproducibility_t* eval_reproducibility_2 = eval_reproducibility_parseFromJSON(jsoneval_reproducibility_1);
	cJSON* jsoneval_reproducibility_2 = eval_reproducibility_convertToJSON(eval_reproducibility_2);
	printf("repeating eval_reproducibility:\n%s\n", cJSON_Print(jsoneval_reproducibility_2));
}

int main() {
  test_eval_reproducibility(1);
  test_eval_reproducibility(0);

  printf("Hello world \n");
  return 0;
}

#endif // eval_reproducibility_MAIN
#endif // eval_reproducibility_TEST
