#ifndef ingest_outcome_TEST
#define ingest_outcome_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define ingest_outcome_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/ingest_outcome.h"
ingest_outcome_t* instantiate_ingest_outcome(int include_optional);

#include "test_write_ack.c"


ingest_outcome_t* instantiate_ingest_outcome(int include_optional) {
  ingest_outcome_t* ingest_outcome = NULL;
  if (include_optional) {
    ingest_outcome = ingest_outcome_create(
       // false, not to have infinite recursion
      instantiate_write_ack(0),
      1
    );
  } else {
    ingest_outcome = ingest_outcome_create(
      NULL,
      1
    );
  }

  return ingest_outcome;
}


#ifdef ingest_outcome_MAIN

void test_ingest_outcome(int include_optional) {
    ingest_outcome_t* ingest_outcome_1 = instantiate_ingest_outcome(include_optional);

	cJSON* jsoningest_outcome_1 = ingest_outcome_convertToJSON(ingest_outcome_1);
	printf("ingest_outcome :\n%s\n", cJSON_Print(jsoningest_outcome_1));
	ingest_outcome_t* ingest_outcome_2 = ingest_outcome_parseFromJSON(jsoningest_outcome_1);
	cJSON* jsoningest_outcome_2 = ingest_outcome_convertToJSON(ingest_outcome_2);
	printf("repeating ingest_outcome:\n%s\n", cJSON_Print(jsoningest_outcome_2));
}

int main() {
  test_ingest_outcome(1);
  test_ingest_outcome(0);

  printf("Hello world \n");
  return 0;
}

#endif // ingest_outcome_MAIN
#endif // ingest_outcome_TEST
