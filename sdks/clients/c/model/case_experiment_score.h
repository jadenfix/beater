/*
 * case_experiment_score.h
 *
 * 
 */

#ifndef _case_experiment_score_H_
#define _case_experiment_score_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct case_experiment_score_t case_experiment_score_t;

#include "any_type.h"
#include "money.h"



typedef struct case_experiment_score_t {
    int baseline_cached; //boolean
    struct money_t *baseline_cost; //model
    any_type_t *baseline_evidence; // custom
    char *baseline_judge_call_id; // string
    any_type_t *baseline_output; // custom
    double baseline_score; //numeric
    any_type_t *baseline_trace; // custom
    int candidate_cached; //boolean
    struct money_t *candidate_cost; //model
    any_type_t *candidate_evidence; // custom
    char *candidate_judge_call_id; // string
    any_type_t *candidate_output; // custom
    double candidate_score; //numeric
    any_type_t *candidate_trace; // custom
    char *case_id; // string
    double delta; //numeric
    any_type_t *reference; // custom

    int _library_owned; // Is the library responsible for freeing this object?
} case_experiment_score_t;

__attribute__((deprecated)) case_experiment_score_t *case_experiment_score_create(
    int baseline_cached,
    money_t *baseline_cost,
    any_type_t *baseline_evidence,
    char *baseline_judge_call_id,
    any_type_t *baseline_output,
    double baseline_score,
    any_type_t *baseline_trace,
    int candidate_cached,
    money_t *candidate_cost,
    any_type_t *candidate_evidence,
    char *candidate_judge_call_id,
    any_type_t *candidate_output,
    double candidate_score,
    any_type_t *candidate_trace,
    char *case_id,
    double delta,
    any_type_t *reference
);

void case_experiment_score_free(case_experiment_score_t *case_experiment_score);

case_experiment_score_t *case_experiment_score_parseFromJSON(cJSON *case_experiment_scoreJSON);

cJSON *case_experiment_score_convertToJSON(case_experiment_score_t *case_experiment_score);

#endif /* _case_experiment_score_H_ */

