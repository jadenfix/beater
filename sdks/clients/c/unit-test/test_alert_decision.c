#ifndef alert_decision_TEST
#define alert_decision_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define alert_decision_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/alert_decision.h"
alert_decision_t* instantiate_alert_decision(int include_optional);

#include "test_webhook_delivery.c"


alert_decision_t* instantiate_alert_decision(int include_optional) {
  alert_decision_t* alert_decision = NULL;
  if (include_optional) {
    alert_decision = alert_decision_create(
       // false, not to have infinite recursion
      instantiate_webhook_delivery(0),
      1,
      "0"
    );
  } else {
    alert_decision = alert_decision_create(
      NULL,
      1,
      "0"
    );
  }

  return alert_decision;
}


#ifdef alert_decision_MAIN

void test_alert_decision(int include_optional) {
    alert_decision_t* alert_decision_1 = instantiate_alert_decision(include_optional);

	cJSON* jsonalert_decision_1 = alert_decision_convertToJSON(alert_decision_1);
	printf("alert_decision :\n%s\n", cJSON_Print(jsonalert_decision_1));
	alert_decision_t* alert_decision_2 = alert_decision_parseFromJSON(jsonalert_decision_1);
	cJSON* jsonalert_decision_2 = alert_decision_convertToJSON(alert_decision_2);
	printf("repeating alert_decision:\n%s\n", cJSON_Print(jsonalert_decision_2));
}

int main() {
  test_alert_decision(1);
  test_alert_decision(0);

  printf("Hello world \n");
  return 0;
}

#endif // alert_decision_MAIN
#endif // alert_decision_TEST
