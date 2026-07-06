/*
 * split.h
 *
 * Which split of the optimization substrate a [&#x60;CaseScore&#x60;] belongs to.  The RSI optimizer searches candidates against &#x60;Train&#x60;/&#x60;Val&#x60; and decides acceptance only on the held-out &#x60;Test&#x60; split (§21.4). The split assignment is the *caller&#39;s* responsibility — it owns the dataset and its train/val/test partition — so [&#x60;run_optimization_round&#x60;] never reshuffles or peeks at the split substrate; it merely routes each [&#x60;CaseScore&#x60;] to the gate by its tag.
 */

#ifndef _split_H_
#define _split_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct split_t split_t;


// Enum  for split

typedef enum { beater_api_split__NULL = 0, beater_api_split__train, beater_api_split__val, beater_api_split__test } beater_api_split__e;

char* split_split_ToString(beater_api_split__e split);

beater_api_split__e split_split_FromString(char* split);

cJSON *split_convertToJSON(beater_api_split__e split);

beater_api_split__e split_parseFromJSON(cJSON *splitJSON);

#endif /* _split_H_ */

