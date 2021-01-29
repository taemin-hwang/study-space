## CMakeLists.txt for the MyApplication executable package ##
cmake_minimum_required(VERSION 3.5)

project(MyApplication VERSION 1.0 LANGUAGES CXX)

find_package(MyLibraries REQUIRED)

add_executable(MyApplication src/main.cpp)

target_link_libraries(MyApplication PRIVATE MyLibraries::MyLibraryA)
