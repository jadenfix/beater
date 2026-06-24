#ifndef write_ack_TEST
#define write_ack_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define write_ack_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/write_ack.h"
write_ack_t* instantiate_write_ack(int include_optional);



write_ack_t* instantiate_write_ack(int include_optional) {
  write_ack_t* write_ack = NULL;
  if (include_optional) {
    write_ack = write_ack_create(
      0,
      0,
      0,
      0
    );
  } else {
    write_ack = write_ack_create(
      0,
      0,
      0,
      0
    );
  }

  return write_ack;
}


#ifdef write_ack_MAIN

void test_write_ack(int include_optional) {
    write_ack_t* write_ack_1 = instantiate_write_ack(include_optional);

	cJSON* jsonwrite_ack_1 = write_ack_convertToJSON(write_ack_1);
	printf("write_ack :\n%s\n", cJSON_Print(jsonwrite_ack_1));
	write_ack_t* write_ack_2 = write_ack_parseFromJSON(jsonwrite_ack_1);
	cJSON* jsonwrite_ack_2 = write_ack_convertToJSON(write_ack_2);
	printf("repeating write_ack:\n%s\n", cJSON_Print(jsonwrite_ack_2));
}

int main() {
  test_write_ack(1);
  test_write_ack(0);

  printf("Hello world \n");
  return 0;
}

#endif // write_ack_MAIN
#endif // write_ack_TEST
