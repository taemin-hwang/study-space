project (singleton)
set (APP_NAME singleton)

file(GLOB_RECURSE SOURCES
    ../src/*.cc
)

add_compile_options (--std=c++1y -g)

include_directories(
    "../src"
)

link_libraries (pthread)
add_executable (${APP_NAME} ${SOURCES})

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/)
