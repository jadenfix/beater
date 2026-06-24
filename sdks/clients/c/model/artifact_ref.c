#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "artifact_ref.h"



static artifact_ref_t *artifact_ref_create_internal(
    char *artifact_id,
    char *mime_type,
    beater_api_redaction_class__e redaction_class,
    char *sha256,
    long size_bytes,
    char *uri
    ) {
    artifact_ref_t *artifact_ref_local_var = malloc(sizeof(artifact_ref_t));
    if (!artifact_ref_local_var) {
        return NULL;
    }
    artifact_ref_local_var->artifact_id = artifact_id;
    artifact_ref_local_var->mime_type = mime_type;
    artifact_ref_local_var->redaction_class = redaction_class;
    artifact_ref_local_var->sha256 = sha256;
    artifact_ref_local_var->size_bytes = size_bytes;
    artifact_ref_local_var->uri = uri;

    artifact_ref_local_var->_library_owned = 1;
    return artifact_ref_local_var;
}

__attribute__((deprecated)) artifact_ref_t *artifact_ref_create(
    char *artifact_id,
    char *mime_type,
    beater_api_redaction_class__e redaction_class,
    char *sha256,
    long size_bytes,
    char *uri
    ) {
    return artifact_ref_create_internal (
        artifact_id,
        mime_type,
        redaction_class,
        sha256,
        size_bytes,
        uri
        );
}

void artifact_ref_free(artifact_ref_t *artifact_ref) {
    if(NULL == artifact_ref){
        return ;
    }
    if(artifact_ref->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "artifact_ref_free");
        return ;
    }
    listEntry_t *listEntry;
    if (artifact_ref->artifact_id) {
        free(artifact_ref->artifact_id);
        artifact_ref->artifact_id = NULL;
    }
    if (artifact_ref->mime_type) {
        free(artifact_ref->mime_type);
        artifact_ref->mime_type = NULL;
    }
    if (artifact_ref->sha256) {
        free(artifact_ref->sha256);
        artifact_ref->sha256 = NULL;
    }
    if (artifact_ref->uri) {
        free(artifact_ref->uri);
        artifact_ref->uri = NULL;
    }
    free(artifact_ref);
}

cJSON *artifact_ref_convertToJSON(artifact_ref_t *artifact_ref) {
    cJSON *item = cJSON_CreateObject();

    // artifact_ref->artifact_id
    if (!artifact_ref->artifact_id) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "artifact_id", artifact_ref->artifact_id) == NULL) {
    goto fail; //String
    }


    // artifact_ref->mime_type
    if (!artifact_ref->mime_type) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "mime_type", artifact_ref->mime_type) == NULL) {
    goto fail; //String
    }


    // artifact_ref->redaction_class
    if (beater_api_redaction_class__NULL == artifact_ref->redaction_class) {
        goto fail;
    }
    cJSON *redaction_class_local_JSON = redaction_class_convertToJSON(artifact_ref->redaction_class);
    if(redaction_class_local_JSON == NULL) {
        goto fail; // custom
    }
    cJSON_AddItemToObject(item, "redaction_class", redaction_class_local_JSON);
    if(item->child == NULL) {
        goto fail;
    }


    // artifact_ref->sha256
    if (!artifact_ref->sha256) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "sha256", artifact_ref->sha256) == NULL) {
    goto fail; //String
    }


    // artifact_ref->size_bytes
    if (!artifact_ref->size_bytes) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "size_bytes", artifact_ref->size_bytes) == NULL) {
    goto fail; //Numeric
    }


    // artifact_ref->uri
    if (!artifact_ref->uri) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "uri", artifact_ref->uri) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

artifact_ref_t *artifact_ref_parseFromJSON(cJSON *artifact_refJSON){

    artifact_ref_t *artifact_ref_local_var = NULL;

    // define the local variable for artifact_ref->redaction_class
    beater_api_redaction_class__e redaction_class_local_nonprim = 0;

    // artifact_ref->artifact_id
    cJSON *artifact_id = cJSON_GetObjectItemCaseSensitive(artifact_refJSON, "artifact_id");
    if (cJSON_IsNull(artifact_id)) {
        artifact_id = NULL;
    }
    if (!artifact_id) {
        goto end;
    }

    
    if(!cJSON_IsString(artifact_id))
    {
    goto end; //String
    }

    // artifact_ref->mime_type
    cJSON *mime_type = cJSON_GetObjectItemCaseSensitive(artifact_refJSON, "mime_type");
    if (cJSON_IsNull(mime_type)) {
        mime_type = NULL;
    }
    if (!mime_type) {
        goto end;
    }

    
    if(!cJSON_IsString(mime_type))
    {
    goto end; //String
    }

    // artifact_ref->redaction_class
    cJSON *redaction_class = cJSON_GetObjectItemCaseSensitive(artifact_refJSON, "redaction_class");
    if (cJSON_IsNull(redaction_class)) {
        redaction_class = NULL;
    }
    if (!redaction_class) {
        goto end;
    }

    
    redaction_class_local_nonprim = redaction_class_parseFromJSON(redaction_class); //custom

    // artifact_ref->sha256
    cJSON *sha256 = cJSON_GetObjectItemCaseSensitive(artifact_refJSON, "sha256");
    if (cJSON_IsNull(sha256)) {
        sha256 = NULL;
    }
    if (!sha256) {
        goto end;
    }

    
    if(!cJSON_IsString(sha256))
    {
    goto end; //String
    }

    // artifact_ref->size_bytes
    cJSON *size_bytes = cJSON_GetObjectItemCaseSensitive(artifact_refJSON, "size_bytes");
    if (cJSON_IsNull(size_bytes)) {
        size_bytes = NULL;
    }
    if (!size_bytes) {
        goto end;
    }

    
    if(!cJSON_IsNumber(size_bytes))
    {
    goto end; //Numeric
    }

    // artifact_ref->uri
    cJSON *uri = cJSON_GetObjectItemCaseSensitive(artifact_refJSON, "uri");
    if (cJSON_IsNull(uri)) {
        uri = NULL;
    }
    if (!uri) {
        goto end;
    }

    
    if(!cJSON_IsString(uri))
    {
    goto end; //String
    }


    artifact_ref_local_var = artifact_ref_create_internal (
        strdup(artifact_id->valuestring),
        strdup(mime_type->valuestring),
        redaction_class_local_nonprim,
        strdup(sha256->valuestring),
        size_bytes->valuedouble,
        strdup(uri->valuestring)
        );

    return artifact_ref_local_var;
end:
    if (redaction_class_local_nonprim) {
        redaction_class_local_nonprim = 0;
    }
    return NULL;

}
