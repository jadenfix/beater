#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluator_spec.h"



static evaluator_spec_t *evaluator_spec_create_internal(
    char *id,
    evaluator_kind_t *kind,
    beater_api_evaluator_lane__e lane
    ) {
    evaluator_spec_t *evaluator_spec_local_var = malloc(sizeof(evaluator_spec_t));
    if (!evaluator_spec_local_var) {
        return NULL;
    }
    evaluator_spec_local_var->id = id;
    evaluator_spec_local_var->kind = kind;
    evaluator_spec_local_var->lane = lane;

    evaluator_spec_local_var->_library_owned = 1;
    return evaluator_spec_local_var;
}

__attribute__((deprecated)) evaluator_spec_t *evaluator_spec_create(
    char *id,
    evaluator_kind_t *kind,
    beater_api_evaluator_lane__e lane
    ) {
    return evaluator_spec_create_internal (
        id,
        kind,
        lane
        );
}

void evaluator_spec_free(evaluator_spec_t *evaluator_spec) {
    if(NULL == evaluator_spec){
        return ;
    }
    if(evaluator_spec->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "evaluator_spec_free");
        return ;
    }
    listEntry_t *listEntry;
    if (evaluator_spec->id) {
        free(evaluator_spec->id);
        evaluator_spec->id = NULL;
    }
    if (evaluator_spec->kind) {
        evaluator_kind_free(evaluator_spec->kind);
        evaluator_spec->kind = NULL;
    }
    free(evaluator_spec);
}

cJSON *evaluator_spec_convertToJSON(evaluator_spec_t *evaluator_spec) {
    cJSON *item = cJSON_CreateObject();

    // evaluator_spec->id
    if (!evaluator_spec->id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "id", evaluator_spec->id) == NULL) {
    goto fail; //String
    }


    // evaluator_spec->kind
    if (!evaluator_spec->kind) {
        goto fail;
    }
    cJSON *kind_local_JSON = evaluator_kind_convertToJSON(evaluator_spec->kind);
    if(kind_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "kind", kind_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // evaluator_spec->lane
    if (beater_api_evaluator_lane__NULL == evaluator_spec->lane) {
        goto fail;
    }
    cJSON *lane_local_JSON = evaluator_lane_convertToJSON(evaluator_spec->lane);
    if(lane_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "lane", lane_local_JSON);
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

evaluator_spec_t *evaluator_spec_parseFromJSON(cJSON *evaluator_specJSON){

    evaluator_spec_t *evaluator_spec_local_var = NULL;

    // define the local variable for evaluator_spec->kind
    evaluator_kind_t *kind_local_nonprim = NULL;

    // define the local variable for evaluator_spec->lane
    beater_api_evaluator_lane__e lane_local_nonprim = 0;

    // evaluator_spec->id
    cJSON *id = cJSON_GetObjectItemCaseSensitive(evaluator_specJSON, "id");
    if (cJSON_IsNull(id)) {
        id = NULL;
    }
    if (!id) {
        goto end;
    }

    
    if(!cJSON_IsString(id))
    {
    goto end; //String
    }

    // evaluator_spec->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(evaluator_specJSON, "kind");
    if (cJSON_IsNull(kind)) {
        kind = NULL;
    }
    if (!kind) {
        goto end;
    }

    
    kind_local_nonprim = evaluator_kind_parseFromJSON(kind); //nonprimitive

    // evaluator_spec->lane
    cJSON *lane = cJSON_GetObjectItemCaseSensitive(evaluator_specJSON, "lane");
    if (cJSON_IsNull(lane)) {
        lane = NULL;
    }
    if (!lane) {
        goto end;
    }

    
    lane_local_nonprim = evaluator_lane_parseFromJSON(lane); //custom


    evaluator_spec_local_var = evaluator_spec_create_internal (
        strdup(id->valuestring),
        kind_local_nonprim,
        lane_local_nonprim
        );

    return evaluator_spec_local_var;
end:
    if (kind_local_nonprim) {
        evaluator_kind_free(kind_local_nonprim);
        kind_local_nonprim = NULL;
    }
    if (lane_local_nonprim) {
        lane_local_nonprim = 0;
    }
    return NULL;

}
