#include "unpack.h"

char *racs_unpack_type(msgpack_object *obj) {
    size_t size = obj->via.array.ptr[0].via.str.size + 1;

    char *str = malloc(size);
    snprintf(str, size, "%s", obj->via.array.ptr[0].via.str.ptr);

    return str;
}

racs_result *racs_unpack_str(msgpack_object *obj, int n) {
    racs_result *result = malloc(sizeof(racs_result));

    result->size = obj->via.array.ptr[n].via.str.size + 1;
    result->data = malloc(result->size);

    snprintf(result->data, result->size, "%s", obj->via.array.ptr[n].via.str.ptr);
    result->type = RACS_TYPE_STR;

    return result;
}

racs_result *racs_unpack_err(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));

    result->size = obj->via.array.ptr[1].via.str.size + 1;
    result->data = malloc(result->size);

    snprintf(result->data, result->size, "%s", obj->via.array.ptr[1].via.str.ptr);
    result->type = RACS_TYPE_ERROR;

    perror(result->data);

    return result;
}

racs_result *racs_unpack_int(msgpack_object *obj, int n) {
    racs_result *result = malloc(sizeof(racs_result));

    result->data = malloc(sizeof(racs_int64));
    result->size = sizeof(racs_int64);

    *(racs_int64 *)result->data = obj->via.array.ptr[n].via.i64;
    result->type = RACS_TYPE_INT;

    return result;
}

racs_result *racs_unpack_float(msgpack_object *obj, int n) {
    racs_result *result = malloc(sizeof(racs_result));

    result->data = malloc(sizeof(double));
    result->size = sizeof(double);

    *(double *)result->data = obj->via.array.ptr[n].via.f64;
    result->type = RACS_TYPE_FLOAT;

    return result;
}

racs_result *racs_unpack_bool(msgpack_object *obj, int n) {
    racs_result *result = malloc(sizeof(racs_result));

    result->data = malloc(sizeof(bool));
    result->size = sizeof(bool);

    *(bool *)result->data = obj->via.array.ptr[n].via.boolean;
    result->type = RACS_TYPE_BOOL;

    return result;
}

racs_result *racs_unpack_null() {
    racs_result *result = malloc(sizeof(racs_result));

    result->size = 0;
    result->data = NULL;
    result->type = RACS_TYPE_NULL;

    return result;
}

racs_result *racs_unpack_u8v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size;

    result->data = malloc(sizeof(racs_uint8) * result->size);
    result->size = sizeof(racs_uint8) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_U8VEC;

    return result;
}

racs_result *racs_unpack_s8v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size;

    result->data = malloc(sizeof(racs_int8) * result->size);
    result->size = sizeof(racs_int8) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_S8VEC;

    return result;
}

racs_result *racs_unpack_u16v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size / sizeof(racs_uint16);

    result->data = malloc(sizeof(racs_uint16) * result->size);
    result->size = sizeof(racs_uint16) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_U16VEC;

    return result;
}

racs_result *racs_unpack_s16v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size / sizeof(racs_int16);

    result->data = malloc(sizeof(racs_int16) * result->size);
    result->size = sizeof(racs_int16) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_S16VEC;

    return result;
}

racs_result *racs_unpack_u32v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size / sizeof(racs_uint32);

    result->data = malloc(sizeof(racs_uint32) * result->size);
    result->size = sizeof(racs_uint32) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_U32VEC;

    return result;
}

racs_result *racs_unpack_s32v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size / sizeof(racs_int32);

    result->data = malloc(sizeof(racs_int32) * result->size);
    result->size = sizeof(racs_int32) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_S32VEC;

    return result;
}

racs_result *racs_unpack_f32v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size / sizeof(float);

    result->data = malloc(sizeof(float) * result->size);
    result->size = sizeof(float) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_F32VEC;

    return result;
}

racs_result *racs_unpack_c64v(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));
    result->size = obj->via.array.ptr[1].via.bin.size / sizeof(racs_complex);

    result->data = malloc(sizeof(racs_complex) * result->size);
    result->size = sizeof(racs_complex) * result->size;

    memcpy(result->data, obj->via.array.ptr[1].via.bin.ptr, result->size);
    result->type = RACS_TYPE_C64VEC;

    return result;
}

