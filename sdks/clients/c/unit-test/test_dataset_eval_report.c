#ifndef dataset_eval_report_TEST
#define dataset_eval_report_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define dataset_eval_report_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/dataset_eval_report.h"
dataset_eval_report_t* instantiate_dataset_eval_report(int include_optional);



dataset_eval_report_t* instantiate_dataset_eval_report(int include_optional) {
  dataset_eval_report_t* dataset_eval_report = NULL;
  if (include_optional) {
    dataset_eval_report = dataset_eval_report_create(
      1.337,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0",
      "0",
      0,
      list_createList(),
      "0"
    );
  } else {
    dataset_eval_report = dataset_eval_report_create(
      1.337,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0",
      "0",
      0,
      list_createList(),
      "0"
    );
  }

  return dataset_eval_report;
}


#ifdef dataset_eval_report_MAIN

void test_dataset_eval_report(int include_optional) {
    dataset_eval_report_t* dataset_eval_report_1 = instantiate_dataset_eval_report(include_optional);

	cJSON* jsondataset_eval_report_1 = dataset_eval_report_convertToJSON(dataset_eval_report_1);
	printf("dataset_eval_report :\n%s\n", cJSON_Print(jsondataset_eval_report_1));
	dataset_eval_report_t* dataset_eval_report_2 = dataset_eval_report_parseFromJSON(jsondataset_eval_report_1);
	cJSON* jsondataset_eval_report_2 = dataset_eval_report_convertToJSON(dataset_eval_report_2);
	printf("repeating dataset_eval_report:\n%s\n", cJSON_Print(jsondataset_eval_report_2));
}

int main() {
  test_dataset_eval_report(1);
  test_dataset_eval_report(0);

  printf("Hello world \n");
  return 0;
}

#endif // dataset_eval_report_MAIN
#endif // dataset_eval_report_TEST
