# racs-client

**racs-client** is a lightweight C client library for [RACS](https://github.com/racslabs/racs).

## System Requirements

**Supported CPU Architectures:**  
`x86/x86-64`, `arm64` (little-endian only)

**Supported Operating Systems:**  
`macOS`, `Linux`, `Unix`

**Supported Compilers:**  
`GCC 7+`

## Installation

Build and install **racs-client** using CMake:

```bash
git clone --branch main https://github.com/racslabs/racs-client.git && cd racs-client
cmake -DCMAKE_INSTALL_PREFIX=/the/install/path
cmake --build . --target all
cmake --install .
```

## Basic Operations

Use ``racs_client_open`` and ``racs_client_close`` to create and close a connection:

```c++
#include <client.h>

racs_client *client = racs_client_open("localhost", 6381);
racs_client_close(client);
```

To run a command, use ``racs_client_execute``:

```c++
#include <client.h>

racs_client *client = racs_client_open("localhost", 6381);

racs_result *result = racs_client_execute(client, "OPEN 'Beethoven Piano Sonata No.1'");
racs_result_destory(result);

racs_client_close(client);
```

For the full list of supported commands, refer to the documentation in [RACS](https://github.com/racslabs/racs) for the commands.

## Understanding ``racs_result``
``racs_client_execute`` always returns a ``racs_result`` structure:

```c++
typedef struct {
    racs_type type;
    size_t size;
    void *data;
} racs_result;
```
The ``data`` field points to the actual result payload, whose type depends on the ``racs_type`` enum.
Use the table below to correctly interpret the result:

| racs_type          | void *data points to     |
|--------------------|--------------------------|
| `RACS_TYPE_STR`    | `char *`                 |
| `RACS_TYPE_INT`    | `racs_int64 *`           |
| `RACS_TYPE_FLOAT`  | `float *`                |
| `RACS_TYPE_LIST`   | `racs_result **`         |
| `RACS_TYPE_NULL`   | `NULL`                   |
| `RACS_TYPE_ERROR`  | `char *` (error message) |
| `RACS_TYPE_BOOL`   | `bool *`                 |
| `RACS_TYPE_U8VEC`  | `racs_uint8 *`           |
| `RACS_TYPE_S8VEC`  | `racs_int8 *`            |
| `RACS_TYPE_U16VEC` | `racs_uint16 *`          |
| `RACS_TYPE_S16VEC` | `racs_int16 *`           |
| `RACS_TYPE_U32VEC` | `racs_uint32 *`          |
| `RACS_TYPE_S32VEC` | `racs_int32 *`           |
| `RACS_TYPE_F32VEC` | `float *`                |
| `RACS_TYPE_C64VEC` | `racs_complex *`         |
