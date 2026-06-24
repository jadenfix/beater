#ifndef ingest_queue_status_TEST
#define ingest_queue_status_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define ingest_queue_status_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/ingest_queue_status.h"
ingest_queue_status_t* instantiate_ingest_queue_status(int include_optional);



ingest_queue_status_t* instantiate_ingest_queue_status(int include_optional) {
  ingest_queue_status_t* ingest_queue_status = NULL;
  if (include_optional) {
    ingest_queue_status = ingest_queue_status_create(
      list_createList(),
      "0",
      "0",
      0,
      0,
      0
    );
  } else {
    ingest_queue_status = ingest_queue_status_create(
      list_createList(),
      "0",
      "0",
      0,
      0,
      0
    );
  }

  return ingest_queue_status;
}


#ifdef ingest_queue_status_MAIN

void test_ingest_queue_status(int include_optional) {
    ingest_queue_status_t* ingest_queue_status_1 = instantiate_ingest_queue_status(include_optional);

	cJSON* jsoningest_queue_status_1 = ingest_queue_status_convertToJSON(ingest_queue_status_1);
	printf("ingest_queue_status :\n%s\n", cJSON_Print(jsoningest_queue_status_1));
	ingest_queue_status_t* ingest_queue_status_2 = ingest_queue_status_parseFromJSON(jsoningest_queue_status_1);
	cJSON* jsoningest_queue_status_2 = ingest_queue_status_convertToJSON(ingest_queue_status_2);
	printf("repeating ingest_queue_status:\n%s\n", cJSON_Print(jsoningest_queue_status_2));
}

int main() {
  test_ingest_queue_status(1);
  test_ingest_queue_status(0);

  printf("Hello world \n");
  return 0;
}

#endif // ingest_queue_status_MAIN
#endif // ingest_queue_status_TEST
