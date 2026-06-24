/*
 * money.h
 *
 * 
 */

#ifndef _money_H_
#define _money_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct money_t money_t;

#include "currency.h"



typedef struct money_t {
    long amount_micros; //numeric
    beater_api_currency__e currency; //referenced enum

    int _library_owned; // Is the library responsible for freeing this object?
} money_t;

__attribute__((deprecated)) money_t *money_create(
    long amount_micros,
    beater_api_currency__e currency
);

void money_free(money_t *money);

money_t *money_parseFromJSON(cJSON *moneyJSON);

cJSON *money_convertToJSON(money_t *money);

#endif /* _money_H_ */

