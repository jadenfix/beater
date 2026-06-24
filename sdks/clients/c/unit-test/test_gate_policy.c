#ifndef gate_policy_TEST
#define gate_policy_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_policy_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_policy.h"
gate_policy_t* instantiate_gate_policy(int include_optional);



gate_policy_t* instantiate_gate_policy(int include_optional) {
  gate_policy_t* gate_policy = NULL;
  if (include_optional) {
    gate_policy = gate_policy_create(
      1.337,
      0,
      1.337,
      0
    );
  } else {
    gate_policy = gate_policy_create(
      1.337,
      0,
      1.337,
      0
    );
  }

  return gate_policy;
}


#ifdef gate_policy_MAIN

void test_gate_policy(int include_optional) {
    gate_policy_t* gate_policy_1 = instantiate_gate_policy(include_optional);

	cJSON* jsongate_policy_1 = gate_policy_convertToJSON(gate_policy_1);
	printf("gate_policy :\n%s\n", cJSON_Print(jsongate_policy_1));
	gate_policy_t* gate_policy_2 = gate_policy_parseFromJSON(jsongate_policy_1);
	cJSON* jsongate_policy_2 = gate_policy_convertToJSON(gate_policy_2);
	printf("repeating gate_policy:\n%s\n", cJSON_Print(jsongate_policy_2));
}

int main() {
  test_gate_policy(1);
  test_gate_policy(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_policy_MAIN
#endif // gate_policy_TEST
