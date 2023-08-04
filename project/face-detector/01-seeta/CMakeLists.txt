cmake_minimum_required(VERSION 2.4)
PROJECT(face-detector)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/FaceDetection)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/FaceDetection/include
)

FILE(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)
FILE(GLOB_RECURSE HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h*)

set(facedet_required_libs seeta_facedet_lib)

find_package(OpenCV)
if (NOT OpenCV_FOUND)
    message(WARNING "OpenCV not found. Test will not be built.")
else()
    include_directories(${OpenCV_INCLUDE_DIRS})
    list(APPEND facedet_required_libs ${OpenCV_LIBS})
    add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES})
    target_link_libraries(${PROJECT_NAME} ${facedet_required_libs})
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/opt/${PROJECT_NAME}/bin/)
