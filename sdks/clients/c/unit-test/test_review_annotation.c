#ifndef review_annotation_TEST
#define review_annotation_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define review_annotation_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/review_annotation.h"
review_annotation_t* instantiate_review_annotation(int include_optional);



review_annotation_t* instantiate_review_annotation(int include_optional) {
  review_annotation_t* review_annotation = NULL;
  if (include_optional) {
    review_annotation = review_annotation_create(
      "0",
      "2013-10-20T19:20:30+01:00",
      null,
      "0",
      "0",
      "0",
      "0",
      "0",
      beater_api_review_annotation__pass
    );
  } else {
    review_annotation = review_annotation_create(
      "0",
      "2013-10-20T19:20:30+01:00",
      null,
      "0",
      "0",
      "0",
      "0",
      "0",
      beater_api_review_annotation__pass
    );
  }

  return review_annotation;
}


#ifdef review_annotation_MAIN

void test_review_annotation(int include_optional) {
    review_annotation_t* review_annotation_1 = instantiate_review_annotation(include_optional);

	cJSON* jsonreview_annotation_1 = review_annotation_convertToJSON(review_annotation_1);
	printf("review_annotation :\n%s\n", cJSON_Print(jsonreview_annotation_1));
	review_annotation_t* review_annotation_2 = review_annotation_parseFromJSON(jsonreview_annotation_1);
	cJSON* jsonreview_annotation_2 = review_annotation_convertToJSON(review_annotation_2);
	printf("repeating review_annotation:\n%s\n", cJSON_Print(jsonreview_annotation_2));
}

int main() {
  test_review_annotation(1);
  test_review_annotation(0);

  printf("Hello world \n");
  return 0;
}

#endif // review_annotation_MAIN
#endif // review_annotation_TEST
