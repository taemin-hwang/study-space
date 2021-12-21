project (curl-client)
set (APP_NAME curl-client)

add_compile_options (--std=c++1y -g)

file(GLOB_RECURSE SOURCES
    src/*.cc
)

include_directories(
    /src
)

link_libraries (curl)
add_executable (${APP_NAME} ${SOURCES})