racs_result *racs_unpack_list(msgpack_object *obj) {
    racs_result *result = malloc(sizeof(racs_result));

    result->size = obj->via.array.size - 1;
    result->data = malloc(sizeof(racs_result *) * result->size);

    for (size_t i = 0; i < result->size; i++) {
        msgpack_object_type type = obj->via.array.ptr[i + 1].type;

        switch (type) {
            case MSGPACK_OBJECT_BOOLEAN: {
                racs_result *r = racs_unpack_bool(obj, i + 1);
                ((racs_result **) result->data)[i] = r;
            }
                break;
            case MSGPACK_OBJECT_POSITIVE_INTEGER:
            case MSGPACK_OBJECT_NEGATIVE_INTEGER: {
                racs_result *r = racs_unpack_int(obj, i + 1);
                ((racs_result **) result->data)[i] = r;
            }
                break;
            case MSGPACK_OBJECT_FLOAT: {
                racs_result *r = racs_unpack_float(obj, i + 1);
                ((racs_result **) result->data)[i] = r;
            }
                break;
            case MSGPACK_OBJECT_STR: {
                racs_result *r = racs_unpack_str(obj, i + 1);
                ((racs_result **) result->data)[i] = r;
            }
                break;
            default:
                perror("Invalid element type");
                break;
        }
    }

    return result;
}

racs_result *racs_unpack(char *data, size_t size) {
    msgpack_unpacked msg;
    msgpack_unpacked_init(&msg);

    if (msgpack_unpack_next(&msg, data, size, 0) == MSGPACK_UNPACK_PARSE_ERROR)
        perror("Error parsing response");

    const char *type = racs_unpack_type(&msg.data);

    if (strcmp(type, "string") == 0)
        return racs_unpack_str(&msg.data, 1);
    if (strcmp(type, "error") == 0)
        return racs_unpack_err(&msg.data);
    if (strcmp(type, "int") == 0)
        return racs_unpack_int(&msg.data, 1);
    if (strcmp(type, "float") == 0)
        return racs_unpack_float(&msg.data, 1);
    if (strcmp(type, "bool") == 0)
        return racs_unpack_bool(&msg.data, 1);
    if (strcmp(type, "list") == 0)
        return racs_unpack_list(&msg.data);
    if (strcmp(type, "null") == 0)
        return racs_unpack_null();
    if (strcmp(type, "u8v") == 0)
        return racs_unpack_u8v(&msg.data);
    if (strcmp(type, "s8v") == 0)
        return racs_unpack_s8v(&msg.data);
    if (strcmp(type, "u16v") == 0)
        return racs_unpack_u16v(&msg.data);
    if (strcmp(type, "s16v") == 0)
        return racs_unpack_s16v(&msg.data);
    if (strcmp(type, "u32v") == 0)
        return racs_unpack_u32v(&msg.data);
    if (strcmp(type, "s32v") == 0)
        return racs_unpack_s32v(&msg.data);
    if (strcmp(type,  "f32v") == 0)
        return racs_unpack_f32v(&msg.data);
    if (strcmp(type, "c64v") == 0)
        return racs_unpack_c64v(&msg.data);

    return NULL;
}

void racs_result_destroy(racs_result *result) {
    switch (result->type) {
        case RACS_TYPE_STR:
        case RACS_TYPE_INT:
        case RACS_TYPE_FLOAT:
        case RACS_TYPE_ERROR:
        case RACS_TYPE_BOOL:
        case RACS_TYPE_U8VEC:
        case RACS_TYPE_S8VEC:
        case RACS_TYPE_U16VEC:
        case RACS_TYPE_S16VEC:
        case RACS_TYPE_U32VEC:
        case RACS_TYPE_S32VEC:
        case RACS_TYPE_F32VEC:
        case RACS_TYPE_C64VEC:
            free(result->data);
            free(result);
            break;
        case RACS_TYPE_LIST: {
            racs_result ** r = result->data;

            for (size_t i = 0; i < result->size; i++)
                racs_result_destroy(r[i]);

            free(result->data);
            free(result);
        }
            break;
        case RACS_TYPE_NULL:
            break;
    }
}