#include "socket.h"

void racs_conn_open(racs_conn *conn, const char *host, int port) {
    racs_conn_init_socket(conn);
    racs_conn_connect(conn, host, port);
}

void racs_conn_init_socket(racs_conn *conn) {
    conn->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (conn->fd < 0) {
        perror("socket");
    }
}

void racs_conn_connect(racs_conn *conn, const char *host, int port) {
    struct addrinfo hints = {0}, *res;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%u", port);

    int rc = getaddrinfo(host, port_str, &hints, &res);
    if (rc != 0) {
        perror("Error getting address info");
        return;
    }

    rc = connect(conn->fd, res->ai_addr, res->ai_addrlen);
    if (rc < 0) {
        perror("Connection refused");
        close(conn->fd);
    }

    freeaddrinfo(res);
}

size_t racs_send(racs_conn *conn, const char *data, size_t size) {
    size_t bytes = 0;

    // len prefix
    ssize_t rc = send(conn->fd, &size, sizeof(size), 0);
    if (rc < 0) {
        perror("send() failed");
        return -1;
    }

    while (bytes < size) {
        rc = send(conn->fd, data + bytes, size - bytes, 0);
        if (rc < 0) {
            perror("send() failed");
            return -1;
        }

        bytes += rc;
    }

    return bytes;
}

void racs_len_prefix(const racs_conn *conn, size_t *len) {
    int rc = recv(conn->fd, len, sizeof(size_t), 0);
    if (rc < 0) {
        perror("recv() failed");
    }

}

size_t racs_recv(racs_conn *conn, racs_memstream *memstream, size_t len) {
    char buf[1024];

    while (memstream->pos < len) {
        int rc = recv(conn->fd, buf, sizeof(buf), 0);

        if (rc < 0) {
            perror("recv() failed");
            return -1;
        }

        if (rc == 0) {
            perror("Connection closed");
            return -1;
        }

        racs_memstream_write(memstream, buf, rc);
    }

    return memstream->pos;
}

