/*
 * span_io_value.h
 *
 * 
 */

#ifndef _span_io_value_H_
#define _span_io_value_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct span_io_value_t span_io_value_t;

#include "any_type.h"
#include "artifact_ref.h"
#include "span_io_value_one_of.h"
#include "span_io_value_one_of_1.h"
#include "span_io_value_one_of_2.h"
#include "span_io_value_one_of_3.h"

// Enum KIND for span_io_value

typedef enum  { beater_api_span_io_value_KIND_NULL = 0, beater_api_span_io_value_KIND_missing } beater_api_span_io_value_KIND_e;

char* span_io_value_kind_ToString(beater_api_span_io_value_KIND_e kind);

beater_api_span_io_value_KIND_e span_io_value_kind_FromString(char* kind);



typedef struct span_io_value_t {
    beater_api_span_io_value_KIND_e kind; //enum
    any_type_t *value; // custom
    struct artifact_ref_t *artifact_ref; //model
    char *reason; // string

    int _library_owned; // Is the library responsible for freeing this object?
} span_io_value_t;

__attribute__((deprecated)) span_io_value_t *span_io_value_create(
    beater_api_span_io_value_KIND_e kind,
    any_type_t *value,
    artifact_ref_t *artifact_ref,
    char *reason
);

void span_io_value_free(span_io_value_t *span_io_value);

span_io_value_t *span_io_value_parseFromJSON(cJSON *span_io_valueJSON);

cJSON *span_io_value_convertToJSON(span_io_value_t *span_io_value);

#endif /* _span_io_value_H_ */

