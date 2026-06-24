#ifndef audit_event_TEST
#define audit_event_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define audit_event_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/audit_event.h"
audit_event_t* instantiate_audit_event(int include_optional);



audit_event_t* instantiate_audit_event(int include_optional) {
  audit_event_t* audit_event = NULL;
  if (include_optional) {
    audit_event = audit_event_create(
      beater_api_audit_event__pii_unmask,
      "0",
      null,
      "0",
      "2013-10-20T19:20:30+01:00",
      "0",
      beater_api_audit_event__allowed,
      "0",
      "0",
      "0",
      "0",
      "0"
    );
  } else {
    audit_event = audit_event_create(
      beater_api_audit_event__pii_unmask,
      "0",
      null,
      "0",
      "2013-10-20T19:20:30+01:00",
      "0",
      beater_api_audit_event__allowed,
      "0",
      "0",
      "0",
      "0",
      "0"
    );
  }

  return audit_event;
}


#ifdef audit_event_MAIN

void test_audit_event(int include_optional) {
    audit_event_t* audit_event_1 = instantiate_audit_event(include_optional);

	cJSON* jsonaudit_event_1 = audit_event_convertToJSON(audit_event_1);
	printf("audit_event :\n%s\n", cJSON_Print(jsonaudit_event_1));
	audit_event_t* audit_event_2 = audit_event_parseFromJSON(jsonaudit_event_1);
	cJSON* jsonaudit_event_2 = audit_event_convertToJSON(audit_event_2);
	printf("repeating audit_event:\n%s\n", cJSON_Print(jsonaudit_event_2));
}

int main() {
  test_audit_event(1);
  test_audit_event(0);

  printf("Hello world \n");
  return 0;
}

#endif // audit_event_MAIN
#endif // audit_event_TEST
