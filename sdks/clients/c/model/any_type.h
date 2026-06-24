/*
 * any_type.h
 *
 * Free-form / additionalProperties value. The openapi-generator C template
 * leaves this as a placeholder; we alias it to cJSON, which is the on-the-wire
 * representation the generated (de)serializers already use.
 */

#ifndef _any_type_H_
#define _any_type_H_

#include "../external/cJSON.h"

typedef cJSON any_type_t;

#endif /* _any_type_H_ */
