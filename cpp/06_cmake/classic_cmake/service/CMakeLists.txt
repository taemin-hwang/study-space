cmake_minimum_required(VERSION 3.5)

project(MyApplication VERSION 1.0 LANGUAGES CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/mod1")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/mod2")
