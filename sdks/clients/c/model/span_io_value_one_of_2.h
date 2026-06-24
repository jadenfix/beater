/*
 * span_io_value_one_of_2.h
 *
 * 
 */

#ifndef _span_io_value_one_of_2_H_
#define _span_io_value_one_of_2_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct span_io_value_one_of_2_t span_io_value_one_of_2_t;


// Enum KIND for span_io_value_one_of_2

typedef enum  { beater_api_span_io_value_one_of_2_KIND_NULL = 0, beater_api_span_io_value_one_of_2_KIND_redacted } beater_api_span_io_value_one_of_2_KIND_e;

char* span_io_value_one_of_2_kind_ToString(beater_api_span_io_value_one_of_2_KIND_e kind);

beater_api_span_io_value_one_of_2_KIND_e span_io_value_one_of_2_kind_FromString(char* kind);



typedef struct span_io_value_one_of_2_t {
    beater_api_span_io_value_one_of_2_KIND_e kind; //enum
    char *reason; // string

    int _library_owned; // Is the library responsible for freeing this object?
} span_io_value_one_of_2_t;

__attribute__((deprecated)) span_io_value_one_of_2_t *span_io_value_one_of_2_create(
    beater_api_span_io_value_one_of_2_KIND_e kind,
    char *reason
);

void span_io_value_one_of_2_free(span_io_value_one_of_2_t *span_io_value_one_of_2);

span_io_value_one_of_2_t *span_io_value_one_of_2_parseFromJSON(cJSON *span_io_value_one_of_2JSON);

cJSON *span_io_value_one_of_2_convertToJSON(span_io_value_one_of_2_t *span_io_value_one_of_2);

#endif /* _span_io_value_one_of_2_H_ */

