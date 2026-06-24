/*
 * statistical_test.h
 *
 * 
 */

#ifndef _statistical_test_H_
#define _statistical_test_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct statistical_test_t statistical_test_t;


// Enum  for statistical_test

typedef enum { beater_api_statistical_test__NULL = 0, beater_api_statistical_test__paired_normal_approximation } beater_api_statistical_test__e;

char* statistical_test_statistical_test_ToString(beater_api_statistical_test__e statistical_test);

beater_api_statistical_test__e statistical_test_statistical_test_FromString(char* statistical_test);

cJSON *statistical_test_convertToJSON(beater_api_statistical_test__e statistical_test);

beater_api_statistical_test__e statistical_test_parseFromJSON(cJSON *statistical_testJSON);

#endif /* _statistical_test_H_ */

