#ifndef api_key_created_response_TEST
#define api_key_created_response_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define api_key_created_response_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/api_key_created_response.h"
api_key_created_response_t* instantiate_api_key_created_response(int include_optional);



api_key_created_response_t* instantiate_api_key_created_response(int include_optional) {
  api_key_created_response_t* api_key_created_response = NULL;
  if (include_optional) {
    api_key_created_response = api_key_created_response_create(
      1,
      "0",
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      list_createList(),
      "0",
      "0"
    );
  } else {
    api_key_created_response = api_key_created_response_create(
      1,
      "0",
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      list_createList(),
      "0",
      "0"
    );
  }

  return api_key_created_response;
}


#ifdef api_key_created_response_MAIN

void test_api_key_created_response(int include_optional) {
    api_key_created_response_t* api_key_created_response_1 = instantiate_api_key_created_response(include_optional);

	cJSON* jsonapi_key_created_response_1 = api_key_created_response_convertToJSON(api_key_created_response_1);
	printf("api_key_created_response :\n%s\n", cJSON_Print(jsonapi_key_created_response_1));
	api_key_created_response_t* api_key_created_response_2 = api_key_created_response_parseFromJSON(jsonapi_key_created_response_1);
	cJSON* jsonapi_key_created_response_2 = api_key_created_response_convertToJSON(api_key_created_response_2);
	printf("repeating api_key_created_response:\n%s\n", cJSON_Print(jsonapi_key_created_response_2));
}

int main() {
  test_api_key_created_response(1);
  test_api_key_created_response(0);

  printf("Hello world \n");
  return 0;
}

#endif // api_key_created_response_MAIN
#endif // api_key_created_response_TEST
