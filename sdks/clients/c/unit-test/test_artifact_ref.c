#ifndef artifact_ref_TEST
#define artifact_ref_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define artifact_ref_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/artifact_ref.h"
artifact_ref_t* instantiate_artifact_ref(int include_optional);



artifact_ref_t* instantiate_artifact_ref(int include_optional) {
  artifact_ref_t* artifact_ref = NULL;
  if (include_optional) {
    artifact_ref = artifact_ref_create(
      "0",
      "0",
      beater_api_artifact_ref__public,
      "0",
      0,
      "0"
    );
  } else {
    artifact_ref = artifact_ref_create(
      "0",
      "0",
      beater_api_artifact_ref__public,
      "0",
      0,
      "0"
    );
  }

  return artifact_ref;
}


#ifdef artifact_ref_MAIN

void test_artifact_ref(int include_optional) {
    artifact_ref_t* artifact_ref_1 = instantiate_artifact_ref(include_optional);

	cJSON* jsonartifact_ref_1 = artifact_ref_convertToJSON(artifact_ref_1);
	printf("artifact_ref :\n%s\n", cJSON_Print(jsonartifact_ref_1));
	artifact_ref_t* artifact_ref_2 = artifact_ref_parseFromJSON(jsonartifact_ref_1);
	cJSON* jsonartifact_ref_2 = artifact_ref_convertToJSON(artifact_ref_2);
	printf("repeating artifact_ref:\n%s\n", cJSON_Print(jsonartifact_ref_2));
}

int main() {
  test_artifact_ref(1);
  test_artifact_ref(0);

  printf("Hello world \n");
  return 0;
}

#endif // artifact_ref_MAIN
#endif // artifact_ref_TEST
