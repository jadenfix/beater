#ifndef model_ref_TEST
#define model_ref_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define model_ref_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/model_ref.h"
model_ref_t* instantiate_model_ref(int include_optional);



model_ref_t* instantiate_model_ref(int include_optional) {
  model_ref_t* model_ref = NULL;
  if (include_optional) {
    model_ref = model_ref_create(
      "0",
      "0"
    );
  } else {
    model_ref = model_ref_create(
      "0",
      "0"
    );
  }

  return model_ref;
}


#ifdef model_ref_MAIN

void test_model_ref(int include_optional) {
    model_ref_t* model_ref_1 = instantiate_model_ref(include_optional);

	cJSON* jsonmodel_ref_1 = model_ref_convertToJSON(model_ref_1);
	printf("model_ref :\n%s\n", cJSON_Print(jsonmodel_ref_1));
	model_ref_t* model_ref_2 = model_ref_parseFromJSON(jsonmodel_ref_1);
	cJSON* jsonmodel_ref_2 = model_ref_convertToJSON(model_ref_2);
	printf("repeating model_ref:\n%s\n", cJSON_Print(jsonmodel_ref_2));
}

int main() {
  test_model_ref(1);
  test_model_ref(0);

  printf("Hello world \n");
  return 0;
}

#endif // model_ref_MAIN
#endif // model_ref_TEST
