# --- Find include directory ---
find_path(UUID_INCLUDE_DIR
        NAMES uuid/uuid.h
        HINTS
        /usr/include
        /usr/local/include
        /opt/local/include
)

# --- Find the library ---
find_library(UUID_LIBRARY
        NAMES uuid
        HINTS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
)

set(UUID_LIBRARIES ${UUID_LIBRARY})
set(UUID_INCLUDE_DIRS ${UUID_INCLUDE_DIR})

message(STATUS "uuid include: ${UUID_INCLUDE_DIR}")
message(STATUS "uuid library: ${UUID_LIBRARY}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UUID
        REQUIRED_VARS UUID_LIBRARY UUID_INCLUDE_DIR
)
