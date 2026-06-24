/*
 * span_io_value_one_of_1.h
 *
 * 
 */

#ifndef _span_io_value_one_of_1_H_
#define _span_io_value_one_of_1_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct span_io_value_one_of_1_t span_io_value_one_of_1_t;

#include "artifact_ref.h"

// Enum KIND for span_io_value_one_of_1

typedef enum  { beater_api_span_io_value_one_of_1_KIND_NULL = 0, beater_api_span_io_value_one_of_1_KIND_artifact } beater_api_span_io_value_one_of_1_KIND_e;

char* span_io_value_one_of_1_kind_ToString(beater_api_span_io_value_one_of_1_KIND_e kind);

beater_api_span_io_value_one_of_1_KIND_e span_io_value_one_of_1_kind_FromString(char* kind);



typedef struct span_io_value_one_of_1_t {
    struct artifact_ref_t *artifact_ref; //model
    beater_api_span_io_value_one_of_1_KIND_e kind; //enum

    int _library_owned; // Is the library responsible for freeing this object?
} span_io_value_one_of_1_t;

__attribute__((deprecated)) span_io_value_one_of_1_t *span_io_value_one_of_1_create(
    artifact_ref_t *artifact_ref,
    beater_api_span_io_value_one_of_1_KIND_e kind
);

void span_io_value_one_of_1_free(span_io_value_one_of_1_t *span_io_value_one_of_1);

span_io_value_one_of_1_t *span_io_value_one_of_1_parseFromJSON(cJSON *span_io_value_one_of_1JSON);

cJSON *span_io_value_one_of_1_convertToJSON(span_io_value_one_of_1_t *span_io_value_one_of_1);

#endif /* _span_io_value_one_of_1_H_ */

