#ifndef dead_letter_TEST
#define dead_letter_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define dead_letter_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/dead_letter.h"
dead_letter_t* instantiate_dead_letter(int include_optional);

#include "test_bus_message.c"


dead_letter_t* instantiate_dead_letter(int include_optional) {
  dead_letter_t* dead_letter = NULL;
  if (include_optional) {
    dead_letter = dead_letter_create(
      "2013-10-20T19:20:30+01:00",
       // false, not to have infinite recursion
      instantiate_bus_message(0),
      "0"
    );
  } else {
    dead_letter = dead_letter_create(
      "2013-10-20T19:20:30+01:00",
      NULL,
      "0"
    );
  }

  return dead_letter;
}


#ifdef dead_letter_MAIN

void test_dead_letter(int include_optional) {
    dead_letter_t* dead_letter_1 = instantiate_dead_letter(include_optional);

	cJSON* jsondead_letter_1 = dead_letter_convertToJSON(dead_letter_1);
	printf("dead_letter :\n%s\n", cJSON_Print(jsondead_letter_1));
	dead_letter_t* dead_letter_2 = dead_letter_parseFromJSON(jsondead_letter_1);
	cJSON* jsondead_letter_2 = dead_letter_convertToJSON(dead_letter_2);
	printf("repeating dead_letter:\n%s\n", cJSON_Print(jsondead_letter_2));
}

int main() {
  test_dead_letter(1);
  test_dead_letter(0);

  printf("Hello world \n");
  return 0;
}

#endif // dead_letter_MAIN
#endif // dead_letter_TEST
