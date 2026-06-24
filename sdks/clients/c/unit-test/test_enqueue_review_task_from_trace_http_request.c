#ifndef enqueue_review_task_from_trace_http_request_TEST
#define enqueue_review_task_from_trace_http_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define enqueue_review_task_from_trace_http_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/enqueue_review_task_from_trace_http_request.h"
enqueue_review_task_from_trace_http_request_t* instantiate_enqueue_review_task_from_trace_http_request(int include_optional);



enqueue_review_task_from_trace_http_request_t* instantiate_enqueue_review_task_from_trace_http_request(int include_optional) {
  enqueue_review_task_from_trace_http_request_t* enqueue_review_task_from_trace_http_request = NULL;
  if (include_optional) {
    enqueue_review_task_from_trace_http_request = enqueue_review_task_from_trace_http_request_create(
      "0",
      "0",
      56,
      "0",
      "0",
      "0"
    );
  } else {
    enqueue_review_task_from_trace_http_request = enqueue_review_task_from_trace_http_request_create(
      "0",
      "0",
      56,
      "0",
      "0",
      "0"
    );
  }

  return enqueue_review_task_from_trace_http_request;
}


#ifdef enqueue_review_task_from_trace_http_request_MAIN

void test_enqueue_review_task_from_trace_http_request(int include_optional) {
    enqueue_review_task_from_trace_http_request_t* enqueue_review_task_from_trace_http_request_1 = instantiate_enqueue_review_task_from_trace_http_request(include_optional);

	cJSON* jsonenqueue_review_task_from_trace_http_request_1 = enqueue_review_task_from_trace_http_request_convertToJSON(enqueue_review_task_from_trace_http_request_1);
	printf("enqueue_review_task_from_trace_http_request :\n%s\n", cJSON_Print(jsonenqueue_review_task_from_trace_http_request_1));
	enqueue_review_task_from_trace_http_request_t* enqueue_review_task_from_trace_http_request_2 = enqueue_review_task_from_trace_http_request_parseFromJSON(jsonenqueue_review_task_from_trace_http_request_1);
	cJSON* jsonenqueue_review_task_from_trace_http_request_2 = enqueue_review_task_from_trace_http_request_convertToJSON(enqueue_review_task_from_trace_http_request_2);
	printf("repeating enqueue_review_task_from_trace_http_request:\n%s\n", cJSON_Print(jsonenqueue_review_task_from_trace_http_request_2));
}

int main() {
  test_enqueue_review_task_from_trace_http_request(1);
  test_enqueue_review_task_from_trace_http_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // enqueue_review_task_from_trace_http_request_MAIN
#endif // enqueue_review_task_from_trace_http_request_TEST
