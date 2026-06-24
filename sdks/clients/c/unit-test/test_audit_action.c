#ifndef audit_action_TEST
#define audit_action_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define audit_action_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/audit_action.h"
audit_action_t* instantiate_audit_action(int include_optional);



audit_action_t* instantiate_audit_action(int include_optional) {
  audit_action_t* audit_action = NULL;
  if (include_optional) {
    audit_action = audit_action_create(
    );
  } else {
    audit_action = audit_action_create(
    );
  }

  return audit_action;
}


#ifdef audit_action_MAIN

void test_audit_action(int include_optional) {
    audit_action_t* audit_action_1 = instantiate_audit_action(include_optional);

	cJSON* jsonaudit_action_1 = audit_action_convertToJSON(audit_action_1);
	printf("audit_action :\n%s\n", cJSON_Print(jsonaudit_action_1));
	audit_action_t* audit_action_2 = audit_action_parseFromJSON(jsonaudit_action_1);
	cJSON* jsonaudit_action_2 = audit_action_convertToJSON(audit_action_2);
	printf("repeating audit_action:\n%s\n", cJSON_Print(jsonaudit_action_2));
}

int main() {
  test_audit_action(1);
  test_audit_action(0);

  printf("Hello world \n");
  return 0;
}

#endif // audit_action_MAIN
#endif // audit_action_TEST
