#ifndef money_TEST
#define money_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define money_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/money.h"
money_t* instantiate_money(int include_optional);



money_t* instantiate_money(int include_optional) {
  money_t* money = NULL;
  if (include_optional) {
    money = money_create(
      56,
      beater_api_money__USD
    );
  } else {
    money = money_create(
      56,
      beater_api_money__USD
    );
  }

  return money;
}


#ifdef money_MAIN

void test_money(int include_optional) {
    money_t* money_1 = instantiate_money(include_optional);

	cJSON* jsonmoney_1 = money_convertToJSON(money_1);
	printf("money :\n%s\n", cJSON_Print(jsonmoney_1));
	money_t* money_2 = money_parseFromJSON(jsonmoney_1);
	cJSON* jsonmoney_2 = money_convertToJSON(money_2);
	printf("repeating money:\n%s\n", cJSON_Print(jsonmoney_2));
}

int main() {
  test_money(1);
  test_money(0);

  printf("Hello world \n");
  return 0;
}

#endif // money_MAIN
#endif // money_TEST
