include(CMakeFindDependencyMacro)

set(SomeLibraries_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../out/lib/cmake/SomeLibraries)

find_dependency(SomeLibraries REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/MyLibrariesTargets.cmake")