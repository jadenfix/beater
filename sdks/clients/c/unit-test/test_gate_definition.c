#ifndef gate_definition_TEST
#define gate_definition_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_definition_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_definition.h"
gate_definition_t* instantiate_gate_definition(int include_optional);



gate_definition_t* instantiate_gate_definition(int include_optional) {
  gate_definition_t* gate_definition = NULL;
  if (include_optional) {
    gate_definition = gate_definition_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      beater_api_gate_definition__pass,
      "0",
      "0",
      "0"
    );
  } else {
    gate_definition = gate_definition_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      beater_api_gate_definition__pass,
      "0",
      "0",
      "0"
    );
  }

  return gate_definition;
}


#ifdef gate_definition_MAIN

void test_gate_definition(int include_optional) {
    gate_definition_t* gate_definition_1 = instantiate_gate_definition(include_optional);

	cJSON* jsongate_definition_1 = gate_definition_convertToJSON(gate_definition_1);
	printf("gate_definition :\n%s\n", cJSON_Print(jsongate_definition_1));
	gate_definition_t* gate_definition_2 = gate_definition_parseFromJSON(jsongate_definition_1);
	cJSON* jsongate_definition_2 = gate_definition_convertToJSON(gate_definition_2);
	printf("repeating gate_definition:\n%s\n", cJSON_Print(jsongate_definition_2));
}

int main() {
  test_gate_definition(1);
  test_gate_definition(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_definition_MAIN
#endif // gate_definition_TEST
