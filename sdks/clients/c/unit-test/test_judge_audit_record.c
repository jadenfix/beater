#ifndef judge_audit_record_TEST
#define judge_audit_record_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define judge_audit_record_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/judge_audit_record.h"
judge_audit_record_t* instantiate_judge_audit_record(int include_optional);

#include "test_money.c"
#include "test_money.c"


judge_audit_record_t* instantiate_judge_audit_record(int include_optional) {
  judge_audit_record_t* judge_audit_record = NULL;
  if (include_optional) {
    judge_audit_record = judge_audit_record_create(
      1,
       // false, not to have infinite recursion
      instantiate_money(0),
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_money(0),
      "0",
      "0",
      "0",
      1.337,
      "0"
    );
  } else {
    judge_audit_record = judge_audit_record_create(
      1,
      NULL,
      "2013-10-20T19:20:30+01:00",
      "0",
      "0",
      "0",
      "0",
      "0",
      NULL,
      "0",
      "0",
      "0",
      1.337,
      "0"
    );
  }

  return judge_audit_record;
}


#ifdef judge_audit_record_MAIN

void test_judge_audit_record(int include_optional) {
    judge_audit_record_t* judge_audit_record_1 = instantiate_judge_audit_record(include_optional);

	cJSON* jsonjudge_audit_record_1 = judge_audit_record_convertToJSON(judge_audit_record_1);
	printf("judge_audit_record :\n%s\n", cJSON_Print(jsonjudge_audit_record_1));
	judge_audit_record_t* judge_audit_record_2 = judge_audit_record_parseFromJSON(jsonjudge_audit_record_1);
	cJSON* jsonjudge_audit_record_2 = judge_audit_record_convertToJSON(judge_audit_record_2);
	printf("repeating judge_audit_record:\n%s\n", cJSON_Print(jsonjudge_audit_record_2));
}

int main() {
  test_judge_audit_record(1);
  test_judge_audit_record(0);

  printf("Hello world \n");
  return 0;
}

#endif // judge_audit_record_MAIN
#endif // judge_audit_record_TEST
