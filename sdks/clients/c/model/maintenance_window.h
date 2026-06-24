/*
 * maintenance_window.h
 *
 * 
 */

#ifndef _maintenance_window_H_
#define _maintenance_window_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct maintenance_window_t maintenance_window_t;




typedef struct maintenance_window_t {
    char *ends_at; //date time
    char *starts_at; //date time

    int _library_owned; // Is the library responsible for freeing this object?
} maintenance_window_t;

__attribute__((deprecated)) maintenance_window_t *maintenance_window_create(
    char *ends_at,
    char *starts_at
);

void maintenance_window_free(maintenance_window_t *maintenance_window);

maintenance_window_t *maintenance_window_parseFromJSON(cJSON *maintenance_windowJSON);

cJSON *maintenance_window_convertToJSON(maintenance_window_t *maintenance_window);

#endif /* _maintenance_window_H_ */

