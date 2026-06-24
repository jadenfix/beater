/*
 * dead_letter_replay_report.h
 *
 * 
 */

#ifndef _dead_letter_replay_report_H_
#define _dead_letter_replay_report_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct dead_letter_replay_report_t dead_letter_replay_report_t;

#include "publish_ack.h"



typedef struct dead_letter_replay_report_t {
    struct publish_ack_t *ack; //model
    char *message_id; // string
    char *project_id; // string
    int reset_attempts; //boolean
    char *tenant_id; // string

    int _library_owned; // Is the library responsible for freeing this object?
} dead_letter_replay_report_t;

__attribute__((deprecated)) dead_letter_replay_report_t *dead_letter_replay_report_create(
    publish_ack_t *ack,
    char *message_id,
    char *project_id,
    int reset_attempts,
    char *tenant_id
);

void dead_letter_replay_report_free(dead_letter_replay_report_t *dead_letter_replay_report);

dead_letter_replay_report_t *dead_letter_replay_report_parseFromJSON(cJSON *dead_letter_replay_reportJSON);

cJSON *dead_letter_replay_report_convertToJSON(dead_letter_replay_report_t *dead_letter_replay_report);

#endif /* _dead_letter_replay_report_H_ */

