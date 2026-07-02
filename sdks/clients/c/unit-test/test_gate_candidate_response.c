#ifndef gate_candidate_response_TEST
#define gate_candidate_response_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_candidate_response_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_candidate_response.h"
gate_candidate_response_t* instantiate_gate_candidate_response(int include_optional);

#include "test_gate_comparison_response.c"
#include "test_overfit_response.c"


gate_candidate_response_t* instantiate_gate_candidate_response(int include_optional) {
  gate_candidate_response_t* gate_candidate_response = NULL;
  if (include_optional) {
    gate_candidate_response = gate_candidate_response_create(
      1,
       // false, not to have infinite recursion
      instantiate_gate_comparison_response(0),
       // false, not to have infinite recursion
      instantiate_overfit_response(0)
    );
  } else {
    gate_candidate_response = gate_candidate_response_create(
      1,
      NULL,
      NULL
    );
  }

  return gate_candidate_response;
}


#ifdef gate_candidate_response_MAIN

void test_gate_candidate_response(int include_optional) {
    gate_candidate_response_t* gate_candidate_response_1 = instantiate_gate_candidate_response(include_optional);

	cJSON* jsongate_candidate_response_1 = gate_candidate_response_convertToJSON(gate_candidate_response_1);
	printf("gate_candidate_response :\n%s\n", cJSON_Print(jsongate_candidate_response_1));
	gate_candidate_response_t* gate_candidate_response_2 = gate_candidate_response_parseFromJSON(jsongate_candidate_response_1);
	cJSON* jsongate_candidate_response_2 = gate_candidate_response_convertToJSON(gate_candidate_response_2);
	printf("repeating gate_candidate_response:\n%s\n", cJSON_Print(jsongate_candidate_response_2));
}

int main() {
  test_gate_candidate_response(1);
  test_gate_candidate_response(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_candidate_response_MAIN
#endif // gate_candidate_response_TEST
