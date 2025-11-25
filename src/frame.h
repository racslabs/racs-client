
#ifndef RACS_STREAM_H
#define RACS_STREAM_H

#include "uuid.h"
#include "murmur3.h"
#include "crc32c.h"
#include "bytes.h"

typedef struct {
    char chunk_id[3];
    racs_uuid   session_id;
    racs_uint64 stream_id;
    racs_uint32 checksum;
    racs_uint16 block_size;
    racs_uint8  flags;
} racs_frame_header;


typedef struct {
    racs_frame_header header;
    racs_uint8 *pcm_block;
} racs_frame;

void racs_frame_init(racs_frame *frame, const char *stream_id);

void racs_frame_header_init(racs_frame_header *header, const char *stream_id);

void racs_frame_set_block(racs_frame *frame, racs_uint8 *block, racs_uint16 size);

#endif //RACS_STREAM_H