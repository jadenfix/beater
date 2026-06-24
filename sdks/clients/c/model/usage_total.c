#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "usage_total.h"



static usage_total_t *usage_total_create_internal(
    long quantity,
    char *unit
    ) {
    usage_total_t *usage_total_local_var = malloc(sizeof(usage_total_t));
    if (!usage_total_local_var) {
        return NULL;
    }
    usage_total_local_var->quantity = quantity;
    usage_total_local_var->unit = unit;

    usage_total_local_var->_library_owned = 1;
    return usage_total_local_var;
}

__attribute__((deprecated)) usage_total_t *usage_total_create(
    long quantity,
    char *unit
    ) {
    return usage_total_create_internal (
        quantity,
        unit
        );
}

void usage_total_free(usage_total_t *usage_total) {
    if(NULL == usage_total){
        return ;
    }
    if(usage_total->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "usage_total_free");
        return ;
    }
    listEntry_t *listEntry;
    if (usage_total->unit) {
        free(usage_total->unit);
        usage_total->unit = NULL;
    }
    free(usage_total);
}

cJSON *usage_total_convertToJSON(usage_total_t *usage_total) {
    cJSON *item = cJSON_CreateObject();

    // usage_total->quantity
    if (!usage_total->quantity) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "quantity", usage_total->quantity) == NULL) {
    goto fail; //Numeric
    }


    // usage_total->unit
    if (!usage_total->unit) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "unit", usage_total->unit) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

usage_total_t *usage_total_parseFromJSON(cJSON *usage_totalJSON){

    usage_total_t *usage_total_local_var = NULL;

    // usage_total->quantity
    cJSON *quantity = cJSON_GetObjectItemCaseSensitive(usage_totalJSON, "quantity");
    if (cJSON_IsNull(quantity)) {
        quantity = NULL;
    }
    if (!quantity) {
        goto end;
    }

    
    if(!cJSON_IsNumber(quantity))
    {
    goto end; //Numeric
    }

    // usage_total->unit
    cJSON *unit = cJSON_GetObjectItemCaseSensitive(usage_totalJSON, "unit");
    if (cJSON_IsNull(unit)) {
        unit = NULL;
    }
    if (!unit) {
        goto end;
    }

    
    if(!cJSON_IsString(unit))
    {
    goto end; //String
    }


    usage_total_local_var = usage_total_create_internal (
        quantity->valuedouble,
        strdup(unit->valuestring)
        );

    return usage_total_local_var;
end:
    return NULL;

}
