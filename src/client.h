
#ifndef RACS_CLIENT_H
#define RACS_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "frame.h"
#include "stream.h"

typedef struct {
    racs_conn conn;
} racs_client;

racs_client *racs_client_open(const char *host, int port);

racs_result *racs_client_execute(racs_client *client, const char *command);

void racs_client_stream(racs_client *client, const char *stream_id, racs_uint16 chunk_size, racs_int32 *data, size_t size);

void racs_client_close(racs_client *client);

#ifdef __cplusplus
}
#endif

#endif //RACS_CLIENT_H