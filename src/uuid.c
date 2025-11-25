#include "uuid.h"

void racs_uuid_generate(racs_uuid u) {
#if defined(_WIN32)
    UUID uu;
    UuidCreate(&uu);

    memcpy(u + 0, &uu.Data1, 4);
    memcpy(u + 4, &uu.Data2, 2);
    memcpy(u + 6, &uu.Data3, 2);
    memcpy(u + 8, uu.Data4, 8);
#else
    uuid_t uu;
    uuid_generate(uu);

    #ifdef __APPLE__
        memcpy(u, uu.bytes, 16);
    #else
        memcpy(u, uu, 16);
    #endif
#endif
}
