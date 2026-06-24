#ifndef review_queue_TEST
#define review_queue_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define review_queue_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/review_queue.h"
review_queue_t* instantiate_review_queue(int include_optional);



review_queue_t* instantiate_review_queue(int include_optional) {
  review_queue_t* review_queue = NULL;
  if (include_optional) {
    review_queue = review_queue_create(
      null,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0"
    );
  } else {
    review_queue = review_queue_create(
      null,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0"
    );
  }

  return review_queue;
}


#ifdef review_queue_MAIN

void test_review_queue(int include_optional) {
    review_queue_t* review_queue_1 = instantiate_review_queue(include_optional);

	cJSON* jsonreview_queue_1 = review_queue_convertToJSON(review_queue_1);
	printf("review_queue :\n%s\n", cJSON_Print(jsonreview_queue_1));
	review_queue_t* review_queue_2 = review_queue_parseFromJSON(jsonreview_queue_1);
	cJSON* jsonreview_queue_2 = review_queue_convertToJSON(review_queue_2);
	printf("repeating review_queue:\n%s\n", cJSON_Print(jsonreview_queue_2));
}

int main() {
  test_review_queue(1);
  test_review_queue(0);

  printf("Hello world \n");
  return 0;
}

#endif // review_queue_MAIN
#endif // review_queue_TEST
