#ifndef create_provider_secret_http_request_TEST
#define create_provider_secret_http_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define create_provider_secret_http_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/create_provider_secret_http_request.h"
create_provider_secret_http_request_t* instantiate_create_provider_secret_http_request(int include_optional);



create_provider_secret_http_request_t* instantiate_create_provider_secret_http_request(int include_optional) {
  create_provider_secret_http_request_t* create_provider_secret_http_request = NULL;
  if (include_optional) {
    create_provider_secret_http_request = create_provider_secret_http_request_create(
      "0",
      "0",
      "0"
    );
  } else {
    create_provider_secret_http_request = create_provider_secret_http_request_create(
      "0",
      "0",
      "0"
    );
  }

  return create_provider_secret_http_request;
}


#ifdef create_provider_secret_http_request_MAIN

void test_create_provider_secret_http_request(int include_optional) {
    create_provider_secret_http_request_t* create_provider_secret_http_request_1 = instantiate_create_provider_secret_http_request(include_optional);

	cJSON* jsoncreate_provider_secret_http_request_1 = create_provider_secret_http_request_convertToJSON(create_provider_secret_http_request_1);
	printf("create_provider_secret_http_request :\n%s\n", cJSON_Print(jsoncreate_provider_secret_http_request_1));
	create_provider_secret_http_request_t* create_provider_secret_http_request_2 = create_provider_secret_http_request_parseFromJSON(jsoncreate_provider_secret_http_request_1);
	cJSON* jsoncreate_provider_secret_http_request_2 = create_provider_secret_http_request_convertToJSON(create_provider_secret_http_request_2);
	printf("repeating create_provider_secret_http_request:\n%s\n", cJSON_Print(jsoncreate_provider_secret_http_request_2));
}

int main() {
  test_create_provider_secret_http_request(1);
  test_create_provider_secret_http_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // create_provider_secret_http_request_MAIN
#endif // create_provider_secret_http_request_TEST
