/*
 * change_kind.h
 *
 * The policy-π (§6.1) lever a [&#x60;CandidateChange&#x60;] targets, mirroring the planned §21.1 &#x60;ChangeKind&#x60; taxonomy. Kept internal to this crate; intentionally not a &#x60;/v1&#x60; contract type.
 */

#ifndef _change_kind_H_
#define _change_kind_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct change_kind_t change_kind_t;


// Enum  for change_kind

typedef enum { beater_api_change_kind__NULL = 0, beater_api_change_kind__system_prompt, beater_api_change_kind__customer_prompt, beater_api_change_kind__code, beater_api_change_kind__tool_add, beater_api_change_kind__tool_remove, beater_api_change_kind__memory_config, beater_api_change_kind__model_params, beater_api_change_kind__data_label } beater_api_change_kind__e;

char* change_kind_change_kind_ToString(beater_api_change_kind__e change_kind);

beater_api_change_kind__e change_kind_change_kind_FromString(char* change_kind);

cJSON *change_kind_convertToJSON(beater_api_change_kind__e change_kind);

beater_api_change_kind__e change_kind_parseFromJSON(cJSON *change_kindJSON);

#endif /* _change_kind_H_ */

