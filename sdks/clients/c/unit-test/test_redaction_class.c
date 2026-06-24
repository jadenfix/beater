#ifndef redaction_class_TEST
#define redaction_class_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define redaction_class_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/redaction_class.h"
redaction_class_t* instantiate_redaction_class(int include_optional);



redaction_class_t* instantiate_redaction_class(int include_optional) {
  redaction_class_t* redaction_class = NULL;
  if (include_optional) {
    redaction_class = redaction_class_create(
    );
  } else {
    redaction_class = redaction_class_create(
    );
  }

  return redaction_class;
}


#ifdef redaction_class_MAIN

void test_redaction_class(int include_optional) {
    redaction_class_t* redaction_class_1 = instantiate_redaction_class(include_optional);

	cJSON* jsonredaction_class_1 = redaction_class_convertToJSON(redaction_class_1);
	printf("redaction_class :\n%s\n", cJSON_Print(jsonredaction_class_1));
	redaction_class_t* redaction_class_2 = redaction_class_parseFromJSON(jsonredaction_class_1);
	cJSON* jsonredaction_class_2 = redaction_class_convertToJSON(redaction_class_2);
	printf("repeating redaction_class:\n%s\n", cJSON_Print(jsonredaction_class_2));
}

int main() {
  test_redaction_class(1);
  test_redaction_class(0);

  printf("Hello world \n");
  return 0;
}

#endif // redaction_class_MAIN
#endif // redaction_class_TEST
