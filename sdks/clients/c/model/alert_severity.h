/*
 * alert_severity.h
 *
 * 
 */

#ifndef _alert_severity_H_
#define _alert_severity_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct alert_severity_t alert_severity_t;


// Enum  for alert_severity

typedef enum { beater_api_alert_severity__NULL = 0, beater_api_alert_severity__info, beater_api_alert_severity__warning, beater_api_alert_severity__critical } beater_api_alert_severity__e;

char* alert_severity_alert_severity_ToString(beater_api_alert_severity__e alert_severity);

beater_api_alert_severity__e alert_severity_alert_severity_FromString(char* alert_severity);

cJSON *alert_severity_convertToJSON(beater_api_alert_severity__e alert_severity);

beater_api_alert_severity__e alert_severity_parseFromJSON(cJSON *alert_severityJSON);

#endif /* _alert_severity_H_ */

