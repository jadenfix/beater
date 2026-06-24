#ifndef token_counts_TEST
#define token_counts_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define token_counts_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/token_counts.h"
token_counts_t* instantiate_token_counts(int include_optional);



token_counts_t* instantiate_token_counts(int include_optional) {
  token_counts_t* token_counts = NULL;
  if (include_optional) {
    token_counts = token_counts_create(
      0,
      0,
      0,
      0
    );
  } else {
    token_counts = token_counts_create(
      0,
      0,
      0,
      0
    );
  }

  return token_counts;
}


#ifdef token_counts_MAIN

void test_token_counts(int include_optional) {
    token_counts_t* token_counts_1 = instantiate_token_counts(include_optional);

	cJSON* jsontoken_counts_1 = token_counts_convertToJSON(token_counts_1);
	printf("token_counts :\n%s\n", cJSON_Print(jsontoken_counts_1));
	token_counts_t* token_counts_2 = token_counts_parseFromJSON(jsontoken_counts_1);
	cJSON* jsontoken_counts_2 = token_counts_convertToJSON(token_counts_2);
	printf("repeating token_counts:\n%s\n", cJSON_Print(jsontoken_counts_2));
}

int main() {
  test_token_counts(1);
  test_token_counts(0);

  printf("Hello world \n");
  return 0;
}

#endif // token_counts_MAIN
#endif // token_counts_TEST
