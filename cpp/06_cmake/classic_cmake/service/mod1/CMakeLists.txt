cmake_minimum_required(VERSION 3.5)

project(mod1 VERSION 1.0 LANGUAGES CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(mod1 src/main.cpp)
