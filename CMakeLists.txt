cmake_minimum_required(VERSION 3.22.1)
project(racs_client LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

set(RACS_TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(RACS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Msgpack)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(UUID)
endif ()

include_directories(
        ${MSGPACK_INCLUDE_DIRS}
        ${UUID_INCLUDE_DIRS}
)

add_executable(racs_client main.c
        src/socket.h
        src/socket.c
        src/memory.h
        src/memory.c
        src/types.h
        src/types.c
        src/export.h
        src/unpack.h
        src/unpack.c
        src/client.h
        src/client.c
        src/frame.h
        src/murmur3.c
        src/murmur3.h
        src/crc32c.h
        src/crc32c.c
        src/uuid.h
        src/uuid.c
        src/frame.c
        src/bytes.h
        src/stream.h
        src/stream.c
)

target_link_libraries(racs_client
        ${MSGPACK_LIBRARIES}
        ${UUID_LIBRARIES}
)
