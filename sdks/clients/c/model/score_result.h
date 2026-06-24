/*
 * score_result.h
 *
 * 
 */

#ifndef _score_result_H_
#define _score_result_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct score_result_t score_result_t;

#include "any_type.h"



typedef struct score_result_t {
    any_type_t *evidence; // custom
    char *label; // string
    double score; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} score_result_t;

__attribute__((deprecated)) score_result_t *score_result_create(
    any_type_t *evidence,
    char *label,
    double score
);

void score_result_free(score_result_t *score_result);

score_result_t *score_result_parseFromJSON(cJSON *score_resultJSON);

cJSON *score_result_convertToJSON(score_result_t *score_result);

#endif /* _score_result_H_ */

