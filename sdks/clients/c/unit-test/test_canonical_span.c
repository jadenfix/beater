#ifndef canonical_span_TEST
#define canonical_span_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define canonical_span_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/canonical_span.h"
canonical_span_t* instantiate_canonical_span(int include_optional);

#include "test_money.c"
#include "test_artifact_ref.c"
#include "test_model_ref.c"
#include "test_artifact_ref.c"
#include "test_artifact_ref.c"
#include "test_token_counts.c"


canonical_span_t* instantiate_canonical_span(int include_optional) {
  canonical_span_t* canonical_span = NULL;
  if (include_optional) {
    canonical_span = canonical_span_create(
      list_createList(),
       // false, not to have infinite recursion
      instantiate_money(0),
      "2013-10-20T19:20:30+01:00",
      "0",
       // false, not to have infinite recursion
      instantiate_artifact_ref(0),
      "0",
       // false, not to have infinite recursion
      instantiate_model_ref(0),
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_artifact_ref(0),
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_artifact_ref(0),
      0,
      0,
      "0",
      "2013-10-20T19:20:30+01:00",
      beater_api_canonical_span__ok,
      "0",
       // false, not to have infinite recursion
      instantiate_token_counts(0),
      "0",
      null
    );
  } else {
    canonical_span = canonical_span_create(
      list_createList(),
      NULL,
      "2013-10-20T19:20:30+01:00",
      "0",
      NULL,
      "0",
      NULL,
      "0",
      "0",
      NULL,
      "0",
      "0",
      NULL,
      0,
      0,
      "0",
      "2013-10-20T19:20:30+01:00",
      beater_api_canonical_span__ok,
      "0",
      NULL,
      "0",
      null
    );
  }

  return canonical_span;
}


#ifdef canonical_span_MAIN

void test_canonical_span(int include_optional) {
    canonical_span_t* canonical_span_1 = instantiate_canonical_span(include_optional);

	cJSON* jsoncanonical_span_1 = canonical_span_convertToJSON(canonical_span_1);
	printf("canonical_span :\n%s\n", cJSON_Print(jsoncanonical_span_1));
	canonical_span_t* canonical_span_2 = canonical_span_parseFromJSON(jsoncanonical_span_1);
	cJSON* jsoncanonical_span_2 = canonical_span_convertToJSON(canonical_span_2);
	printf("repeating canonical_span:\n%s\n", cJSON_Print(jsoncanonical_span_2));
}

int main() {
  test_canonical_span(1);
  test_canonical_span(0);

  printf("Hello world \n");
  return 0;
}

#endif // canonical_span_MAIN
#endif // canonical_span_TEST
