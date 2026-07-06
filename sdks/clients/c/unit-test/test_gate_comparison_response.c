#ifndef gate_comparison_response_TEST
#define gate_comparison_response_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_comparison_response_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_comparison_response.h"
gate_comparison_response_t* instantiate_gate_comparison_response(int include_optional);



gate_comparison_response_t* instantiate_gate_comparison_response(int include_optional) {
  gate_comparison_response_t* gate_comparison_response = NULL;
  if (include_optional) {
    gate_comparison_response = gate_comparison_response_create(
      1.337,
      1.337,
      1.337,
      1.337,
      beater_api_gate_comparison_response__pass,
      1.337,
      1.337,
      0
    );
  } else {
    gate_comparison_response = gate_comparison_response_create(
      1.337,
      1.337,
      1.337,
      1.337,
      beater_api_gate_comparison_response__pass,
      1.337,
      1.337,
      0
    );
  }

  return gate_comparison_response;
}


#ifdef gate_comparison_response_MAIN

void test_gate_comparison_response(int include_optional) {
    gate_comparison_response_t* gate_comparison_response_1 = instantiate_gate_comparison_response(include_optional);

	cJSON* jsongate_comparison_response_1 = gate_comparison_response_convertToJSON(gate_comparison_response_1);
	printf("gate_comparison_response :\n%s\n", cJSON_Print(jsongate_comparison_response_1));
	gate_comparison_response_t* gate_comparison_response_2 = gate_comparison_response_parseFromJSON(jsongate_comparison_response_1);
	cJSON* jsongate_comparison_response_2 = gate_comparison_response_convertToJSON(gate_comparison_response_2);
	printf("repeating gate_comparison_response:\n%s\n", cJSON_Print(jsongate_comparison_response_2));
}

int main() {
  test_gate_comparison_response(1);
  test_gate_comparison_response(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_comparison_response_MAIN
#endif // gate_comparison_response_TEST
