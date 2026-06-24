#ifndef webhook_delivery_TEST
#define webhook_delivery_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define webhook_delivery_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/webhook_delivery.h"
webhook_delivery_t* instantiate_webhook_delivery(int include_optional);



webhook_delivery_t* instantiate_webhook_delivery(int include_optional) {
  webhook_delivery_t* webhook_delivery = NULL;
  if (include_optional) {
    webhook_delivery = webhook_delivery_create(
      null,
      "0",
      list_createList()
    );
  } else {
    webhook_delivery = webhook_delivery_create(
      null,
      "0",
      list_createList()
    );
  }

  return webhook_delivery;
}


#ifdef webhook_delivery_MAIN

void test_webhook_delivery(int include_optional) {
    webhook_delivery_t* webhook_delivery_1 = instantiate_webhook_delivery(include_optional);

	cJSON* jsonwebhook_delivery_1 = webhook_delivery_convertToJSON(webhook_delivery_1);
	printf("webhook_delivery :\n%s\n", cJSON_Print(jsonwebhook_delivery_1));
	webhook_delivery_t* webhook_delivery_2 = webhook_delivery_parseFromJSON(jsonwebhook_delivery_1);
	cJSON* jsonwebhook_delivery_2 = webhook_delivery_convertToJSON(webhook_delivery_2);
	printf("repeating webhook_delivery:\n%s\n", cJSON_Print(jsonwebhook_delivery_2));
}

int main() {
  test_webhook_delivery(1);
  test_webhook_delivery(0);

  printf("Hello world \n");
  return 0;
}

#endif // webhook_delivery_MAIN
#endif // webhook_delivery_TEST
