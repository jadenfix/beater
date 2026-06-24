#ifndef promote_review_annotation_http_request_TEST
#define promote_review_annotation_http_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define promote_review_annotation_http_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/promote_review_annotation_http_request.h"
promote_review_annotation_http_request_t* instantiate_promote_review_annotation_http_request(int include_optional);



promote_review_annotation_http_request_t* instantiate_promote_review_annotation_http_request(int include_optional) {
  promote_review_annotation_http_request_t* promote_review_annotation_http_request = NULL;
  if (include_optional) {
    promote_review_annotation_http_request = promote_review_annotation_http_request_create(
      "0",
      null
    );
  } else {
    promote_review_annotation_http_request = promote_review_annotation_http_request_create(
      "0",
      null
    );
  }

  return promote_review_annotation_http_request;
}


#ifdef promote_review_annotation_http_request_MAIN

void test_promote_review_annotation_http_request(int include_optional) {
    promote_review_annotation_http_request_t* promote_review_annotation_http_request_1 = instantiate_promote_review_annotation_http_request(include_optional);

	cJSON* jsonpromote_review_annotation_http_request_1 = promote_review_annotation_http_request_convertToJSON(promote_review_annotation_http_request_1);
	printf("promote_review_annotation_http_request :\n%s\n", cJSON_Print(jsonpromote_review_annotation_http_request_1));
	promote_review_annotation_http_request_t* promote_review_annotation_http_request_2 = promote_review_annotation_http_request_parseFromJSON(jsonpromote_review_annotation_http_request_1);
	cJSON* jsonpromote_review_annotation_http_request_2 = promote_review_annotation_http_request_convertToJSON(promote_review_annotation_http_request_2);
	printf("repeating promote_review_annotation_http_request:\n%s\n", cJSON_Print(jsonpromote_review_annotation_http_request_2));
}

int main() {
  test_promote_review_annotation_http_request(1);
  test_promote_review_annotation_http_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // promote_review_annotation_http_request_MAIN
#endif // promote_review_annotation_http_request_TEST
