#ifndef gate_candidate_request_TEST
#define gate_candidate_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_candidate_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_candidate_request.h"
gate_candidate_request_t* instantiate_gate_candidate_request(int include_optional);

#include "test_gate_candidate_change_request.c"
#include "test_gate_policy.c"


gate_candidate_request_t* instantiate_gate_candidate_request(int include_optional) {
  gate_candidate_request_t* gate_candidate_request = NULL;
  if (include_optional) {
    gate_candidate_request = gate_candidate_request_create(
       // false, not to have infinite recursion
      instantiate_gate_candidate_change_request(0),
       // false, not to have infinite recursion
      instantiate_gate_policy(0),
      1.337,
      0,
      0,
      1.337,
      list_createList()
    );
  } else {
    gate_candidate_request = gate_candidate_request_create(
      NULL,
      NULL,
      1.337,
      0,
      0,
      1.337,
      list_createList()
    );
  }

  return gate_candidate_request;
}


#ifdef gate_candidate_request_MAIN

void test_gate_candidate_request(int include_optional) {
    gate_candidate_request_t* gate_candidate_request_1 = instantiate_gate_candidate_request(include_optional);

	cJSON* jsongate_candidate_request_1 = gate_candidate_request_convertToJSON(gate_candidate_request_1);
	printf("gate_candidate_request :\n%s\n", cJSON_Print(jsongate_candidate_request_1));
	gate_candidate_request_t* gate_candidate_request_2 = gate_candidate_request_parseFromJSON(jsongate_candidate_request_1);
	cJSON* jsongate_candidate_request_2 = gate_candidate_request_convertToJSON(gate_candidate_request_2);
	printf("repeating gate_candidate_request:\n%s\n", cJSON_Print(jsongate_candidate_request_2));
}

int main() {
  test_gate_candidate_request(1);
  test_gate_candidate_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_candidate_request_MAIN
#endif // gate_candidate_request_TEST
