#ifndef page_run_summary_items_inner_TEST
#define page_run_summary_items_inner_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define page_run_summary_items_inner_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/page_run_summary_items_inner.h"
page_run_summary_items_inner_t* instantiate_page_run_summary_items_inner(int include_optional);

#include "test_money.c"


page_run_summary_items_inner_t* instantiate_page_run_summary_items_inner(int include_optional) {
  page_run_summary_items_inner_t* page_run_summary_items_inner = NULL;
  if (include_optional) {
    page_run_summary_items_inner = page_run_summary_items_inner_create(
      56,
      "2013-10-20T19:20:30+01:00",
      "0",
      list_createList(),
      "0",
      list_createList(),
      0,
      "2013-10-20T19:20:30+01:00",
      beater_api_page_run_summary_items_inner__ok,
      "0",
       // false, not to have infinite recursion
      instantiate_money(0),
      "0"
    );
  } else {
    page_run_summary_items_inner = page_run_summary_items_inner_create(
      56,
      "2013-10-20T19:20:30+01:00",
      "0",
      list_createList(),
      "0",
      list_createList(),
      0,
      "2013-10-20T19:20:30+01:00",
      beater_api_page_run_summary_items_inner__ok,
      "0",
      NULL,
      "0"
    );
  }

  return page_run_summary_items_inner;
}


#ifdef page_run_summary_items_inner_MAIN

void test_page_run_summary_items_inner(int include_optional) {
    page_run_summary_items_inner_t* page_run_summary_items_inner_1 = instantiate_page_run_summary_items_inner(include_optional);

	cJSON* jsonpage_run_summary_items_inner_1 = page_run_summary_items_inner_convertToJSON(page_run_summary_items_inner_1);
	printf("page_run_summary_items_inner :\n%s\n", cJSON_Print(jsonpage_run_summary_items_inner_1));
	page_run_summary_items_inner_t* page_run_summary_items_inner_2 = page_run_summary_items_inner_parseFromJSON(jsonpage_run_summary_items_inner_1);
	cJSON* jsonpage_run_summary_items_inner_2 = page_run_summary_items_inner_convertToJSON(page_run_summary_items_inner_2);
	printf("repeating page_run_summary_items_inner:\n%s\n", cJSON_Print(jsonpage_run_summary_items_inner_2));
}

int main() {
  test_page_run_summary_items_inner(1);
  test_page_run_summary_items_inner(0);

  printf("Hello world \n");
  return 0;
}

#endif // page_run_summary_items_inner_MAIN
#endif // page_run_summary_items_inner_TEST
