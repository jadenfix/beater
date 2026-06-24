#ifndef revoked_provider_secret_TEST
#define revoked_provider_secret_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define revoked_provider_secret_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/revoked_provider_secret.h"
revoked_provider_secret_t* instantiate_revoked_provider_secret(int include_optional);



revoked_provider_secret_t* instantiate_revoked_provider_secret(int include_optional) {
  revoked_provider_secret_t* revoked_provider_secret = NULL;
  if (include_optional) {
    revoked_provider_secret = revoked_provider_secret_create(
      1,
      "0",
      "2013-10-20T19:20:30+01:00"
    );
  } else {
    revoked_provider_secret = revoked_provider_secret_create(
      1,
      "0",
      "2013-10-20T19:20:30+01:00"
    );
  }

  return revoked_provider_secret;
}


#ifdef revoked_provider_secret_MAIN

void test_revoked_provider_secret(int include_optional) {
    revoked_provider_secret_t* revoked_provider_secret_1 = instantiate_revoked_provider_secret(include_optional);

	cJSON* jsonrevoked_provider_secret_1 = revoked_provider_secret_convertToJSON(revoked_provider_secret_1);
	printf("revoked_provider_secret :\n%s\n", cJSON_Print(jsonrevoked_provider_secret_1));
	revoked_provider_secret_t* revoked_provider_secret_2 = revoked_provider_secret_parseFromJSON(jsonrevoked_provider_secret_1);
	cJSON* jsonrevoked_provider_secret_2 = revoked_provider_secret_convertToJSON(revoked_provider_secret_2);
	printf("repeating revoked_provider_secret:\n%s\n", cJSON_Print(jsonrevoked_provider_secret_2));
}

int main() {
  test_revoked_provider_secret(1);
  test_revoked_provider_secret(0);

  printf("Hello world \n");
  return 0;
}

#endif // revoked_provider_secret_MAIN
#endif // revoked_provider_secret_TEST
