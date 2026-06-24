/*
 * span_io_value_one_of.h
 *
 * 
 */

#ifndef _span_io_value_one_of_H_
#define _span_io_value_one_of_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct span_io_value_one_of_t span_io_value_one_of_t;

#include "any_type.h"

// Enum KIND for span_io_value_one_of

typedef enum  { beater_api_span_io_value_one_of_KIND_NULL = 0, beater_api_span_io_value_one_of_KIND__inline } beater_api_span_io_value_one_of_KIND_e;

char* span_io_value_one_of_kind_ToString(beater_api_span_io_value_one_of_KIND_e kind);

beater_api_span_io_value_one_of_KIND_e span_io_value_one_of_kind_FromString(char* kind);



typedef struct span_io_value_one_of_t {
    beater_api_span_io_value_one_of_KIND_e kind; //enum
    any_type_t *value; // custom

    int _library_owned; // Is the library responsible for freeing this object?
} span_io_value_one_of_t;

__attribute__((deprecated)) span_io_value_one_of_t *span_io_value_one_of_create(
    beater_api_span_io_value_one_of_KIND_e kind,
    any_type_t *value
);

void span_io_value_one_of_free(span_io_value_one_of_t *span_io_value_one_of);

span_io_value_one_of_t *span_io_value_one_of_parseFromJSON(cJSON *span_io_value_one_ofJSON);

cJSON *span_io_value_one_of_convertToJSON(span_io_value_one_of_t *span_io_value_one_of);

#endif /* _span_io_value_one_of_H_ */

