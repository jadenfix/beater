#ifndef provider_secret_metadata_TEST
#define provider_secret_metadata_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define provider_secret_metadata_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/provider_secret_metadata.h"
provider_secret_metadata_t* instantiate_provider_secret_metadata(int include_optional);



provider_secret_metadata_t* instantiate_provider_secret_metadata(int include_optional) {
  provider_secret_metadata_t* provider_secret_metadata = NULL;
  if (include_optional) {
    provider_secret_metadata = provider_secret_metadata_create(
      1,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0",
      "2013-10-20T19:20:30+01:00",
      "0"
    );
  } else {
    provider_secret_metadata = provider_secret_metadata_create(
      1,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0",
      "2013-10-20T19:20:30+01:00",
      "0"
    );
  }

  return provider_secret_metadata;
}


#ifdef provider_secret_metadata_MAIN

void test_provider_secret_metadata(int include_optional) {
    provider_secret_metadata_t* provider_secret_metadata_1 = instantiate_provider_secret_metadata(include_optional);

	cJSON* jsonprovider_secret_metadata_1 = provider_secret_metadata_convertToJSON(provider_secret_metadata_1);
	printf("provider_secret_metadata :\n%s\n", cJSON_Print(jsonprovider_secret_metadata_1));
	provider_secret_metadata_t* provider_secret_metadata_2 = provider_secret_metadata_parseFromJSON(jsonprovider_secret_metadata_1);
	cJSON* jsonprovider_secret_metadata_2 = provider_secret_metadata_convertToJSON(provider_secret_metadata_2);
	printf("repeating provider_secret_metadata:\n%s\n", cJSON_Print(jsonprovider_secret_metadata_2));
}

int main() {
  test_provider_secret_metadata(1);
  test_provider_secret_metadata(0);

  printf("Hello world \n");
  return 0;
}

#endif // provider_secret_metadata_MAIN
#endif // provider_secret_metadata_TEST
