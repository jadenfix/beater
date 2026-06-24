/*
 * dead_letter.h
 *
 * 
 */

#ifndef _dead_letter_H_
#define _dead_letter_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct dead_letter_t dead_letter_t;

#include "bus_message.h"



typedef struct dead_letter_t {
    char *failed_at; //date time
    struct bus_message_t *message; //model
    char *reason; // string

    int _library_owned; // Is the library responsible for freeing this object?
} dead_letter_t;

__attribute__((deprecated)) dead_letter_t *dead_letter_create(
    char *failed_at,
    bus_message_t *message,
    char *reason
);

void dead_letter_free(dead_letter_t *dead_letter);

dead_letter_t *dead_letter_parseFromJSON(cJSON *dead_letterJSON);

cJSON *dead_letter_convertToJSON(dead_letter_t *dead_letter);

#endif /* _dead_letter_H_ */

