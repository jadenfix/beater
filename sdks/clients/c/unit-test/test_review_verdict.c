#ifndef review_verdict_TEST
#define review_verdict_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define review_verdict_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/review_verdict.h"
review_verdict_t* instantiate_review_verdict(int include_optional);



review_verdict_t* instantiate_review_verdict(int include_optional) {
  review_verdict_t* review_verdict = NULL;
  if (include_optional) {
    review_verdict = review_verdict_create(
    );
  } else {
    review_verdict = review_verdict_create(
    );
  }

  return review_verdict;
}


#ifdef review_verdict_MAIN

void test_review_verdict(int include_optional) {
    review_verdict_t* review_verdict_1 = instantiate_review_verdict(include_optional);

	cJSON* jsonreview_verdict_1 = review_verdict_convertToJSON(review_verdict_1);
	printf("review_verdict :\n%s\n", cJSON_Print(jsonreview_verdict_1));
	review_verdict_t* review_verdict_2 = review_verdict_parseFromJSON(jsonreview_verdict_1);
	cJSON* jsonreview_verdict_2 = review_verdict_convertToJSON(review_verdict_2);
	printf("repeating review_verdict:\n%s\n", cJSON_Print(jsonreview_verdict_2));
}

int main() {
  test_review_verdict(1);
  test_review_verdict(0);

  printf("Hello world \n");
  return 0;
}

#endif // review_verdict_MAIN
#endif // review_verdict_TEST
