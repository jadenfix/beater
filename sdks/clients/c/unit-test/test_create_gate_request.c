#ifndef create_gate_request_TEST
#define create_gate_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define create_gate_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/create_gate_request.h"
create_gate_request_t* instantiate_create_gate_request(int include_optional);



create_gate_request_t* instantiate_create_gate_request(int include_optional) {
  create_gate_request_t* create_gate_request = NULL;
  if (include_optional) {
    create_gate_request = create_gate_request_create(
      "0",
      "0",
      "0",
      beater_api_create_gate_request__pass,
      "0"
    );
  } else {
    create_gate_request = create_gate_request_create(
      "0",
      "0",
      "0",
      beater_api_create_gate_request__pass,
      "0"
    );
  }

  return create_gate_request;
}


#ifdef create_gate_request_MAIN

void test_create_gate_request(int include_optional) {
    create_gate_request_t* create_gate_request_1 = instantiate_create_gate_request(include_optional);

	cJSON* jsoncreate_gate_request_1 = create_gate_request_convertToJSON(create_gate_request_1);
	printf("create_gate_request :\n%s\n", cJSON_Print(jsoncreate_gate_request_1));
	create_gate_request_t* create_gate_request_2 = create_gate_request_parseFromJSON(jsoncreate_gate_request_1);
	cJSON* jsoncreate_gate_request_2 = create_gate_request_convertToJSON(create_gate_request_2);
	printf("repeating create_gate_request:\n%s\n", cJSON_Print(jsoncreate_gate_request_2));
}

int main() {
  test_create_gate_request(1);
  test_create_gate_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // create_gate_request_MAIN
#endif // create_gate_request_TEST
