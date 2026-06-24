#ifndef archive_query_response_TEST
#define archive_query_response_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define archive_query_response_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/archive_query_response.h"
archive_query_response_t* instantiate_archive_query_response(int include_optional);



archive_query_response_t* instantiate_archive_query_response(int include_optional) {
  archive_query_response_t* archive_query_response = NULL;
  if (include_optional) {
    archive_query_response = archive_query_response_create(
      list_createList()
    );
  } else {
    archive_query_response = archive_query_response_create(
      list_createList()
    );
  }

  return archive_query_response;
}


#ifdef archive_query_response_MAIN

void test_archive_query_response(int include_optional) {
    archive_query_response_t* archive_query_response_1 = instantiate_archive_query_response(include_optional);

	cJSON* jsonarchive_query_response_1 = archive_query_response_convertToJSON(archive_query_response_1);
	printf("archive_query_response :\n%s\n", cJSON_Print(jsonarchive_query_response_1));
	archive_query_response_t* archive_query_response_2 = archive_query_response_parseFromJSON(jsonarchive_query_response_1);
	cJSON* jsonarchive_query_response_2 = archive_query_response_convertToJSON(archive_query_response_2);
	printf("repeating archive_query_response:\n%s\n", cJSON_Print(jsonarchive_query_response_2));
}

int main() {
  test_archive_query_response(1);
  test_archive_query_response(0);

  printf("Hello world \n");
  return 0;
}

#endif // archive_query_response_MAIN
#endif // archive_query_response_TEST
