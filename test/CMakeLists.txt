set (TEST_NAME test-googletest)

file(GLOB_RECURSE SOURCES
    ${WORKING_DIR}/src/*.cpp
    ${WORKING_DIR}/test/src/*.cpp
)

list(REMOVE_ITEM SOURCES ${WORKING_DIR}/src/main.cpp)

add_compile_options (--std=c++1y -g)

include_directories(
    "${WORKING_DIR}/src"
    "${WORKING_DIR}/test/src"
)

link_libraries (gtest gmock gtest_main pthread)
add_executable (${TEST_NAME} ${SOURCES})

install(TARGETS ${TEST_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/opt/)
