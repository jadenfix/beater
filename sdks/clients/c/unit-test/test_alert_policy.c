#ifndef alert_policy_TEST
#define alert_policy_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define alert_policy_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/alert_policy.h"
alert_policy_t* instantiate_alert_policy(int include_optional);



alert_policy_t* instantiate_alert_policy(int include_optional) {
  alert_policy_t* alert_policy = NULL;
  if (include_optional) {
    alert_policy = alert_policy_create(
      56,
      "0",
      1.337,
      list_createList(),
      "0",
      beater_api_alert_policy__info,
      "0"
    );
  } else {
    alert_policy = alert_policy_create(
      56,
      "0",
      1.337,
      list_createList(),
      "0",
      beater_api_alert_policy__info,
      "0"
    );
  }

  return alert_policy;
}


#ifdef alert_policy_MAIN

void test_alert_policy(int include_optional) {
    alert_policy_t* alert_policy_1 = instantiate_alert_policy(include_optional);

	cJSON* jsonalert_policy_1 = alert_policy_convertToJSON(alert_policy_1);
	printf("alert_policy :\n%s\n", cJSON_Print(jsonalert_policy_1));
	alert_policy_t* alert_policy_2 = alert_policy_parseFromJSON(jsonalert_policy_1);
	cJSON* jsonalert_policy_2 = alert_policy_convertToJSON(alert_policy_2);
	printf("repeating alert_policy:\n%s\n", cJSON_Print(jsonalert_policy_2));
}

int main() {
  test_alert_policy(1);
  test_alert_policy(0);

  printf("Hello world \n");
  return 0;
}

#endif // alert_policy_MAIN
#endif // alert_policy_TEST
