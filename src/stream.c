#include "stream.h"

racs_uint16 racs_stream_bit_depth(racs_conn *conn, const char *stream_id) {

    char *command;
    asprintf(&command, "INFO '%s' 'bit_depth'", stream_id);

    racs_send(conn, command,  strlen(command) + 1);
    free(command);

    size_t len;
    racs_len_prefix(conn, &len);

    racs_memstream memstream;
    racs_memstream_init(&memstream);

    racs_recv(conn, &memstream, len);

    racs_result *result = racs_unpack((char *)memstream.data, memstream.pos);
    free(memstream.data);

    return *(racs_uint16 *)result->data;
}

void racs_stream(racs_conn *conn, const char *stream_id, racs_uint16 chunk_size, racs_int32 *data, size_t size) {
    racs_uint16 bit_depth = racs_stream_bit_depth(conn, stream_id);

    racs_frame frame;
    racs_frame_init(&frame, stream_id);

    size_t i = 0;
    racs_uint16 n = chunk_size / (bit_depth / 8);

    for (i = 0; i < size; i += n) {
        racs_uint8 *pcm_block = racs_pack(data + i, bit_depth, n);
        racs_frame_set_block(&frame, pcm_block, chunk_size);

        racs_send_frame(conn, &frame);

        free(pcm_block);
    }
}

void *racs_pack(racs_int32 *data, racs_uint16 bit_depth, size_t n) {
    if (bit_depth == 16)
        return racs_s32_s16(data, n);
    if (bit_depth == 24)
        return racs_s32_s24(data, n);

    return NULL;

}