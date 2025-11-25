#include "frame.h"

void racs_frame_init(racs_frame *frame, const char *stream_id) {
    racs_frame_header_init(&frame->header, stream_id);
}

void racs_frame_header_init(racs_frame_header *header, const char *stream_id) {
    memcpy(header->chunk_id, "rsp", 3);
    racs_uuid_generate(header->session_id);

    racs_uint64 hash[2];
    murmur3_x64_128(stream_id, strlen(stream_id), 0, hash);

    header->stream_id = hash[0];
    header->flags = 0;
}

void racs_frame_set_block(racs_frame *frame, racs_uint8 *block, racs_uint16 size) {
    frame->header.checksum = crc32c(0, block, size);
    frame->header.block_size = size;
    frame->pcm_block = block;
}

racs_uint8 *racs_frame_write(racs_frame *frame) {
    racs_uint8 *buf = malloc(sizeof(racs_frame_header) + frame->header.block_size);

    memcpy(buf, frame->header.chunk_id, 3);
    memcpy(buf + 3, frame->header.session_id, 16);

    racs_write_uint64(buf, frame->header.stream_id, 19);
    racs_write_uint32(buf, frame->header.checksum, 27);
    racs_write_uint16(buf, frame->header.block_size, 31);

    buf[33] = 0;
    memcpy(buf + 34, frame->pcm_block, 16);

    return buf;
}

void racs_send_frame(racs_conn *conn, racs_frame *frame) {
    racs_uint8 *block = racs_frame_write(frame);

    racs_send(conn, (char *)block, 34 + frame->header.block_size);
    free(block);

    size_t len;
    racs_len_prefix(conn, &len);

    racs_memstream memstream;
    racs_memstream_init(&memstream);

    racs_recv(conn, &memstream, len);

    racs_result *result = racs_unpack((char *)memstream.data, memstream.pos);
    free(memstream.data);

    if (result->type == RACS_TYPE_ERROR) {
        perror(result->data);
        racs_result_destroy(result);
    }
}





