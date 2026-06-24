#ifndef create_api_key_http_request_TEST
#define create_api_key_http_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define create_api_key_http_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/create_api_key_http_request.h"
create_api_key_http_request_t* instantiate_create_api_key_http_request(int include_optional);



create_api_key_http_request_t* instantiate_create_api_key_http_request(int include_optional) {
  create_api_key_http_request_t* create_api_key_http_request = NULL;
  if (include_optional) {
    create_api_key_http_request = create_api_key_http_request_create(
      list_createList()
    );
  } else {
    create_api_key_http_request = create_api_key_http_request_create(
      list_createList()
    );
  }

  return create_api_key_http_request;
}


#ifdef create_api_key_http_request_MAIN

void test_create_api_key_http_request(int include_optional) {
    create_api_key_http_request_t* create_api_key_http_request_1 = instantiate_create_api_key_http_request(include_optional);

	cJSON* jsoncreate_api_key_http_request_1 = create_api_key_http_request_convertToJSON(create_api_key_http_request_1);
	printf("create_api_key_http_request :\n%s\n", cJSON_Print(jsoncreate_api_key_http_request_1));
	create_api_key_http_request_t* create_api_key_http_request_2 = create_api_key_http_request_parseFromJSON(jsoncreate_api_key_http_request_1);
	cJSON* jsoncreate_api_key_http_request_2 = create_api_key_http_request_convertToJSON(create_api_key_http_request_2);
	printf("repeating create_api_key_http_request:\n%s\n", cJSON_Print(jsoncreate_api_key_http_request_2));
}

int main() {
  test_create_api_key_http_request(1);
  test_create_api_key_http_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // create_api_key_http_request_MAIN
#endif // create_api_key_http_request_TEST
