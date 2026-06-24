/*
 * model_ref.h
 *
 * 
 */

#ifndef _model_ref_H_
#define _model_ref_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct model_ref_t model_ref_t;




typedef struct model_ref_t {
    char *name; // string
    char *provider; // string

    int _library_owned; // Is the library responsible for freeing this object?
} model_ref_t;

__attribute__((deprecated)) model_ref_t *model_ref_create(
    char *name,
    char *provider
);

void model_ref_free(model_ref_t *model_ref);

model_ref_t *model_ref_parseFromJSON(cJSON *model_refJSON);

cJSON *model_ref_convertToJSON(model_ref_t *model_ref);

#endif /* _model_ref_H_ */

