#ifndef judge_broker_outcome_TEST
#define judge_broker_outcome_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define judge_broker_outcome_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/judge_broker_outcome.h"
judge_broker_outcome_t* instantiate_judge_broker_outcome(int include_optional);

#include "test_judge_audit_record.c"
#include "test_money.c"
#include "test_score_result.c"


judge_broker_outcome_t* instantiate_judge_broker_outcome(int include_optional) {
  judge_broker_outcome_t* judge_broker_outcome = NULL;
  if (include_optional) {
    judge_broker_outcome = judge_broker_outcome_create(
       // false, not to have infinite recursion
      instantiate_judge_audit_record(0),
       // false, not to have infinite recursion
      instantiate_money(0),
       // false, not to have infinite recursion
      instantiate_score_result(0)
    );
  } else {
    judge_broker_outcome = judge_broker_outcome_create(
      NULL,
      NULL,
      NULL
    );
  }

  return judge_broker_outcome;
}


#ifdef judge_broker_outcome_MAIN

void test_judge_broker_outcome(int include_optional) {
    judge_broker_outcome_t* judge_broker_outcome_1 = instantiate_judge_broker_outcome(include_optional);

	cJSON* jsonjudge_broker_outcome_1 = judge_broker_outcome_convertToJSON(judge_broker_outcome_1);
	printf("judge_broker_outcome :\n%s\n", cJSON_Print(jsonjudge_broker_outcome_1));
	judge_broker_outcome_t* judge_broker_outcome_2 = judge_broker_outcome_parseFromJSON(jsonjudge_broker_outcome_1);
	cJSON* jsonjudge_broker_outcome_2 = judge_broker_outcome_convertToJSON(judge_broker_outcome_2);
	printf("repeating judge_broker_outcome:\n%s\n", cJSON_Print(jsonjudge_broker_outcome_2));
}

int main() {
  test_judge_broker_outcome(1);
  test_judge_broker_outcome(0);

  printf("Hello world \n");
  return 0;
}

#endif // judge_broker_outcome_MAIN
#endif // judge_broker_outcome_TEST
