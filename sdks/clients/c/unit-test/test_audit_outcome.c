#ifndef audit_outcome_TEST
#define audit_outcome_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define audit_outcome_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/audit_outcome.h"
audit_outcome_t* instantiate_audit_outcome(int include_optional);



audit_outcome_t* instantiate_audit_outcome(int include_optional) {
  audit_outcome_t* audit_outcome = NULL;
  if (include_optional) {
    audit_outcome = audit_outcome_create(
    );
  } else {
    audit_outcome = audit_outcome_create(
    );
  }

  return audit_outcome;
}


#ifdef audit_outcome_MAIN

void test_audit_outcome(int include_optional) {
    audit_outcome_t* audit_outcome_1 = instantiate_audit_outcome(include_optional);

	cJSON* jsonaudit_outcome_1 = audit_outcome_convertToJSON(audit_outcome_1);
	printf("audit_outcome :\n%s\n", cJSON_Print(jsonaudit_outcome_1));
	audit_outcome_t* audit_outcome_2 = audit_outcome_parseFromJSON(jsonaudit_outcome_1);
	cJSON* jsonaudit_outcome_2 = audit_outcome_convertToJSON(audit_outcome_2);
	printf("repeating audit_outcome:\n%s\n", cJSON_Print(jsonaudit_outcome_2));
}

int main() {
  test_audit_outcome(1);
  test_audit_outcome(0);

  printf("Hello world \n");
  return 0;
}

#endif // audit_outcome_MAIN
#endif // audit_outcome_TEST
