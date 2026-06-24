#ifndef publish_ack_TEST
#define publish_ack_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define publish_ack_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/publish_ack.h"
publish_ack_t* instantiate_publish_ack(int include_optional);



publish_ack_t* instantiate_publish_ack(int include_optional) {
  publish_ack_t* publish_ack = NULL;
  if (include_optional) {
    publish_ack = publish_ack_create(
      1,
      1
    );
  } else {
    publish_ack = publish_ack_create(
      1,
      1
    );
  }

  return publish_ack;
}


#ifdef publish_ack_MAIN

void test_publish_ack(int include_optional) {
    publish_ack_t* publish_ack_1 = instantiate_publish_ack(include_optional);

	cJSON* jsonpublish_ack_1 = publish_ack_convertToJSON(publish_ack_1);
	printf("publish_ack :\n%s\n", cJSON_Print(jsonpublish_ack_1));
	publish_ack_t* publish_ack_2 = publish_ack_parseFromJSON(jsonpublish_ack_1);
	cJSON* jsonpublish_ack_2 = publish_ack_convertToJSON(publish_ack_2);
	printf("repeating publish_ack:\n%s\n", cJSON_Print(jsonpublish_ack_2));
}

int main() {
  test_publish_ack(1);
  test_publish_ack(0);

  printf("Hello world \n");
  return 0;
}

#endif // publish_ack_MAIN
#endif // publish_ack_TEST
