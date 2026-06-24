#ifndef create_dataset_request_TEST
#define create_dataset_request_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define create_dataset_request_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/create_dataset_request.h"
create_dataset_request_t* instantiate_create_dataset_request(int include_optional);



create_dataset_request_t* instantiate_create_dataset_request(int include_optional) {
  create_dataset_request_t* create_dataset_request = NULL;
  if (include_optional) {
    create_dataset_request = create_dataset_request_create(
      "0"
    );
  } else {
    create_dataset_request = create_dataset_request_create(
      "0"
    );
  }

  return create_dataset_request;
}


#ifdef create_dataset_request_MAIN

void test_create_dataset_request(int include_optional) {
    create_dataset_request_t* create_dataset_request_1 = instantiate_create_dataset_request(include_optional);

	cJSON* jsoncreate_dataset_request_1 = create_dataset_request_convertToJSON(create_dataset_request_1);
	printf("create_dataset_request :\n%s\n", cJSON_Print(jsoncreate_dataset_request_1));
	create_dataset_request_t* create_dataset_request_2 = create_dataset_request_parseFromJSON(jsoncreate_dataset_request_1);
	cJSON* jsoncreate_dataset_request_2 = create_dataset_request_convertToJSON(create_dataset_request_2);
	printf("repeating create_dataset_request:\n%s\n", cJSON_Print(jsoncreate_dataset_request_2));
}

int main() {
  test_create_dataset_request(1);
  test_create_dataset_request(0);

  printf("Hello world \n");
  return 0;
}

#endif // create_dataset_request_MAIN
#endif // create_dataset_request_TEST
