cmake_minimum_required(VERSION 3.15)
set(APP_NAME cpp_python)
project(${APP_NAME})

set(CMAKE_CXX_STANDARD 14)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(${APP_NAME} main.cc)
target_link_libraries(${APP_NAME} ${PYTHON_LIBRARIES})

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
