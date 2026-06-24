#ifndef auth_context_TEST
#define auth_context_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define auth_context_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/auth_context.h"
auth_context_t* instantiate_auth_context(int include_optional);



auth_context_t* instantiate_auth_context(int include_optional) {
  auth_context_t* auth_context = NULL;
  if (include_optional) {
    auth_context = auth_context_create(
      "0",
      list_createList()
    );
  } else {
    auth_context = auth_context_create(
      "0",
      list_createList()
    );
  }

  return auth_context;
}


#ifdef auth_context_MAIN

void test_auth_context(int include_optional) {
    auth_context_t* auth_context_1 = instantiate_auth_context(include_optional);

	cJSON* jsonauth_context_1 = auth_context_convertToJSON(auth_context_1);
	printf("auth_context :\n%s\n", cJSON_Print(jsonauth_context_1));
	auth_context_t* auth_context_2 = auth_context_parseFromJSON(jsonauth_context_1);
	cJSON* jsonauth_context_2 = auth_context_convertToJSON(auth_context_2);
	printf("repeating auth_context:\n%s\n", cJSON_Print(jsonauth_context_2));
}

int main() {
  test_auth_context(1);
  test_auth_context(0);

  printf("Hello world \n");
  return 0;
}

#endif // auth_context_MAIN
#endif // auth_context_TEST
