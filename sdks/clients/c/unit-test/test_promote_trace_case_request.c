#ifndef promote_trace_case_request_TEST
#define promote_trace_case_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define promote_trace_case_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/promote_trace_case_request.h"
promote_trace_case_request_t* instantiate_promote_trace_case_request(int include_optional);



promote_trace_case_request_t* instantiate_promote_trace_case_request(int include_optional) {
  promote_trace_case_request_t* promote_trace_case_request = NULL;
  if (include_optional) {
    promote_trace_case_request = promote_trace_case_request_create(
      null,
      "0",
      "0"
    );
  } else {
    promote_trace_case_request = promote_trace_case_request_create(
      null,
      "0",
      "0"
    );
  }

  return promote_trace_case_request;
}


#ifdef promote_trace_case_request_MAIN

void test_promote_trace_case_request(int include_optional) {
    promote_trace_case_request_t* promote_trace_case_request_1 = instantiate_promote_trace_case_request(include_optional);

	cJSON* jsonpromote_trace_case_request_1 = promote_trace_case_request_convertToJSON(promote_trace_case_request_1);
	printf("promote_trace_case_request :\n%s\n", cJSON_Print(jsonpromote_trace_case_request_1));
	promote_trace_case_request_t* promote_trace_case_request_2 = promote_trace_case_request_parseFromJSON(jsonpromote_trace_case_request_1);
	cJSON* jsonpromote_trace_case_request_2 = promote_trace_case_request_convertToJSON(promote_trace_case_request_2);
	printf("repeating promote_trace_case_request:\n%s\n", cJSON_Print(jsonpromote_trace_case_request_2));
}

int main() {
  test_promote_trace_case_request(1);
  test_promote_trace_case_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // promote_trace_case_request_MAIN
#endif // promote_trace_case_request_TEST
