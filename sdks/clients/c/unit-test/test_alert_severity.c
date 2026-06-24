#ifndef alert_severity_TEST
#define alert_severity_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define alert_severity_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/alert_severity.h"
alert_severity_t* instantiate_alert_severity(int include_optional);



alert_severity_t* instantiate_alert_severity(int include_optional) {
  alert_severity_t* alert_severity = NULL;
  if (include_optional) {
    alert_severity = alert_severity_create(
    );
  } else {
    alert_severity = alert_severity_create(
    );
  }

  return alert_severity;
}


#ifdef alert_severity_MAIN

void test_alert_severity(int include_optional) {
    alert_severity_t* alert_severity_1 = instantiate_alert_severity(include_optional);

	cJSON* jsonalert_severity_1 = alert_severity_convertToJSON(alert_severity_1);
	printf("alert_severity :\n%s\n", cJSON_Print(jsonalert_severity_1));
	alert_severity_t* alert_severity_2 = alert_severity_parseFromJSON(jsonalert_severity_1);
	cJSON* jsonalert_severity_2 = alert_severity_convertToJSON(alert_severity_2);
	printf("repeating alert_severity:\n%s\n", cJSON_Print(jsonalert_severity_2));
}

int main() {
  test_alert_severity(1);
  test_alert_severity(0);

  printf("Hello world \n");
  return 0;
}

#endif // alert_severity_MAIN
#endif // alert_severity_TEST
