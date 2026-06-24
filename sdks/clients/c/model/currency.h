/*
 * currency.h
 *
 * 
 */

#ifndef _currency_H_
#define _currency_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct currency_t currency_t;


// Enum  for currency

typedef enum { beater_api_currency__NULL = 0, beater_api_currency__USD } beater_api_currency__e;

char* currency_currency_ToString(beater_api_currency__e currency);

beater_api_currency__e currency_currency_FromString(char* currency);

cJSON *currency_convertToJSON(beater_api_currency__e currency);

beater_api_currency__e currency_parseFromJSON(cJSON *currencyJSON);

#endif /* _currency_H_ */

