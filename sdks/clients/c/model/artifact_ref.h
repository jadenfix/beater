/*
 * artifact_ref.h
 *
 * 
 */

#ifndef _artifact_ref_H_
#define _artifact_ref_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct artifact_ref_t artifact_ref_t;

#include "redaction_class.h"



typedef struct artifact_ref_t {
    char *artifact_id; // string
    char *mime_type; // string
    beater_api_redaction_class__e redaction_class; //referenced enum
    char *sha256; // string
    long size_bytes; //numeric
    char *uri; // string

    int _library_owned; // Is the library responsible for freeing this object?
} artifact_ref_t;

__attribute__((deprecated)) artifact_ref_t *artifact_ref_create(
    char *artifact_id,
    char *mime_type,
    beater_api_redaction_class__e redaction_class,
    char *sha256,
    long size_bytes,
    char *uri
);

void artifact_ref_free(artifact_ref_t *artifact_ref);

artifact_ref_t *artifact_ref_parseFromJSON(cJSON *artifact_refJSON);

cJSON *artifact_ref_convertToJSON(artifact_ref_t *artifact_ref);

#endif /* _artifact_ref_H_ */

