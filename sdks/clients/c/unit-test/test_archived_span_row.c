#ifndef archived_span_row_TEST
#define archived_span_row_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define archived_span_row_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/archived_span_row.h"
archived_span_row_t* instantiate_archived_span_row(int include_optional);



archived_span_row_t* instantiate_archived_span_row(int include_optional) {
  archived_span_row_t* archived_span_row = NULL;
  if (include_optional) {
    archived_span_row = archived_span_row_create(
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      0,
      "0",
      "0",
      "0",
      "0",
      "0",
      "0"
    );
  } else {
    archived_span_row = archived_span_row_create(
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      "0",
      0,
      "0",
      "0",
      "0",
      "0",
      "0",
      "0"
    );
  }

  return archived_span_row;
}


#ifdef archived_span_row_MAIN

void test_archived_span_row(int include_optional) {
    archived_span_row_t* archived_span_row_1 = instantiate_archived_span_row(include_optional);

	cJSON* jsonarchived_span_row_1 = archived_span_row_convertToJSON(archived_span_row_1);
	printf("archived_span_row :\n%s\n", cJSON_Print(jsonarchived_span_row_1));
	archived_span_row_t* archived_span_row_2 = archived_span_row_parseFromJSON(jsonarchived_span_row_1);
	cJSON* jsonarchived_span_row_2 = archived_span_row_convertToJSON(archived_span_row_2);
	printf("repeating archived_span_row:\n%s\n", cJSON_Print(jsonarchived_span_row_2));
}

int main() {
  test_archived_span_row(1);
  test_archived_span_row(0);

  printf("Hello world \n");
  return 0;
}

#endif // archived_span_row_MAIN
#endif // archived_span_row_TEST
