/*
 * span_io_value_one_of_3.h
 *
 * 
 */

#ifndef _span_io_value_one_of_3_H_
#define _span_io_value_one_of_3_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct span_io_value_one_of_3_t span_io_value_one_of_3_t;


// Enum KIND for span_io_value_one_of_3

typedef enum  { beater_api_span_io_value_one_of_3_KIND_NULL = 0, beater_api_span_io_value_one_of_3_KIND_missing } beater_api_span_io_value_one_of_3_KIND_e;

char* span_io_value_one_of_3_kind_ToString(beater_api_span_io_value_one_of_3_KIND_e kind);

beater_api_span_io_value_one_of_3_KIND_e span_io_value_one_of_3_kind_FromString(char* kind);



typedef struct span_io_value_one_of_3_t {
    beater_api_span_io_value_one_of_3_KIND_e kind; //enum

    int _library_owned; // Is the library responsible for freeing this object?
} span_io_value_one_of_3_t;

__attribute__((deprecated)) span_io_value_one_of_3_t *span_io_value_one_of_3_create(
    beater_api_span_io_value_one_of_3_KIND_e kind
);

void span_io_value_one_of_3_free(span_io_value_one_of_3_t *span_io_value_one_of_3);

span_io_value_one_of_3_t *span_io_value_one_of_3_parseFromJSON(cJSON *span_io_value_one_of_3JSON);

cJSON *span_io_value_one_of_3_convertToJSON(span_io_value_one_of_3_t *span_io_value_one_of_3);

#endif /* _span_io_value_one_of_3_H_ */

