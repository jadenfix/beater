/*
 * eval_result.h
 *
 * 
 */

#ifndef _eval_result_H_
#define _eval_result_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct eval_result_t eval_result_t;

#include "any_type.h"
#include "eval_reproducibility.h"
#include "money.h"
#include "token_counts.h"



typedef struct eval_result_t {
    struct money_t *cost; //model
    char *created_at; //date time
    char *eval_result_id; // string
    any_type_t *evidence; // custom
    char *label; // string
    char *non_reproducible_reason; // string
    char *project_id; // string
    struct eval_reproducibility_t *reproducibility; //model
    double score; //numeric
    char *span_id; // string
    char *tenant_id; // string
    struct token_counts_t *tokens; //model
    char *trace_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} eval_result_t;

__attribute__((deprecated)) eval_result_t *eval_result_create(
    money_t *cost,
    char *created_at,
    char *eval_result_id,
    any_type_t *evidence,
    char *label,
    char *non_reproducible_reason,
    char *project_id,
    eval_reproducibility_t *reproducibility,
    double score,
    char *span_id,
    char *tenant_id,
    token_counts_t *tokens,
    char *trace_id
);

void eval_result_free(eval_result_t *eval_result);

eval_result_t *eval_result_parseFromJSON(cJSON *eval_resultJSON);

cJSON *eval_result_convertToJSON(eval_result_t *eval_result);

#endif /* _eval_result_H_ */

