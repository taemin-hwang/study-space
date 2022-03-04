cmake_minimum_required(VERSION 2.4)
PROJECT(driver-tracker)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

FILE(GLOB_RECURSE SRC_FILES src/*.c*)
FILE(GLOB_RECURSE HDR_FILES src/*.h*)

add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES})
add_definitions(-std=c++14)

target_link_libraries(${PROJECT_NAME} pthread)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/opt/${PROJECT_NAME}/bin/)
