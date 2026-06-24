#ifndef review_task_TEST
#define review_task_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define review_task_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/review_task.h"
review_task_t* instantiate_review_task(int include_optional);



review_task_t* instantiate_review_task(int include_optional) {
  review_task_t* review_task = NULL;
  if (include_optional) {
    review_task = review_task_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      56,
      "0",
      "0",
      "0",
      beater_api_review_task__open,
      "0",
      "0",
      "0",
      "2013-10-20T19:20:30+01:00"
    );
  } else {
    review_task = review_task_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      56,
      "0",
      "0",
      "0",
      beater_api_review_task__open,
      "0",
      "0",
      "0",
      "2013-10-20T19:20:30+01:00"
    );
  }

  return review_task;
}


#ifdef review_task_MAIN

void test_review_task(int include_optional) {
    review_task_t* review_task_1 = instantiate_review_task(include_optional);

	cJSON* jsonreview_task_1 = review_task_convertToJSON(review_task_1);
	printf("review_task :\n%s\n", cJSON_Print(jsonreview_task_1));
	review_task_t* review_task_2 = review_task_parseFromJSON(jsonreview_task_1);
	cJSON* jsonreview_task_2 = review_task_convertToJSON(review_task_2);
	printf("repeating review_task:\n%s\n", cJSON_Print(jsonreview_task_2));
}

int main() {
  test_review_task(1);
  test_review_task(0);

  printf("Hello world \n");
  return 0;
}

#endif // review_task_MAIN
#endif // review_task_TEST
