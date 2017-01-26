cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "cannyDetector")
project( ${PROJECT_NAME} )

find_package( OpenCV REQUIRED )

add_executable( cannyDetector src/main.cpp )
target_link_libraries( cannyDetector ${OpenCV_LIBS} )