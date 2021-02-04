cmake_minimum_required(VERSION 3.5)

project(mod2 VERSION 1.0 LANGUAGES CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(mod2 src/main.cpp)
