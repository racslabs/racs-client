
#ifndef RACS_UUID_H
#define RACS_UUID_H

#include <uuid/uuid.h>
#include <string.h>
#include "types.h"

typedef racs_uint8 racs_uuid [16];

void racs_uuid_generate(racs_uuid u);

#endif //RACS_UUID_H