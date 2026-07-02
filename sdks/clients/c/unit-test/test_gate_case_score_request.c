#ifndef gate_case_score_request_TEST
#define gate_case_score_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define gate_case_score_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/gate_case_score_request.h"
gate_case_score_request_t* instantiate_gate_case_score_request(int include_optional);



gate_case_score_request_t* instantiate_gate_case_score_request(int include_optional) {
  gate_case_score_request_t* gate_case_score_request = NULL;
  if (include_optional) {
    gate_case_score_request = gate_case_score_request_create(
      1.337,
      1.337,
      "0"
    );
  } else {
    gate_case_score_request = gate_case_score_request_create(
      1.337,
      1.337,
      "0"
    );
  }

  return gate_case_score_request;
}


#ifdef gate_case_score_request_MAIN

void test_gate_case_score_request(int include_optional) {
    gate_case_score_request_t* gate_case_score_request_1 = instantiate_gate_case_score_request(include_optional);

	cJSON* jsongate_case_score_request_1 = gate_case_score_request_convertToJSON(gate_case_score_request_1);
	printf("gate_case_score_request :\n%s\n", cJSON_Print(jsongate_case_score_request_1));
	gate_case_score_request_t* gate_case_score_request_2 = gate_case_score_request_parseFromJSON(jsongate_case_score_request_1);
	cJSON* jsongate_case_score_request_2 = gate_case_score_request_convertToJSON(gate_case_score_request_2);
	printf("repeating gate_case_score_request:\n%s\n", cJSON_Print(jsongate_case_score_request_2));
}

int main() {
  test_gate_case_score_request(1);
  test_gate_case_score_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // gate_case_score_request_MAIN
#endif // gate_case_score_request_TEST
