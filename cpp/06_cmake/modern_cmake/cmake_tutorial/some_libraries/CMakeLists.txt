## CMakeLists.txt for SomeLibraries ##

cmake_minimum_required(VERSION 3.5)

project(SomeLibraries VERSION 1.0 LANGUAGES CXX)
add_library(SomeLibraryA SHARED src/some_library_a.cpp)

## you might have noticed that SomeLibraries packages defines 2 targets (SomeLibraryA, SomeLibraryB)
## 'target_include_directories' it is specifying include path for the target
## you can see this as if the object "SomeLibraryA" is calling its member function 'target_include_directories'
## "IMPORTANT" since it has the PUBLIC keyword, the include path will be applied to the user of SomeLibraryA when it addeds dependency via target_link_libraries.

## generator expressions are used to selectively choose the include path.
## $<BUILD_INTERFACE:> is used when building target itself
## $<INSTALL_INTERACE:> is used when we use find_package and import target in another CMake project

target_include_directories(SomeLibraryA
PUBLIC
$<INSTALL_INTERFACE:include>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(SomeLibraryB SHARED src/some_library_b.cpp)

target_include_directories(SomeLibraryB
PUBLIC
$<INSTALL_INTERFACE:include>
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

## it is setting the installation locations for each target and putting the information out to SomeLibraries-export
install(TARGETS SomeLibraryA SomeLibraryB
EXPORT SomeLibraries-export
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
)

## it is writing out the information that was set to SomeLibraries-export to SomeLibrariesTarget.cmake file and copying to DESTINATION
## NAMESPACE can be specified for each exported target
install(EXPORT SomeLibraries-export
FILE
SomeLibrariesTargets.cmake
NAMESPACE
SomeLibraries::
DESTINATION
lib/cmake/SomeLibraries
)

install(FILES
${CMAKE_CURRENT_SOURCE_DIR}/include/some_libraries/some_library_a.hpp
${CMAKE_CURRENT_SOURCE_DIR}/include/some_libraries/some_library_b.hpp
DESTINATION "include/SomeLibraries")

install(FILES
${CMAKE_CURRENT_SOURCE_DIR}/cmake/SomeLibrariesConfig.cmake
DESTINATION "lib/cmake/SomeLibraries" )
