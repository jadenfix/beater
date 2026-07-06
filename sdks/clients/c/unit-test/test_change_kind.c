#ifndef change_kind_TEST
#define change_kind_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define change_kind_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/change_kind.h"
change_kind_t* instantiate_change_kind(int include_optional);



change_kind_t* instantiate_change_kind(int include_optional) {
  change_kind_t* change_kind = NULL;
  if (include_optional) {
    change_kind = change_kind_create(
    );
  } else {
    change_kind = change_kind_create(
    );
  }

  return change_kind;
}


#ifdef change_kind_MAIN

void test_change_kind(int include_optional) {
    change_kind_t* change_kind_1 = instantiate_change_kind(include_optional);

	cJSON* jsonchange_kind_1 = change_kind_convertToJSON(change_kind_1);
	printf("change_kind :\n%s\n", cJSON_Print(jsonchange_kind_1));
	change_kind_t* change_kind_2 = change_kind_parseFromJSON(jsonchange_kind_1);
	cJSON* jsonchange_kind_2 = change_kind_convertToJSON(change_kind_2);
	printf("repeating change_kind:\n%s\n", cJSON_Print(jsonchange_kind_2));
}

int main() {
  test_change_kind(1);
  test_change_kind(0);

  printf("Hello world \n");
  return 0;
}

#endif // change_kind_MAIN
#endif // change_kind_TEST
