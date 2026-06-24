/*
 * archived_span_row.h
 *
 * 
 */

#ifndef _archived_span_row_H_
#define _archived_span_row_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct archived_span_row_t archived_span_row_t;




typedef struct archived_span_row_t {
    char *attributes_json; // string
    char *cost_amount_micros; // string
    char *cost_currency; // string
    char *end_time; // string
    char *environment_id; // string
    char *input_tokens; // string
    char *input_uri; // string
    char *kind; // string
    char *model_name; // string
    char *model_provider; // string
    char *name; // string
    char *output_tokens; // string
    char *output_uri; // string
    char *parent_span_id; // string
    char *project_id; // string
    char *raw_uri; // string
    char *reasoning_tokens; // string
    long seq; //numeric
    char *span_id; // string
    char *start_time; // string
    char *status; // string
    char *tenant_id; // string
    char *trace_id; // string
    char *unmapped_json; // string

    int _library_owned; // Is the library responsible for freeing this object?
} archived_span_row_t;

__attribute__((deprecated)) archived_span_row_t *archived_span_row_create(
    char *attributes_json,
    char *cost_amount_micros,
    char *cost_currency,
    char *end_time,
    char *environment_id,
    char *input_tokens,
    char *input_uri,
    char *kind,
    char *model_name,
    char *model_provider,
    char *name,
    char *output_tokens,
    char *output_uri,
    char *parent_span_id,
    char *project_id,
    char *raw_uri,
    char *reasoning_tokens,
    long seq,
    char *span_id,
    char *start_time,
    char *status,
    char *tenant_id,
    char *trace_id,
    char *unmapped_json
);

void archived_span_row_free(archived_span_row_t *archived_span_row);

archived_span_row_t *archived_span_row_parseFromJSON(cJSON *archived_span_rowJSON);

cJSON *archived_span_row_convertToJSON(archived_span_row_t *archived_span_row);

#endif /* _archived_span_row_H_ */

