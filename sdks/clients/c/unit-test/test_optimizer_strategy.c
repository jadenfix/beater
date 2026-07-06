#ifndef optimizer_strategy_TEST
#define optimizer_strategy_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define optimizer_strategy_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/optimizer_strategy.h"
optimizer_strategy_t* instantiate_optimizer_strategy(int include_optional);



optimizer_strategy_t* instantiate_optimizer_strategy(int include_optional) {
  optimizer_strategy_t* optimizer_strategy = NULL;
  if (include_optional) {
    optimizer_strategy = optimizer_strategy_create(
    );
  } else {
    optimizer_strategy = optimizer_strategy_create(
    );
  }

  return optimizer_strategy;
}


#ifdef optimizer_strategy_MAIN

void test_optimizer_strategy(int include_optional) {
    optimizer_strategy_t* optimizer_strategy_1 = instantiate_optimizer_strategy(include_optional);

	cJSON* jsonoptimizer_strategy_1 = optimizer_strategy_convertToJSON(optimizer_strategy_1);
	printf("optimizer_strategy :\n%s\n", cJSON_Print(jsonoptimizer_strategy_1));
	optimizer_strategy_t* optimizer_strategy_2 = optimizer_strategy_parseFromJSON(jsonoptimizer_strategy_1);
	cJSON* jsonoptimizer_strategy_2 = optimizer_strategy_convertToJSON(optimizer_strategy_2);
	printf("repeating optimizer_strategy:\n%s\n", cJSON_Print(jsonoptimizer_strategy_2));
}

int main() {
  test_optimizer_strategy(1);
  test_optimizer_strategy(0);

  printf("Hello world \n");
  return 0;
}

#endif // optimizer_strategy_MAIN
#endif // optimizer_strategy_TEST
