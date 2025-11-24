
#ifndef RACS_UNPACK_H
#define RACS_UNPACK_H

#include <msgpack.h>
#include "types.h"

typedef enum {
    RACS_TYPE_STR,
    RACS_TYPE_INT,
    RACS_TYPE_FLOAT,
    RACS_TYPE_LIST,
    RACS_TYPE_NULL,
    RACS_TYPE_ERROR,
    RACS_TYPE_BOOL,
    RACS_TYPE_U8VEC,
    RACS_TYPE_S8VEC,
    RACS_TYPE_U16VEC,
    RACS_TYPE_S16VEC,
    RACS_TYPE_U32VEC,
    RACS_TYPE_S32VEC,
    RACS_TYPE_F32VEC,
    RACS_TYPE_C64VEC
} racs_type;


typedef struct {
    racs_type type;
    size_t size;
    void *data;
} racs_result;


racs_result *racs_unpack(char *data, size_t size);

racs_result *racs_unpack_str(msgpack_object *obj, int n);

racs_result *racs_unpack_err(msgpack_object *obj);

racs_result *racs_unpack_int(msgpack_object *obj, int n);

racs_result *racs_unpack_float(msgpack_object *obj, int n);

racs_result *racs_unpack_bool(msgpack_object *obj, int n);

racs_result *racs_unpack_null();

racs_result *racs_unpack_list(msgpack_object *obj);

racs_result *racs_unpack_u8v(msgpack_object *obj);

racs_result *racs_unpack_s8v(msgpack_object *obj);

racs_result *racs_unpack_u16v(msgpack_object *obj);

racs_result *racs_unpack_s16v(msgpack_object *obj);

racs_result *racs_unpack_u32v(msgpack_object *obj);

racs_result *racs_unpack_s32v(msgpack_object *obj);

racs_result *racs_unpack_f32v(msgpack_object *obj);

racs_result *racs_unpack_c64v(msgpack_object *obj);

char *racs_unpack_type(msgpack_object *obj);

#endif //RACS_UNPACK_H