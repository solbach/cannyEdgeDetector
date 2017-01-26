cmake_minimum_required(VERSION 2.8)

set(execName detector)
set(PROJECT_NAME "Detector")
project( ${PROJECT_NAME} )

find_package( OpenCV REQUIRED )

set(SRC_FOLDER src)
file(GLOB_RECURSE SRC_FILES "${SRC_FOLDER}/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(${execName} ${SRC_FILES})
set_property(TARGET ${execName} PROPERTY OUTPUT_NAME ${execName})
add_definitions(-std=c++0x -g -O3)

target_link_libraries(${execName} ${OpenCV_LIBS})