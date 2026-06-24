#ifndef create_review_queue_http_request_TEST
#define create_review_queue_http_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define create_review_queue_http_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/create_review_queue_http_request.h"
create_review_queue_http_request_t* instantiate_create_review_queue_http_request(int include_optional);



create_review_queue_http_request_t* instantiate_create_review_queue_http_request(int include_optional) {
  create_review_queue_http_request_t* create_review_queue_http_request = NULL;
  if (include_optional) {
    create_review_queue_http_request = create_review_queue_http_request_create(
      null,
      "0",
      "0"
    );
  } else {
    create_review_queue_http_request = create_review_queue_http_request_create(
      null,
      "0",
      "0"
    );
  }

  return create_review_queue_http_request;
}


#ifdef create_review_queue_http_request_MAIN

void test_create_review_queue_http_request(int include_optional) {
    create_review_queue_http_request_t* create_review_queue_http_request_1 = instantiate_create_review_queue_http_request(include_optional);

	cJSON* jsoncreate_review_queue_http_request_1 = create_review_queue_http_request_convertToJSON(create_review_queue_http_request_1);
	printf("create_review_queue_http_request :\n%s\n", cJSON_Print(jsoncreate_review_queue_http_request_1));
	create_review_queue_http_request_t* create_review_queue_http_request_2 = create_review_queue_http_request_parseFromJSON(jsoncreate_review_queue_http_request_1);
	cJSON* jsoncreate_review_queue_http_request_2 = create_review_queue_http_request_convertToJSON(create_review_queue_http_request_2);
	printf("repeating create_review_queue_http_request:\n%s\n", cJSON_Print(jsoncreate_review_queue_http_request_2));
}

int main() {
  test_create_review_queue_http_request(1);
  test_create_review_queue_http_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // create_review_queue_http_request_MAIN
#endif // create_review_queue_http_request_TEST
