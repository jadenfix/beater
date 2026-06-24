#ifndef usage_summary_TEST
#define usage_summary_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define usage_summary_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/usage_summary.h"
usage_summary_t* instantiate_usage_summary(int include_optional);



usage_summary_t* instantiate_usage_summary(int include_optional) {
  usage_summary_t* usage_summary = NULL;
  if (include_optional) {
    usage_summary = usage_summary_create(
      "0",
      "0",
      list_createList()
    );
  } else {
    usage_summary = usage_summary_create(
      "0",
      "0",
      list_createList()
    );
  }

  return usage_summary;
}


#ifdef usage_summary_MAIN

void test_usage_summary(int include_optional) {
    usage_summary_t* usage_summary_1 = instantiate_usage_summary(include_optional);

	cJSON* jsonusage_summary_1 = usage_summary_convertToJSON(usage_summary_1);
	printf("usage_summary :\n%s\n", cJSON_Print(jsonusage_summary_1));
	usage_summary_t* usage_summary_2 = usage_summary_parseFromJSON(jsonusage_summary_1);
	cJSON* jsonusage_summary_2 = usage_summary_convertToJSON(usage_summary_2);
	printf("repeating usage_summary:\n%s\n", cJSON_Print(jsonusage_summary_2));
}

int main() {
  test_usage_summary(1);
  test_usage_summary(0);

  printf("Hello world \n");
  return 0;
}

#endif // usage_summary_MAIN
#endif // usage_summary_TEST
