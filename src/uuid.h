
#ifndef RACS_UUID_H
#define RACS_UUID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <uuid/uuid.h>
#include <string.h>
#include "types.h"

typedef racs_uint8 racs_uuid [16];

void racs_uuid_generate(racs_uuid u);

#ifdef __cplusplus
}
#endif

#endif //RACS_UUID_H