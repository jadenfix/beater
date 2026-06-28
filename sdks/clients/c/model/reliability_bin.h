/*
 * reliability_bin.h
 *
 * 
 */

#ifndef _reliability_bin_H_
#define _reliability_bin_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct reliability_bin_t reliability_bin_t;




typedef struct reliability_bin_t {
    double accuracy; //numeric
    int bin_index; //numeric
    double calibration_gap; //numeric
    double lower_bound; //numeric
    double mean_confidence; //numeric
    int sample_count; //numeric
    double upper_bound; //numeric

    int _library_owned; // Is the library responsible for freeing this object?
} reliability_bin_t;

__attribute__((deprecated)) reliability_bin_t *reliability_bin_create(
    double accuracy,
    int bin_index,
    double calibration_gap,
    double lower_bound,
    double mean_confidence,
    int sample_count,
    double upper_bound
);

void reliability_bin_free(reliability_bin_t *reliability_bin);

reliability_bin_t *reliability_bin_parseFromJSON(cJSON *reliability_binJSON);

cJSON *reliability_bin_convertToJSON(reliability_bin_t *reliability_bin);

#endif /* _reliability_bin_H_ */

