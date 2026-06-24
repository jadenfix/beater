#ifndef usage_total_TEST
#define usage_total_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define usage_total_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/usage_total.h"
usage_total_t* instantiate_usage_total(int include_optional);



usage_total_t* instantiate_usage_total(int include_optional) {
  usage_total_t* usage_total = NULL;
  if (include_optional) {
    usage_total = usage_total_create(
      56,
      "0"
    );
  } else {
    usage_total = usage_total_create(
      56,
      "0"
    );
  }

  return usage_total;
}


#ifdef usage_total_MAIN

void test_usage_total(int include_optional) {
    usage_total_t* usage_total_1 = instantiate_usage_total(include_optional);

	cJSON* jsonusage_total_1 = usage_total_convertToJSON(usage_total_1);
	printf("usage_total :\n%s\n", cJSON_Print(jsonusage_total_1));
	usage_total_t* usage_total_2 = usage_total_parseFromJSON(jsonusage_total_1);
	cJSON* jsonusage_total_2 = usage_total_convertToJSON(usage_total_2);
	printf("repeating usage_total:\n%s\n", cJSON_Print(jsonusage_total_2));
}

int main() {
  test_usage_total(1);
  test_usage_total(0);

  printf("Hello world \n");
  return 0;
}

#endif // usage_total_MAIN
#endif // usage_total_TEST
