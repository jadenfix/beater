#ifndef online_sampling_policy_TEST
#define online_sampling_policy_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define online_sampling_policy_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/online_sampling_policy.h"
online_sampling_policy_t* instantiate_online_sampling_policy(int include_optional);



online_sampling_policy_t* instantiate_online_sampling_policy(int include_optional) {
  online_sampling_policy_t* online_sampling_policy = NULL;
  if (include_optional) {
    online_sampling_policy = online_sampling_policy_create(
      56,
      1,
      0,
      0
    );
  } else {
    online_sampling_policy = online_sampling_policy_create(
      56,
      1,
      0,
      0
    );
  }

  return online_sampling_policy;
}


#ifdef online_sampling_policy_MAIN

void test_online_sampling_policy(int include_optional) {
    online_sampling_policy_t* online_sampling_policy_1 = instantiate_online_sampling_policy(include_optional);

	cJSON* jsononline_sampling_policy_1 = online_sampling_policy_convertToJSON(online_sampling_policy_1);
	printf("online_sampling_policy :\n%s\n", cJSON_Print(jsononline_sampling_policy_1));
	online_sampling_policy_t* online_sampling_policy_2 = online_sampling_policy_parseFromJSON(jsononline_sampling_policy_1);
	cJSON* jsononline_sampling_policy_2 = online_sampling_policy_convertToJSON(online_sampling_policy_2);
	printf("repeating online_sampling_policy:\n%s\n", cJSON_Print(jsononline_sampling_policy_2));
}

int main() {
  test_online_sampling_policy(1);
  test_online_sampling_policy(0);

  printf("Hello world \n");
  return 0;
}

#endif // online_sampling_policy_MAIN
#endif // online_sampling_policy_TEST
