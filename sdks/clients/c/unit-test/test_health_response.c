#ifndef health_response_TEST
#define health_response_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define health_response_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/health_response.h"
health_response_t* instantiate_health_response(int include_optional);



health_response_t* instantiate_health_response(int include_optional) {
  health_response_t* health_response = NULL;
  if (include_optional) {
    health_response = health_response_create(
      1
    );
  } else {
    health_response = health_response_create(
      1
    );
  }

  return health_response;
}


#ifdef health_response_MAIN

void test_health_response(int include_optional) {
    health_response_t* health_response_1 = instantiate_health_response(include_optional);

	cJSON* jsonhealth_response_1 = health_response_convertToJSON(health_response_1);
	printf("health_response :\n%s\n", cJSON_Print(jsonhealth_response_1));
	health_response_t* health_response_2 = health_response_parseFromJSON(jsonhealth_response_1);
	cJSON* jsonhealth_response_2 = health_response_convertToJSON(health_response_2);
	printf("repeating health_response:\n%s\n", cJSON_Print(jsonhealth_response_2));
}

int main() {
  test_health_response(1);
  test_health_response(0);

  printf("Hello world \n");
  return 0;
}

#endif // health_response_MAIN
#endif // health_response_TEST
