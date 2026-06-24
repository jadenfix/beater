#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dead_letter_replay_report.h"



static dead_letter_replay_report_t *dead_letter_replay_report_create_internal(
    publish_ack_t *ack,
    char *message_id,
    char *project_id,
    int reset_attempts,
    char *tenant_id
    ) {
    dead_letter_replay_report_t *dead_letter_replay_report_local_var = malloc(sizeof(dead_letter_replay_report_t));
    if (!dead_letter_replay_report_local_var) {
        return NULL;
    }
    dead_letter_replay_report_local_var->ack = ack;
    dead_letter_replay_report_local_var->message_id = message_id;
    dead_letter_replay_report_local_var->project_id = project_id;
    dead_letter_replay_report_local_var->reset_attempts = reset_attempts;
    dead_letter_replay_report_local_var->tenant_id = tenant_id;

    dead_letter_replay_report_local_var->_library_owned = 1;
    return dead_letter_replay_report_local_var;
}

__attribute__((deprecated)) dead_letter_replay_report_t *dead_letter_replay_report_create(
    publish_ack_t *ack,
    char *message_id,
    char *project_id,
    int reset_attempts,
    char *tenant_id
    ) {
    return dead_letter_replay_report_create_internal (
        ack,
        message_id,
        project_id,
        reset_attempts,
        tenant_id
        );
}

void dead_letter_replay_report_free(dead_letter_replay_report_t *dead_letter_replay_report) {
    if(NULL == dead_letter_replay_report){
        return ;
    }
    if(dead_letter_replay_report->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "dead_letter_replay_report_free");
        return ;
    }
    listEntry_t *listEntry;
    if (dead_letter_replay_report->ack) {
        publish_ack_free(dead_letter_replay_report->ack);
        dead_letter_replay_report->ack = NULL;
    }
    if (dead_letter_replay_report->message_id) {
        free(dead_letter_replay_report->message_id);
        dead_letter_replay_report->message_id = NULL;
    }
    if (dead_letter_replay_report->project_id) {
        free(dead_letter_replay_report->project_id);
        dead_letter_replay_report->project_id = NULL;
    }
    if (dead_letter_replay_report->tenant_id) {
        free(dead_letter_replay_report->tenant_id);
        dead_letter_replay_report->tenant_id = NULL;
    }
    free(dead_letter_replay_report);
}

cJSON *dead_letter_replay_report_convertToJSON(dead_letter_replay_report_t *dead_letter_replay_report) {
    cJSON *item = cJSON_CreateObject();

    // dead_letter_replay_report->ack
    if (!dead_letter_replay_report->ack) {
        goto fail;
    }
    cJSON *ack_local_JSON = publish_ack_convertToJSON(dead_letter_replay_report->ack);
    if(ack_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "ack", ack_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // dead_letter_replay_report->message_id
    if (!dead_letter_replay_report->message_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "message_id", dead_letter_replay_report->message_id) == NULL) {
    goto fail; //String
    }


    // dead_letter_replay_report->project_id
    if (!dead_letter_replay_report->project_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "project_id", dead_letter_replay_report->project_id) == NULL) {
    goto fail; //String
    }


    // dead_letter_replay_report->reset_attempts
    if (!dead_letter_replay_report->reset_attempts) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "reset_attempts", dead_letter_replay_report->reset_attempts) == NULL) {
    goto fail; //Bool
    }


    // dead_letter_replay_report->tenant_id
    if (!dead_letter_replay_report->tenant_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "tenant_id", dead_letter_replay_report->tenant_id) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

dead_letter_replay_report_t *dead_letter_replay_report_parseFromJSON(cJSON *dead_letter_replay_reportJSON){

    dead_letter_replay_report_t *dead_letter_replay_report_local_var = NULL;

    // define the local variable for dead_letter_replay_report->ack
    publish_ack_t *ack_local_nonprim = NULL;

    // dead_letter_replay_report->ack
    cJSON *ack = cJSON_GetObjectItemCaseSensitive(dead_letter_replay_reportJSON, "ack");
    if (cJSON_IsNull(ack)) {
        ack = NULL;
    }
    if (!ack) {
        goto end;
    }

    
    ack_local_nonprim = publish_ack_parseFromJSON(ack); //nonprimitive

    // dead_letter_replay_report->message_id
    cJSON *message_id = cJSON_GetObjectItemCaseSensitive(dead_letter_replay_reportJSON, "message_id");
    if (cJSON_IsNull(message_id)) {
        message_id = NULL;
    }
    if (!message_id) {
        goto end;
    }

    
    if(!cJSON_IsString(message_id))
    {
    goto end; //String
    }

    // dead_letter_replay_report->project_id
    cJSON *project_id = cJSON_GetObjectItemCaseSensitive(dead_letter_replay_reportJSON, "project_id");
    if (cJSON_IsNull(project_id)) {
        project_id = NULL;
    }
    if (!project_id) {
        goto end;
    }

    
    if(!cJSON_IsString(project_id))
    {
    goto end; //String
    }

    // dead_letter_replay_report->reset_attempts
    cJSON *reset_attempts = cJSON_GetObjectItemCaseSensitive(dead_letter_replay_reportJSON, "reset_attempts");
    if (cJSON_IsNull(reset_attempts)) {
        reset_attempts = NULL;
    }
    if (!reset_attempts) {
        goto end;
    }

    
    if(!cJSON_IsBool(reset_attempts))
    {
    goto end; //Bool
    }

    // dead_letter_replay_report->tenant_id
    cJSON *tenant_id = cJSON_GetObjectItemCaseSensitive(dead_letter_replay_reportJSON, "tenant_id");
    if (cJSON_IsNull(tenant_id)) {
        tenant_id = NULL;
    }
    if (!tenant_id) {
        goto end;
    }

    
    if(!cJSON_IsString(tenant_id))
    {
    goto end; //String
    }


    dead_letter_replay_report_local_var = dead_letter_replay_report_create_internal (
        ack_local_nonprim,
        strdup(message_id->valuestring),
        strdup(project_id->valuestring),
        reset_attempts->valueint,
        strdup(tenant_id->valuestring)
        );

    return dead_letter_replay_report_local_var;
end:
    if (ack_local_nonprim) {
        publish_ack_free(ack_local_nonprim);
        ack_local_nonprim = NULL;
    }
    return NULL;

}
