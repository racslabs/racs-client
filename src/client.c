#include "client.h"

racs_client *racs_client_open(const char *host, int port) {
    racs_client *client = malloc(sizeof(racs_client));

    racs_conn_open(&client->conn, host, port);
    return client;
}

racs_result *racs_client_execute(racs_client *client, const char *command) {
    racs_send(&client->conn, command, strlen(command) + 1);

    size_t len;
    racs_len_prefix(&client->conn, &len);

    racs_memstream memstream;
    racs_memstream_init(&memstream);

    racs_recv(&client->conn, &memstream, len);

    return racs_unpack((char *)memstream.data, memstream.pos);
}