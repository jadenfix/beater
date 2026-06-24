#ifndef alert_links_TEST
#define alert_links_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define alert_links_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/alert_links.h"
alert_links_t* instantiate_alert_links(int include_optional);



alert_links_t* instantiate_alert_links(int include_optional) {
  alert_links_t* alert_links = NULL;
  if (include_optional) {
    alert_links = alert_links_create(
      "0",
      "0",
      "0",
      "0"
    );
  } else {
    alert_links = alert_links_create(
      "0",
      "0",
      "0",
      "0"
    );
  }

  return alert_links;
}


#ifdef alert_links_MAIN

void test_alert_links(int include_optional) {
    alert_links_t* alert_links_1 = instantiate_alert_links(include_optional);

	cJSON* jsonalert_links_1 = alert_links_convertToJSON(alert_links_1);
	printf("alert_links :\n%s\n", cJSON_Print(jsonalert_links_1));
	alert_links_t* alert_links_2 = alert_links_parseFromJSON(jsonalert_links_1);
	cJSON* jsonalert_links_2 = alert_links_convertToJSON(alert_links_2);
	printf("repeating alert_links:\n%s\n", cJSON_Print(jsonalert_links_2));
}

int main() {
  test_alert_links(1);
  test_alert_links(0);

  printf("Hello world \n");
  return 0;
}

#endif // alert_links_MAIN
#endif // alert_links_TEST
