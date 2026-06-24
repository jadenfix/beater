#ifndef tenant_scope_TEST
#define tenant_scope_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define tenant_scope_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/tenant_scope.h"
tenant_scope_t* instantiate_tenant_scope(int include_optional);



tenant_scope_t* instantiate_tenant_scope(int include_optional) {
  tenant_scope_t* tenant_scope = NULL;
  if (include_optional) {
    tenant_scope = tenant_scope_create(
      "0",
      "0",
      "0"
    );
  } else {
    tenant_scope = tenant_scope_create(
      "0",
      "0",
      "0"
    );
  }

  return tenant_scope;
}


#ifdef tenant_scope_MAIN

void test_tenant_scope(int include_optional) {
    tenant_scope_t* tenant_scope_1 = instantiate_tenant_scope(include_optional);

	cJSON* jsontenant_scope_1 = tenant_scope_convertToJSON(tenant_scope_1);
	printf("tenant_scope :\n%s\n", cJSON_Print(jsontenant_scope_1));
	tenant_scope_t* tenant_scope_2 = tenant_scope_parseFromJSON(jsontenant_scope_1);
	cJSON* jsontenant_scope_2 = tenant_scope_convertToJSON(tenant_scope_2);
	printf("repeating tenant_scope:\n%s\n", cJSON_Print(jsontenant_scope_2));
}

int main() {
  test_tenant_scope(1);
  test_tenant_scope(0);

  printf("Hello world \n");
  return 0;
}

#endif // tenant_scope_MAIN
#endif // tenant_scope_TEST
