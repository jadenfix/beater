/*
 * canonical_span.h
 *
 * 
 */

#ifndef _canonical_span_H_
#define _canonical_span_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct canonical_span_t canonical_span_t;

#include "any_type.h"
#include "artifact_ref.h"
#include "model_ref.h"
#include "money.h"
#include "span_status.h"
#include "token_counts.h"



typedef struct canonical_span_t {
    list_t* attributes; //map
    struct money_t *cost; //model
    char *end_time; //date time
    char *environment_id; // string
    struct artifact_ref_t *input_ref; //model
    char *kind; // string
    struct model_ref_t *model; //model
    char *name; // string
    char *normalizer_version; // string
    struct artifact_ref_t *output_ref; //model
    char *parent_span_id; // string
    char *project_id; // string
    struct artifact_ref_t *raw_ref; //model
    int schema_version; //numeric
    long seq; //numeric
    char *span_id; // string
    char *start_time; //date time
    beater_api_span_status__e status; //referenced enum
    char *tenant_id; // string
    struct token_counts_t *tokens; //model
    char *trace_id; // string
    any_type_t *unmapped_attrs; // custom

    int _library_owned; // Is the library responsible for freeing this object?
} canonical_span_t;

__attribute__((deprecated)) canonical_span_t *canonical_span_create(
    list_t* attributes,
    money_t *cost,
    char *end_time,
    char *environment_id,
    artifact_ref_t *input_ref,
    char *kind,
    model_ref_t *model,
    char *name,
    char *normalizer_version,
    artifact_ref_t *output_ref,
    char *parent_span_id,
    char *project_id,
    artifact_ref_t *raw_ref,
    int schema_version,
    long seq,
    char *span_id,
    char *start_time,
    beater_api_span_status__e status,
    char *tenant_id,
    token_counts_t *tokens,
    char *trace_id,
    any_type_t *unmapped_attrs
);

void canonical_span_free(canonical_span_t *canonical_span);

canonical_span_t *canonical_span_parseFromJSON(cJSON *canonical_spanJSON);

cJSON *canonical_span_convertToJSON(canonical_span_t *canonical_span);

#endif /* _canonical_span_H_ */

