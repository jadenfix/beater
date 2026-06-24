#ifndef gate_decision_TEST
#define gate_decision_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_decision_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_decision.h"
gate_decision_t* instantiate_gate_decision(int include_optional);



gate_decision_t* instantiate_gate_decision(int include_optional) {
  gate_decision_t* gate_decision = NULL;
  if (include_optional) {
    gate_decision = gate_decision_create(
    );
  } else {
    gate_decision = gate_decision_create(
    );
  }

  return gate_decision;
}


#ifdef gate_decision_MAIN

void test_gate_decision(int include_optional) {
    gate_decision_t* gate_decision_1 = instantiate_gate_decision(include_optional);

	cJSON* jsongate_decision_1 = gate_decision_convertToJSON(gate_decision_1);
	printf("gate_decision :\n%s\n", cJSON_Print(jsongate_decision_1));
	gate_decision_t* gate_decision_2 = gate_decision_parseFromJSON(jsongate_decision_1);
	cJSON* jsongate_decision_2 = gate_decision_convertToJSON(gate_decision_2);
	printf("repeating gate_decision:\n%s\n", cJSON_Print(jsongate_decision_2));
}

int main() {
  test_gate_decision(1);
  test_gate_decision(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_decision_MAIN
#endif // gate_decision_TEST
