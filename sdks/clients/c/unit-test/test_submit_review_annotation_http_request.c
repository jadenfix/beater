#ifndef submit_review_annotation_http_request_TEST
#define submit_review_annotation_http_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define submit_review_annotation_http_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/submit_review_annotation_http_request.h"
submit_review_annotation_http_request_t* instantiate_submit_review_annotation_http_request(int include_optional);



submit_review_annotation_http_request_t* instantiate_submit_review_annotation_http_request(int include_optional) {
  submit_review_annotation_http_request_t* submit_review_annotation_http_request = NULL;
  if (include_optional) {
    submit_review_annotation_http_request = submit_review_annotation_http_request_create(
      "0",
      null,
      "0",
      beater_api_submit_review_annotation_http_request__pass
    );
  } else {
    submit_review_annotation_http_request = submit_review_annotation_http_request_create(
      "0",
      null,
      "0",
      beater_api_submit_review_annotation_http_request__pass
    );
  }

  return submit_review_annotation_http_request;
}


#ifdef submit_review_annotation_http_request_MAIN

void test_submit_review_annotation_http_request(int include_optional) {
    submit_review_annotation_http_request_t* submit_review_annotation_http_request_1 = instantiate_submit_review_annotation_http_request(include_optional);

	cJSON* jsonsubmit_review_annotation_http_request_1 = submit_review_annotation_http_request_convertToJSON(submit_review_annotation_http_request_1);
	printf("submit_review_annotation_http_request :\n%s\n", cJSON_Print(jsonsubmit_review_annotation_http_request_1));
	submit_review_annotation_http_request_t* submit_review_annotation_http_request_2 = submit_review_annotation_http_request_parseFromJSON(jsonsubmit_review_annotation_http_request_1);
	cJSON* jsonsubmit_review_annotation_http_request_2 = submit_review_annotation_http_request_convertToJSON(submit_review_annotation_http_request_2);
	printf("repeating submit_review_annotation_http_request:\n%s\n", cJSON_Print(jsonsubmit_review_annotation_http_request_2));
}

int main() {
  test_submit_review_annotation_http_request(1);
  test_submit_review_annotation_http_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // submit_review_annotation_http_request_MAIN
#endif // submit_review_annotation_http_request_TEST
