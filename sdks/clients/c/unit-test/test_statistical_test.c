#ifndef statistical_test_TEST
#define statistical_test_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define statistical_test_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/statistical_test.h"
statistical_test_t* instantiate_statistical_test(int include_optional);



statistical_test_t* instantiate_statistical_test(int include_optional) {
  statistical_test_t* statistical_test = NULL;
  if (include_optional) {
    statistical_test = statistical_test_create(
    );
  } else {
    statistical_test = statistical_test_create(
    );
  }

  return statistical_test;
}


#ifdef statistical_test_MAIN

void test_statistical_test(int include_optional) {
    statistical_test_t* statistical_test_1 = instantiate_statistical_test(include_optional);

	cJSON* jsonstatistical_test_1 = statistical_test_convertToJSON(statistical_test_1);
	printf("statistical_test :\n%s\n", cJSON_Print(jsonstatistical_test_1));
	statistical_test_t* statistical_test_2 = statistical_test_parseFromJSON(jsonstatistical_test_1);
	cJSON* jsonstatistical_test_2 = statistical_test_convertToJSON(statistical_test_2);
	printf("repeating statistical_test:\n%s\n", cJSON_Print(jsonstatistical_test_2));
}

int main() {
  test_statistical_test(1);
  test_statistical_test(0);

  printf("Hello world \n");
  return 0;
}

#endif // statistical_test_MAIN
#endif // statistical_test_TEST
