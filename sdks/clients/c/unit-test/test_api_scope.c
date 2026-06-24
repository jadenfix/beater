#ifndef api_scope_TEST
#define api_scope_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define api_scope_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/api_scope.h"
api_scope_t* instantiate_api_scope(int include_optional);



api_scope_t* instantiate_api_scope(int include_optional) {
  api_scope_t* api_scope = NULL;
  if (include_optional) {
    api_scope = api_scope_create(
    );
  } else {
    api_scope = api_scope_create(
    );
  }

  return api_scope;
}


#ifdef api_scope_MAIN

void test_api_scope(int include_optional) {
    api_scope_t* api_scope_1 = instantiate_api_scope(include_optional);

	cJSON* jsonapi_scope_1 = api_scope_convertToJSON(api_scope_1);
	printf("api_scope :\n%s\n", cJSON_Print(jsonapi_scope_1));
	api_scope_t* api_scope_2 = api_scope_parseFromJSON(jsonapi_scope_1);
	cJSON* jsonapi_scope_2 = api_scope_convertToJSON(api_scope_2);
	printf("repeating api_scope:\n%s\n", cJSON_Print(jsonapi_scope_2));
}

int main() {
  test_api_scope(1);
  test_api_scope(0);

  printf("Hello world \n");
  return 0;
}

#endif // api_scope_MAIN
#endif // api_scope_TEST
