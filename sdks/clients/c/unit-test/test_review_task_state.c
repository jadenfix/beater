#ifndef review_task_state_TEST
#define review_task_state_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define review_task_state_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/review_task_state.h"
review_task_state_t* instantiate_review_task_state(int include_optional);



review_task_state_t* instantiate_review_task_state(int include_optional) {
  review_task_state_t* review_task_state = NULL;
  if (include_optional) {
    review_task_state = review_task_state_create(
    );
  } else {
    review_task_state = review_task_state_create(
    );
  }

  return review_task_state;
}


#ifdef review_task_state_MAIN

void test_review_task_state(int include_optional) {
    review_task_state_t* review_task_state_1 = instantiate_review_task_state(include_optional);

	cJSON* jsonreview_task_state_1 = review_task_state_convertToJSON(review_task_state_1);
	printf("review_task_state :\n%s\n", cJSON_Print(jsonreview_task_state_1));
	review_task_state_t* review_task_state_2 = review_task_state_parseFromJSON(jsonreview_task_state_1);
	cJSON* jsonreview_task_state_2 = review_task_state_convertToJSON(review_task_state_2);
	printf("repeating review_task_state:\n%s\n", cJSON_Print(jsonreview_task_state_2));
}

int main() {
  test_review_task_state(1);
  test_review_task_state(0);

  printf("Hello world \n");
  return 0;
}

#endif // review_task_state_MAIN
#endif // review_task_state_TEST
