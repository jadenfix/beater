#ifndef dead_letter_replay_report_TEST
#define dead_letter_replay_report_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define dead_letter_replay_report_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/dead_letter_replay_report.h"
dead_letter_replay_report_t* instantiate_dead_letter_replay_report(int include_optional);

#include "test_publish_ack.c"


dead_letter_replay_report_t* instantiate_dead_letter_replay_report(int include_optional) {
  dead_letter_replay_report_t* dead_letter_replay_report = NULL;
  if (include_optional) {
    dead_letter_replay_report = dead_letter_replay_report_create(
       // false, not to have infinite recursion
      instantiate_publish_ack(0),
      "0",
      "0",
      1,
      "0"
    );
  } else {
    dead_letter_replay_report = dead_letter_replay_report_create(
      NULL,
      "0",
      "0",
      1,
      "0"
    );
  }

  return dead_letter_replay_report;
}


#ifdef dead_letter_replay_report_MAIN

void test_dead_letter_replay_report(int include_optional) {
    dead_letter_replay_report_t* dead_letter_replay_report_1 = instantiate_dead_letter_replay_report(include_optional);

	cJSON* jsondead_letter_replay_report_1 = dead_letter_replay_report_convertToJSON(dead_letter_replay_report_1);
	printf("dead_letter_replay_report :\n%s\n", cJSON_Print(jsondead_letter_replay_report_1));
	dead_letter_replay_report_t* dead_letter_replay_report_2 = dead_letter_replay_report_parseFromJSON(jsondead_letter_replay_report_1);
	cJSON* jsondead_letter_replay_report_2 = dead_letter_replay_report_convertToJSON(dead_letter_replay_report_2);
	printf("repeating dead_letter_replay_report:\n%s\n", cJSON_Print(jsondead_letter_replay_report_2));
}

int main() {
  test_dead_letter_replay_report(1);
  test_dead_letter_replay_report(0);

  printf("Hello world \n");
  return 0;
}

#endif // dead_letter_replay_report_MAIN
#endif // dead_letter_replay_report_TEST
