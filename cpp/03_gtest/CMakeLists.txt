project (googletest)
set (APP_NAME googletest)

message("${WORKING_DIR}")

file(GLOB_RECURSE SOURCES
    ${WORKING_DIR}/src/*.cc
)

add_compile_options (--std=c++1y -g)

include_directories(
    "${WORKING_DIR}/src"
)

link_libraries (pthread)
add_executable (${APP_NAME} ${SOURCES})

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/)

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
