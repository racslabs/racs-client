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

    racs_result *result = racs_unpack((char *)memstream.data, memstream.pos);
    free(memstream.data);

    return result;
}

void racs_client_stream(racs_client *client, const char *stream_id, racs_uint16 chunk_size, racs_int32 *data, size_t size) {
    racs_stream(&client->conn, stream_id, chunk_size, data, size);
}

void racs_client_close(racs_client *client) {
    racs_conn_close(&client->conn);
}