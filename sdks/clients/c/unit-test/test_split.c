#ifndef split_TEST
#define split_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define split_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/split.h"
split_t* instantiate_split(int include_optional);



split_t* instantiate_split(int include_optional) {
  split_t* split = NULL;
  if (include_optional) {
    split = split_create(
    );
  } else {
    split = split_create(
    );
  }

  return split;
}


#ifdef split_MAIN

void test_split(int include_optional) {
    split_t* split_1 = instantiate_split(include_optional);

	cJSON* jsonsplit_1 = split_convertToJSON(split_1);
	printf("split :\n%s\n", cJSON_Print(jsonsplit_1));
	split_t* split_2 = split_parseFromJSON(jsonsplit_1);
	cJSON* jsonsplit_2 = split_convertToJSON(split_2);
	printf("repeating split:\n%s\n", cJSON_Print(jsonsplit_2));
}

int main() {
  test_split(1);
  test_split(0);

  printf("Hello world \n");
  return 0;
}

#endif // split_MAIN
#endif // split_TEST
