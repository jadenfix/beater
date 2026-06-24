#ifndef queued_trace_work_TEST
#define queued_trace_work_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define queued_trace_work_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/queued_trace_work.h"
queued_trace_work_t* instantiate_queued_trace_work(int include_optional);



queued_trace_work_t* instantiate_queued_trace_work(int include_optional) {
  queued_trace_work_t* queued_trace_work = NULL;
  if (include_optional) {
    queued_trace_work = queued_trace_work_create(
      "0",
      "0",
      "0"
    );
  } else {
    queued_trace_work = queued_trace_work_create(
      "0",
      "0",
      "0"
    );
  }

  return queued_trace_work;
}


#ifdef queued_trace_work_MAIN

void test_queued_trace_work(int include_optional) {
    queued_trace_work_t* queued_trace_work_1 = instantiate_queued_trace_work(include_optional);

	cJSON* jsonqueued_trace_work_1 = queued_trace_work_convertToJSON(queued_trace_work_1);
	printf("queued_trace_work :\n%s\n", cJSON_Print(jsonqueued_trace_work_1));
	queued_trace_work_t* queued_trace_work_2 = queued_trace_work_parseFromJSON(jsonqueued_trace_work_1);
	cJSON* jsonqueued_trace_work_2 = queued_trace_work_convertToJSON(queued_trace_work_2);
	printf("repeating queued_trace_work:\n%s\n", cJSON_Print(jsonqueued_trace_work_2));
}

int main() {
  test_queued_trace_work(1);
  test_queued_trace_work(0);

  printf("Hello world \n");
  return 0;
}

#endif // queued_trace_work_MAIN
#endif // queued_trace_work_TEST
