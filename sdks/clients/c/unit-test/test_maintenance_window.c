#ifndef maintenance_window_TEST
#define maintenance_window_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define maintenance_window_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/maintenance_window.h"
maintenance_window_t* instantiate_maintenance_window(int include_optional);



maintenance_window_t* instantiate_maintenance_window(int include_optional) {
  maintenance_window_t* maintenance_window = NULL;
  if (include_optional) {
    maintenance_window = maintenance_window_create(
      "2013-10-20T19:20:30+01:00",
      "2013-10-20T19:20:30+01:00"
    );
  } else {
    maintenance_window = maintenance_window_create(
      "2013-10-20T19:20:30+01:00",
      "2013-10-20T19:20:30+01:00"
    );
  }

  return maintenance_window;
}


#ifdef maintenance_window_MAIN

void test_maintenance_window(int include_optional) {
    maintenance_window_t* maintenance_window_1 = instantiate_maintenance_window(include_optional);

	cJSON* jsonmaintenance_window_1 = maintenance_window_convertToJSON(maintenance_window_1);
	printf("maintenance_window :\n%s\n", cJSON_Print(jsonmaintenance_window_1));
	maintenance_window_t* maintenance_window_2 = maintenance_window_parseFromJSON(jsonmaintenance_window_1);
	cJSON* jsonmaintenance_window_2 = maintenance_window_convertToJSON(maintenance_window_2);
	printf("repeating maintenance_window:\n%s\n", cJSON_Print(jsonmaintenance_window_2));
}

int main() {
  test_maintenance_window(1);
  test_maintenance_window(0);

  printf("Hello world \n");
  return 0;
}

#endif // maintenance_window_MAIN
#endif // maintenance_window_TEST
