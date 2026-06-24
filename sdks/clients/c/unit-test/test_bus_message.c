#ifndef bus_message_TEST
#define bus_message_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define bus_message_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/bus_message.h"
bus_message_t* instantiate_bus_message(int include_optional);



bus_message_t* instantiate_bus_message(int include_optional) {
  bus_message_t* bus_message = NULL;
  if (include_optional) {
    bus_message = bus_message_create(
      0,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      0,
      "0",
      list_createList(),
      "0",
      "0"
    );
  } else {
    bus_message = bus_message_create(
      0,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      0,
      "0",
      list_createList(),
      "0",
      "0"
    );
  }

  return bus_message;
}


#ifdef bus_message_MAIN

void test_bus_message(int include_optional) {
    bus_message_t* bus_message_1 = instantiate_bus_message(include_optional);

	cJSON* jsonbus_message_1 = bus_message_convertToJSON(bus_message_1);
	printf("bus_message :\n%s\n", cJSON_Print(jsonbus_message_1));
	bus_message_t* bus_message_2 = bus_message_parseFromJSON(jsonbus_message_1);
	cJSON* jsonbus_message_2 = bus_message_convertToJSON(bus_message_2);
	printf("repeating bus_message:\n%s\n", cJSON_Print(jsonbus_message_2));
}

int main() {
  test_bus_message(1);
  test_bus_message(0);

  printf("Hello world \n");
  return 0;
}

#endif // bus_message_MAIN
#endif // bus_message_TEST
