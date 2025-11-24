
#ifndef RACS_CLIENT_H
#define RACS_CLIENT_H

#include "socket.h"
#include "unpack.h"

typedef struct {
    racs_conn conn;
} racs_client;

racs_client *racs_client_open(const char *host, int port);

racs_result *racs_client_execute(racs_client *client, const char *command);

#endif //RACS_CLIENT_H