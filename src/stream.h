
#ifndef RACS_STREAM_H
#define RACS_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "frame.h"

void racs_stream(racs_conn *conn, const char *stream_id, racs_uint16 chunk_size, racs_int32 *data, size_t size);

racs_uint16 racs_stream_bit_depth(racs_conn *conn, const char *stream_id);

void *racs_pack(racs_int32 *data, racs_uint16 bit_depth, size_t n);

#ifdef __cplusplus
}
#endif

#endif //RACS_STREAM_H