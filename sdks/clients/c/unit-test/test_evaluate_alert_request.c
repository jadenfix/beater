#ifndef evaluate_alert_request_TEST
#define evaluate_alert_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define evaluate_alert_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/evaluate_alert_request.h"
evaluate_alert_request_t* instantiate_evaluate_alert_request(int include_optional);

#include "test_alert_input.c"
#include "test_alert_policy.c"


evaluate_alert_request_t* instantiate_evaluate_alert_request(int include_optional) {
  evaluate_alert_request_t* evaluate_alert_request = NULL;
  if (include_optional) {
    evaluate_alert_request = evaluate_alert_request_create(
       // false, not to have infinite recursion
      instantiate_alert_input(0),
       // false, not to have infinite recursion
      instantiate_alert_policy(0)
    );
  } else {
    evaluate_alert_request = evaluate_alert_request_create(
      NULL,
      NULL
    );
  }

  return evaluate_alert_request;
}


#ifdef evaluate_alert_request_MAIN

void test_evaluate_alert_request(int include_optional) {
    evaluate_alert_request_t* evaluate_alert_request_1 = instantiate_evaluate_alert_request(include_optional);

	cJSON* jsonevaluate_alert_request_1 = evaluate_alert_request_convertToJSON(evaluate_alert_request_1);
	printf("evaluate_alert_request :\n%s\n", cJSON_Print(jsonevaluate_alert_request_1));
	evaluate_alert_request_t* evaluate_alert_request_2 = evaluate_alert_request_parseFromJSON(jsonevaluate_alert_request_1);
	cJSON* jsonevaluate_alert_request_2 = evaluate_alert_request_convertToJSON(evaluate_alert_request_2);
	printf("repeating evaluate_alert_request:\n%s\n", cJSON_Print(jsonevaluate_alert_request_2));
}

int main() {
  test_evaluate_alert_request(1);
  test_evaluate_alert_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // evaluate_alert_request_MAIN
#endif // evaluate_alert_request_TEST
