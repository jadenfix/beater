/*
 * redaction_class.h
 *
 * 
 */

#ifndef _redaction_class_H_
#define _redaction_class_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct redaction_class_t redaction_class_t;


// Enum  for redaction_class

typedef enum { beater_api_redaction_class__NULL = 0, beater_api_redaction_class___public, beater_api_redaction_class__internal, beater_api_redaction_class__sensitive, beater_api_redaction_class__secret } beater_api_redaction_class__e;

char* redaction_class_redaction_class_ToString(beater_api_redaction_class__e redaction_class);

beater_api_redaction_class__e redaction_class_redaction_class_FromString(char* redaction_class);

cJSON *redaction_class_convertToJSON(beater_api_redaction_class__e redaction_class);

beater_api_redaction_class__e redaction_class_parseFromJSON(cJSON *redaction_classJSON);

#endif /* _redaction_class_H_ */

