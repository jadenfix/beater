#ifndef archive_manifest_TEST
#define archive_manifest_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define archive_manifest_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/archive_manifest.h"
archive_manifest_t* instantiate_archive_manifest(int include_optional);



archive_manifest_t* instantiate_archive_manifest(int include_optional) {
  archive_manifest_t* archive_manifest = NULL;
  if (include_optional) {
    archive_manifest = archive_manifest_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      0,
      "0"
    );
  } else {
    archive_manifest = archive_manifest_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      0,
      "0"
    );
  }

  return archive_manifest;
}


#ifdef archive_manifest_MAIN

void test_archive_manifest(int include_optional) {
    archive_manifest_t* archive_manifest_1 = instantiate_archive_manifest(include_optional);

	cJSON* jsonarchive_manifest_1 = archive_manifest_convertToJSON(archive_manifest_1);
	printf("archive_manifest :\n%s\n", cJSON_Print(jsonarchive_manifest_1));
	archive_manifest_t* archive_manifest_2 = archive_manifest_parseFromJSON(jsonarchive_manifest_1);
	cJSON* jsonarchive_manifest_2 = archive_manifest_convertToJSON(archive_manifest_2);
	printf("repeating archive_manifest:\n%s\n", cJSON_Print(jsonarchive_manifest_2));
}

int main() {
  test_archive_manifest(1);
  test_archive_manifest(0);

  printf("Hello world \n");
  return 0;
}

#endif // archive_manifest_MAIN
#endif // archive_manifest_TEST
