#ifndef case_output_override_request_TEST
#define case_output_override_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define case_output_override_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/case_output_override_request.h"
case_output_override_request_t* instantiate_case_output_override_request(int include_optional);



case_output_override_request_t* instantiate_case_output_override_request(int include_optional) {
  case_output_override_request_t* case_output_override_request = NULL;
  if (include_optional) {
    case_output_override_request = case_output_override_request_create(
      "0",
      null,
      null
    );
  } else {
    case_output_override_request = case_output_override_request_create(
      "0",
      null,
      null
    );
  }

  return case_output_override_request;
}


#ifdef case_output_override_request_MAIN

void test_case_output_override_request(int include_optional) {
    case_output_override_request_t* case_output_override_request_1 = instantiate_case_output_override_request(include_optional);

	cJSON* jsoncase_output_override_request_1 = case_output_override_request_convertToJSON(case_output_override_request_1);
	printf("case_output_override_request :\n%s\n", cJSON_Print(jsoncase_output_override_request_1));
	case_output_override_request_t* case_output_override_request_2 = case_output_override_request_parseFromJSON(jsoncase_output_override_request_1);
	cJSON* jsoncase_output_override_request_2 = case_output_override_request_convertToJSON(case_output_override_request_2);
	printf("repeating case_output_override_request:\n%s\n", cJSON_Print(jsoncase_output_override_request_2));
}

int main() {
  test_case_output_override_request(1);
  test_case_output_override_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // case_output_override_request_MAIN
#endif // case_output_override_request_TEST
