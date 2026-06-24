#ifndef search_hit_TEST
#define search_hit_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define search_hit_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/search_hit.h"
search_hit_t* instantiate_search_hit(int include_optional);



search_hit_t* instantiate_search_hit(int include_optional) {
  search_hit_t* search_hit = NULL;
  if (include_optional) {
    search_hit = search_hit_create(
      "0",
      "0",
      "0",
      "0",
      "0",
      1.337,
      "0",
      "0",
      "0",
      "0",
      "0"
    );
  } else {
    search_hit = search_hit_create(
      "0",
      "0",
      "0",
      "0",
      "0",
      1.337,
      "0",
      "0",
      "0",
      "0",
      "0"
    );
  }

  return search_hit;
}


#ifdef search_hit_MAIN

void test_search_hit(int include_optional) {
    search_hit_t* search_hit_1 = instantiate_search_hit(include_optional);

	cJSON* jsonsearch_hit_1 = search_hit_convertToJSON(search_hit_1);
	printf("search_hit :\n%s\n", cJSON_Print(jsonsearch_hit_1));
	search_hit_t* search_hit_2 = search_hit_parseFromJSON(jsonsearch_hit_1);
	cJSON* jsonsearch_hit_2 = search_hit_convertToJSON(search_hit_2);
	printf("repeating search_hit:\n%s\n", cJSON_Print(jsonsearch_hit_2));
}

int main() {
  test_search_hit(1);
  test_search_hit(0);

  printf("Hello world \n");
  return 0;
}

#endif // search_hit_MAIN
#endif // search_hit_TEST
