#ifndef otlp_ingest_outcome_TEST
#define otlp_ingest_outcome_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define otlp_ingest_outcome_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/otlp_ingest_outcome.h"
otlp_ingest_outcome_t* instantiate_otlp_ingest_outcome(int include_optional);



otlp_ingest_outcome_t* instantiate_otlp_ingest_outcome(int include_optional) {
  otlp_ingest_outcome_t* otlp_ingest_outcome = NULL;
  if (include_optional) {
    otlp_ingest_outcome = otlp_ingest_outcome_create(
      0,
      0,
      1,
      0,
      0
    );
  } else {
    otlp_ingest_outcome = otlp_ingest_outcome_create(
      0,
      0,
      1,
      0,
      0
    );
  }

  return otlp_ingest_outcome;
}


#ifdef otlp_ingest_outcome_MAIN

void test_otlp_ingest_outcome(int include_optional) {
    otlp_ingest_outcome_t* otlp_ingest_outcome_1 = instantiate_otlp_ingest_outcome(include_optional);

	cJSON* jsonotlp_ingest_outcome_1 = otlp_ingest_outcome_convertToJSON(otlp_ingest_outcome_1);
	printf("otlp_ingest_outcome :\n%s\n", cJSON_Print(jsonotlp_ingest_outcome_1));
	otlp_ingest_outcome_t* otlp_ingest_outcome_2 = otlp_ingest_outcome_parseFromJSON(jsonotlp_ingest_outcome_1);
	cJSON* jsonotlp_ingest_outcome_2 = otlp_ingest_outcome_convertToJSON(otlp_ingest_outcome_2);
	printf("repeating otlp_ingest_outcome:\n%s\n", cJSON_Print(jsonotlp_ingest_outcome_2));
}

int main() {
  test_otlp_ingest_outcome(1);
  test_otlp_ingest_outcome(0);

  printf("Hello world \n");
  return 0;
}

#endif // otlp_ingest_outcome_MAIN
#endif // otlp_ingest_outcome_TEST
