#ifndef alert_input_TEST
#define alert_input_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define alert_input_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/alert_input.h"
alert_input_t* instantiate_alert_input(int include_optional);

#include "test_alert_links.c"


alert_input_t* instantiate_alert_input(int include_optional) {
  alert_input_t* alert_input = NULL;
  if (include_optional) {
    alert_input = alert_input_create(
      1.337,
      "0",
       // false, not to have infinite recursion
      instantiate_alert_links(0),
      "2013-10-20T19:20:30+01:00",
      "0",
      1.337,
      "0",
      "0",
      "0"
    );
  } else {
    alert_input = alert_input_create(
      1.337,
      "0",
      NULL,
      "2013-10-20T19:20:30+01:00",
      "0",
      1.337,
      "0",
      "0",
      "0"
    );
  }

  return alert_input;
}


#ifdef alert_input_MAIN

void test_alert_input(int include_optional) {
    alert_input_t* alert_input_1 = instantiate_alert_input(include_optional);

	cJSON* jsonalert_input_1 = alert_input_convertToJSON(alert_input_1);
	printf("alert_input :\n%s\n", cJSON_Print(jsonalert_input_1));
	alert_input_t* alert_input_2 = alert_input_parseFromJSON(jsonalert_input_1);
	cJSON* jsonalert_input_2 = alert_input_convertToJSON(alert_input_2);
	printf("repeating alert_input:\n%s\n", cJSON_Print(jsonalert_input_2));
}

int main() {
  test_alert_input(1);
  test_alert_input(0);

  printf("Hello world \n");
  return 0;
}

#endif // alert_input_MAIN
#endif // alert_input_TEST
