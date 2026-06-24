#ifndef dataset_TEST
#define dataset_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define dataset_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/dataset.h"
dataset_t* instantiate_dataset(int include_optional);



dataset_t* instantiate_dataset(int include_optional) {
  dataset_t* dataset = NULL;
  if (include_optional) {
    dataset = dataset_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0"
    );
  } else {
    dataset = dataset_create(
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0"
    );
  }

  return dataset;
}


#ifdef dataset_MAIN

void test_dataset(int include_optional) {
    dataset_t* dataset_1 = instantiate_dataset(include_optional);

	cJSON* jsondataset_1 = dataset_convertToJSON(dataset_1);
	printf("dataset :\n%s\n", cJSON_Print(jsondataset_1));
	dataset_t* dataset_2 = dataset_parseFromJSON(jsondataset_1);
	cJSON* jsondataset_2 = dataset_convertToJSON(dataset_2);
	printf("repeating dataset:\n%s\n", cJSON_Print(jsondataset_2));
}

int main() {
  test_dataset(1);
  test_dataset(0);

  printf("Hello world \n");
  return 0;
}

#endif // dataset_MAIN
#endif // dataset_TEST
