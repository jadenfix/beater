#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "money.h"



static money_t *money_create_internal(
    long amount_micros,
    beater_api_currency__e currency
    ) {
    money_t *money_local_var = malloc(sizeof(money_t));
    if (!money_local_var) {
        return NULL;
    }
    money_local_var->amount_micros = amount_micros;
    money_local_var->currency = currency;

    money_local_var->_library_owned = 1;
    return money_local_var;
}

__attribute__((deprecated)) money_t *money_create(
    long amount_micros,
    beater_api_currency__e currency
    ) {
    return money_create_internal (
        amount_micros,
        currency
        );
}

void money_free(money_t *money) {
    if(NULL == money){
        return ;
    }
    if(money->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "money_free");
        return ;
    }
    listEntry_t *listEntry;
    free(money);
}

cJSON *money_convertToJSON(money_t *money) {
    cJSON *item = cJSON_CreateObject();

    // money->amount_micros
    if (!money->amount_micros) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "amount_micros", money->amount_micros) == NULL) {
    goto fail; //Numeric
    }


    // money->currency
    if (beater_api_currency__NULL == money->currency) {
        goto fail;
    }
    cJSON *currency_local_JSON = currency_convertToJSON(money->currency);
    if(currency_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "currency", currency_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

money_t *money_parseFromJSON(cJSON *moneyJSON){

    money_t *money_local_var = NULL;

    // define the local variable for money->currency
    beater_api_currency__e currency_local_nonprim = 0;

    // money->amount_micros
    cJSON *amount_micros = cJSON_GetObjectItemCaseSensitive(moneyJSON, "amount_micros");
    if (cJSON_IsNull(amount_micros)) {
        amount_micros = NULL;
    }
    if (!amount_micros) {
        goto end;
    }

    
    if(!cJSON_IsNumber(amount_micros))
    {
    goto end; //Numeric
    }

    // money->currency
    cJSON *currency = cJSON_GetObjectItemCaseSensitive(moneyJSON, "currency");
    if (cJSON_IsNull(currency)) {
        currency = NULL;
    }
    if (!currency) {
        goto end;
    }

    
    currency_local_nonprim = currency_parseFromJSON(currency); //custom


    money_local_var = money_create_internal (
        amount_micros->valuedouble,
        currency_local_nonprim
        );

    return money_local_var;
end:
    if (currency_local_nonprim) {
        currency_local_nonprim = 0;
    }
    return NULL;

}
