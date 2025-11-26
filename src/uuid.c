#include "uuid.h"

void racs_uuid_generate(racs_uuid u) {
    uuid_t uu;
    uuid_generate(uu);

    memcpy(u, uu, 16);
}
