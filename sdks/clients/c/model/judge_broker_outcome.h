/*
 * judge_broker_outcome.h
 *
 * 
 */

#ifndef _judge_broker_outcome_H_
#define _judge_broker_outcome_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct judge_broker_outcome_t judge_broker_outcome_t;

#include "judge_audit_record.h"
#include "money.h"
#include "score_result.h"



typedef struct judge_broker_outcome_t {
    struct judge_audit_record_t *audit; //model
    struct money_t *remaining_budget; //model
    struct score_result_t *result; //model

    int _library_owned; // Is the library responsible for freeing this object?
} judge_broker_outcome_t;

__attribute__((deprecated)) judge_broker_outcome_t *judge_broker_outcome_create(
    judge_audit_record_t *audit,
    money_t *remaining_budget,
    score_result_t *result
);

void judge_broker_outcome_free(judge_broker_outcome_t *judge_broker_outcome);

judge_broker_outcome_t *judge_broker_outcome_parseFromJSON(cJSON *judge_broker_outcomeJSON);

cJSON *judge_broker_outcome_convertToJSON(judge_broker_outcome_t *judge_broker_outcome);

#endif /* _judge_broker_outcome_H_ */

