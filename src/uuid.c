#include "uuid.h"

void racs_uuid_generate(racs_uuid u) {
    uuid_t uu;
    uuid_generate(uu);

    #ifdef __APPLE__
        memcpy(u, uu.bytes, 16);
    #else
        memcpy(u, uu, 16);
    #endif

}
