/*
 * native_ingest_request.h
 *
 * 
 */

#ifndef _native_ingest_request_H_
#define _native_ingest_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct native_ingest_request_t native_ingest_request_t;

#include "any_type.h"
#include "auth_context.h"
#include "model_ref.h"
#include "money.h"
#include "redaction_class.h"
#include "span_status.h"
#include "tenant_scope.h"
#include "token_counts.h"



typedef struct native_ingest_request_t {
    list_t* attributes; //map
    struct auth_context_t *auth_context; //model
    struct money_t *cost; //model
    char *end_time; //date time
    char *idempotency_key; // string
    any_type_t *input; // custom
    char *kind; // string
    struct model_ref_t *model; //model
    char *name; // string
    any_type_t *output; // custom
    char *parent_span_id; // string
    beater_api_redaction_class__e redaction_class; //referenced enum
    struct tenant_scope_t *scope; //model
    long seq; //numeric
    char *span_id; // string
    char *start_time; //date time
    beater_api_span_status__e status; //referenced enum
    struct token_counts_t *tokens; //model
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} native_ingest_request_t;

__attribute__((deprecated)) native_ingest_request_t *native_ingest_request_create(
    list_t* attributes,
    auth_context_t *auth_context,
    money_t *cost,
    char *end_time,
    char *idempotency_key,
    any_type_t *input,
    char *kind,
    model_ref_t *model,
    char *name,
    any_type_t *output,
    char *parent_span_id,
    beater_api_redaction_class__e redaction_class,
    tenant_scope_t *scope,
    long seq,
    char *span_id,
    char *start_time,
    beater_api_span_status__e status,
    token_counts_t *tokens,
    char *trace_id
);

void native_ingest_request_free(native_ingest_request_t *native_ingest_request);

native_ingest_request_t *native_ingest_request_parseFromJSON(cJSON *native_ingest_requestJSON);

cJSON *native_ingest_request_convertToJSON(native_ingest_request_t *native_ingest_request);

#endif /* _native_ingest_request_H_ */

