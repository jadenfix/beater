/*
 * review_verdict.h
 *
 * 
 */

#ifndef _review_verdict_H_
#define _review_verdict_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct review_verdict_t review_verdict_t;


// Enum  for review_verdict

typedef enum { beater_api_review_verdict__NULL = 0, beater_api_review_verdict__pass, beater_api_review_verdict__fail, beater_api_review_verdict__needs_fix, beater_api_review_verdict__unsure } beater_api_review_verdict__e;

char* review_verdict_review_verdict_ToString(beater_api_review_verdict__e review_verdict);

beater_api_review_verdict__e review_verdict_review_verdict_FromString(char* review_verdict);

cJSON *review_verdict_convertToJSON(beater_api_review_verdict__e review_verdict);

beater_api_review_verdict__e review_verdict_parseFromJSON(cJSON *review_verdictJSON);

#endif /* _review_verdict_H_ */

