#ifndef inconclusive_policy_TEST
#define inconclusive_policy_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define inconclusive_policy_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/inconclusive_policy.h"
inconclusive_policy_t* instantiate_inconclusive_policy(int include_optional);



inconclusive_policy_t* instantiate_inconclusive_policy(int include_optional) {
  inconclusive_policy_t* inconclusive_policy = NULL;
  if (include_optional) {
    inconclusive_policy = inconclusive_policy_create(
    );
  } else {
    inconclusive_policy = inconclusive_policy_create(
    );
  }

  return inconclusive_policy;
}


#ifdef inconclusive_policy_MAIN

void test_inconclusive_policy(int include_optional) {
    inconclusive_policy_t* inconclusive_policy_1 = instantiate_inconclusive_policy(include_optional);

	cJSON* jsoninconclusive_policy_1 = inconclusive_policy_convertToJSON(inconclusive_policy_1);
	printf("inconclusive_policy :\n%s\n", cJSON_Print(jsoninconclusive_policy_1));
	inconclusive_policy_t* inconclusive_policy_2 = inconclusive_policy_parseFromJSON(jsoninconclusive_policy_1);
	cJSON* jsoninconclusive_policy_2 = inconclusive_policy_convertToJSON(inconclusive_policy_2);
	printf("repeating inconclusive_policy:\n%s\n", cJSON_Print(jsoninconclusive_policy_2));
}

int main() {
  test_inconclusive_policy(1);
  test_inconclusive_policy(0);

  printf("Hello world \n");
  return 0;
}

#endif // inconclusive_policy_MAIN
#endif // inconclusive_policy_TEST
