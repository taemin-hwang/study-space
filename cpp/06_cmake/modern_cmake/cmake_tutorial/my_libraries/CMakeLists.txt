## CMakeLists.txt for MyLibraries ##
cmake_minimum_required(VERSION 3.5)

project(MyLibraries VERSION 1.0 LANGUAGES CXX)

## it uses find_package(some_libraries REQUIRED) to import SomeLibraries package.
## This triffers CMake to search for SomeLibrariesConfig.cmake file.
find_package(SomeLibraries REQUIRED)

add_library(MyLibraryA SHARED src/my_library_a.cpp)

target_include_directories(MyLibraryA
PUBLIC
$<INSTALL_INTERFACE:include>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

## by adding PRIVATE keyword, it is specifying that the MyLibararyA's dependency to SomeLibraryB as "private"
## Although other target link MyLibraryA, inherited properties from SomeLibraryB will not be passed.

target_link_libraries(MyLibraryA
PUBLIC
SomeLibraries::SomeLibraryA
PRIVATE
SomeLibraries::SomeLibraryB
)

install(TARGETS MyLibraryA
EXPORT  MyLibraries-export
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
)

install(EXPORT MyLibraries-export
FILE
MyLibrariesTargets.cmake
NAMESPACE
MyLibraries::
DESTINATION
lib/cmake/MyLibraries
)

install(FILES
${CMAKE_CURRENT_SOURCE_DIR}/include/my_libraries/my_library_a.hpp
DESTINATION "include/MyLibraries")

install(FILES
${CMAKE_CURRENT_SOURCE_DIR}/cmake/MyLibrariesConfig.cmake
DESTINATION "lib/cmake/MyLibraries" )
