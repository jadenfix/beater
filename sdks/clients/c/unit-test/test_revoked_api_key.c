#ifndef revoked_api_key_TEST
#define revoked_api_key_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define revoked_api_key_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/revoked_api_key.h"
revoked_api_key_t* instantiate_revoked_api_key(int include_optional);



revoked_api_key_t* instantiate_revoked_api_key(int include_optional) {
  revoked_api_key_t* revoked_api_key = NULL;
  if (include_optional) {
    revoked_api_key = revoked_api_key_create(
      1,
      "0",
      "2013-10-20T19:20:30+01:00"
    );
  } else {
    revoked_api_key = revoked_api_key_create(
      1,
      "0",
      "2013-10-20T19:20:30+01:00"
    );
  }

  return revoked_api_key;
}


#ifdef revoked_api_key_MAIN

void test_revoked_api_key(int include_optional) {
    revoked_api_key_t* revoked_api_key_1 = instantiate_revoked_api_key(include_optional);

	cJSON* jsonrevoked_api_key_1 = revoked_api_key_convertToJSON(revoked_api_key_1);
	printf("revoked_api_key :\n%s\n", cJSON_Print(jsonrevoked_api_key_1));
	revoked_api_key_t* revoked_api_key_2 = revoked_api_key_parseFromJSON(jsonrevoked_api_key_1);
	cJSON* jsonrevoked_api_key_2 = revoked_api_key_convertToJSON(revoked_api_key_2);
	printf("repeating revoked_api_key:\n%s\n", cJSON_Print(jsonrevoked_api_key_2));
}

int main() {
  test_revoked_api_key(1);
  test_revoked_api_key(0);

  printf("Hello world \n");
  return 0;
}

#endif // revoked_api_key_MAIN
#endif // revoked_api_key_TEST
