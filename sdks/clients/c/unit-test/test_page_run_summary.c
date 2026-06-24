#ifndef page_run_summary_TEST
#define page_run_summary_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define page_run_summary_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/page_run_summary.h"
page_run_summary_t* instantiate_page_run_summary(int include_optional);



page_run_summary_t* instantiate_page_run_summary(int include_optional) {
  page_run_summary_t* page_run_summary = NULL;
  if (include_optional) {
    page_run_summary = page_run_summary_create(
      list_createList(),
      "0"
    );
  } else {
    page_run_summary = page_run_summary_create(
      list_createList(),
      "0"
    );
  }

  return page_run_summary;
}


#ifdef page_run_summary_MAIN

void test_page_run_summary(int include_optional) {
    page_run_summary_t* page_run_summary_1 = instantiate_page_run_summary(include_optional);

	cJSON* jsonpage_run_summary_1 = page_run_summary_convertToJSON(page_run_summary_1);
	printf("page_run_summary :\n%s\n", cJSON_Print(jsonpage_run_summary_1));
	page_run_summary_t* page_run_summary_2 = page_run_summary_parseFromJSON(jsonpage_run_summary_1);
	cJSON* jsonpage_run_summary_2 = page_run_summary_convertToJSON(page_run_summary_2);
	printf("repeating page_run_summary:\n%s\n", cJSON_Print(jsonpage_run_summary_2));
}

int main() {
  test_page_run_summary(1);
  test_page_run_summary(0);

  printf("Hello world \n");
  return 0;
}

#endif // page_run_summary_MAIN
#endif // page_run_summary_TEST
