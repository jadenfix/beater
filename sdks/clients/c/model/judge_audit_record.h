/*
 * judge_audit_record.h
 *
 * 
 */

#ifndef _judge_audit_record_H_
#define _judge_audit_record_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct judge_audit_record_t judge_audit_record_t;

#include "money.h"



typedef struct judge_audit_record_t {
    int cached; //boolean
    struct money_t *charged_cost; //model
    char *created_at; //date time
    char *evaluator_id; // string
    char *judge_call_id; // string
    char *model; // string
    char *project_id; // string
    char *provider; // string
    struct money_t *provider_cost; //model
    char *provider_secret_id; // string
    char *request_hash; // string
    char *response_hash; // string
    double score; //numeric
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} judge_audit_record_t;

__attribute__((deprecated)) judge_audit_record_t *judge_audit_record_create(
    int cached,
    money_t *charged_cost,
    char *created_at,
    char *evaluator_id,
    char *judge_call_id,
    char *model,
    char *project_id,
    char *provider,
    money_t *provider_cost,
    char *provider_secret_id,
    char *request_hash,
    char *response_hash,
    double score,
    char *tenant_id
);

void judge_audit_record_free(judge_audit_record_t *judge_audit_record);

judge_audit_record_t *judge_audit_record_parseFromJSON(cJSON *judge_audit_recordJSON);

cJSON *judge_audit_record_convertToJSON(judge_audit_record_t *judge_audit_record);

#endif /* _judge_audit_record_H_ */

