#include "src/socket.h"
#include "src/unpack.h"

int main(void) {
    racs_conn conn;
    racs_conn_open(&conn, "localhost", 6381);

    racs_send(&conn, "EVAL '(list 2.0)'", strlen("EVAL '(list 2.0)'")+1);

    size_t len;
    racs_len_prefix(&conn, &len);

    racs_memstream memstream;
    racs_memstream_init(&memstream);

    racs_recv(&conn, &memstream, len);

    racs_result *res = racs_unpack((char*)memstream.data, memstream.pos);
    racs_result *s = ((racs_result **)res->data)[0];

    printf("%f", *(double*)s->data);


    return 0;
}