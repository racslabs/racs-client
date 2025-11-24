
#ifndef RACS_CONN_H
#define RACS_CONN_H

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "memory.h"

typedef struct {
    int fd;
} racs_conn;

void racs_conn_open(racs_conn *conn, const char *host, int port);

void racs_conn_init_socket(racs_conn *conn);

void racs_conn_connect(racs_conn *conn, const char *host, int port);

size_t racs_send(racs_conn *conn, const char *data, size_t size);

size_t racs_recv(racs_conn *conn, racs_memstream *memstream, size_t len);

void racs_len_prefix(const racs_conn *conn, size_t *len);


#endif //RACS_CONN_H