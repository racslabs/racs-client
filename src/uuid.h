
#ifndef RACS_UUID_H
#define RACS_UUID_H

#include "types.h"

#if defined(_WIN32)
    #include <rpc.h>
    #pragma comment(lib, "Rpcrt4.lib")
#else
    #include <uuid/uuid.h>
#endif

#include <string.h>

typedef racs_uint8 racs_uuid [16];

void racs_uuid_generate(racs_uuid u);




#endif //RACS_UUID_H