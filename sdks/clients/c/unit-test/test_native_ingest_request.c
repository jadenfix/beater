#ifndef native_ingest_request_TEST
#define native_ingest_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define native_ingest_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/native_ingest_request.h"
native_ingest_request_t* instantiate_native_ingest_request(int include_optional);

#include "test_auth_context.c"
#include "test_money.c"
#include "test_model_ref.c"
#include "test_tenant_scope.c"
#include "test_token_counts.c"


native_ingest_request_t* instantiate_native_ingest_request(int include_optional) {
  native_ingest_request_t* native_ingest_request = NULL;
  if (include_optional) {
    native_ingest_request = native_ingest_request_create(
      list_createList(),
       // false, not to have infinite recursion
      instantiate_auth_context(0),
       // false, not to have infinite recursion
      instantiate_money(0),
      "2013-10-20T19:20:30+01:00",
      "0",
      null,
      "0",
       // false, not to have infinite recursion
      instantiate_model_ref(0),
      "0",
      null,
      "0",
      beater_api_native_ingest_request__public,
       // false, not to have infinite recursion
      instantiate_tenant_scope(0),
      0,
      "0",
      "2013-10-20T19:20:30+01:00",
      beater_api_native_ingest_request__ok,
       // false, not to have infinite recursion
      instantiate_token_counts(0),
      "0"
    );
  } else {
    native_ingest_request = native_ingest_request_create(
      list_createList(),
      NULL,
      NULL,
      "2013-10-20T19:20:30+01:00",
      "0",
      null,
      "0",
      NULL,
      "0",
      null,
      "0",
      beater_api_native_ingest_request__public,
      NULL,
      0,
      "0",
      "2013-10-20T19:20:30+01:00",
      beater_api_native_ingest_request__ok,
      NULL,
      "0"
    );
  }

  return native_ingest_request;
}


#ifdef native_ingest_request_MAIN

void test_native_ingest_request(int include_optional) {
    native_ingest_request_t* native_ingest_request_1 = instantiate_native_ingest_request(include_optional);

	cJSON* jsonnative_ingest_request_1 = native_ingest_request_convertToJSON(native_ingest_request_1);
	printf("native_ingest_request :\n%s\n", cJSON_Print(jsonnative_ingest_request_1));
	native_ingest_request_t* native_ingest_request_2 = native_ingest_request_parseFromJSON(jsonnative_ingest_request_1);
	cJSON* jsonnative_ingest_request_2 = native_ingest_request_convertToJSON(native_ingest_request_2);
	printf("repeating native_ingest_request:\n%s\n", cJSON_Print(jsonnative_ingest_request_2));
}

int main() {
  test_native_ingest_request(1);
  test_native_ingest_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // native_ingest_request_MAIN
#endif // native_ingest_request_TEST
