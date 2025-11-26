
#ifndef RACS_CONN_H
#define RACS_CONN_H

#if defined(_WIN32) || defined(__CYGWIN__)
    #include <winsock2.h>
    #include <ws2tcpip.h>

    #pragma comment(lib, "ws2_32.lib")
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/tcp.h>
    #include <netdb.h>
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "memory.h"

typedef struct {
    int fd;
} racs_conn;

void racs_conn_open(racs_conn *conn, const char *host, int port);

void racs_conn_init_socket(racs_conn *conn);

void racs_conn_connect(racs_conn *conn, const char *host, int port);

void racs_conn_setsockopt(racs_conn *conn);

size_t racs_send(racs_conn *conn, const char *data, size_t size);

size_t racs_recv(racs_conn *conn, racs_memstream *memstream, size_t len);

void racs_len_prefix(const racs_conn *conn, size_t *len);

void racs_conn_close(racs_conn *conn);

#endif //RACS_CONN_H