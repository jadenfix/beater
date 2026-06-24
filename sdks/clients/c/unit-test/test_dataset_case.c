#ifndef dataset_case_TEST
#define dataset_case_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define dataset_case_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/dataset_case.h"
dataset_case_t* instantiate_dataset_case(int include_optional);



dataset_case_t* instantiate_dataset_case(int include_optional) {
  dataset_case_t* dataset_case = NULL;
  if (include_optional) {
    dataset_case = dataset_case_create(
      "0",
      "2013-10-20T19:20:30+01:00",
      "0",
      null,
      list_createList(),
      "0",
      null,
      "0",
      null,
      "0",
      "0",
      "0",
      "0",
      null,
      0
    );
  } else {
    dataset_case = dataset_case_create(
      "0",
      "2013-10-20T19:20:30+01:00",
      "0",
      null,
      list_createList(),
      "0",
      null,
      "0",
      null,
      "0",
      "0",
      "0",
      "0",
      null,
      0
    );
  }

  return dataset_case;
}


#ifdef dataset_case_MAIN

void test_dataset_case(int include_optional) {
    dataset_case_t* dataset_case_1 = instantiate_dataset_case(include_optional);

	cJSON* jsondataset_case_1 = dataset_case_convertToJSON(dataset_case_1);
	printf("dataset_case :\n%s\n", cJSON_Print(jsondataset_case_1));
	dataset_case_t* dataset_case_2 = dataset_case_parseFromJSON(jsondataset_case_1);
	cJSON* jsondataset_case_2 = dataset_case_convertToJSON(dataset_case_2);
	printf("repeating dataset_case:\n%s\n", cJSON_Print(jsondataset_case_2));
}

int main() {
  test_dataset_case(1);
  test_dataset_case(0);

  printf("Hello world \n");
  return 0;
}

#endif // dataset_case_MAIN
#endif // dataset_case_TEST
