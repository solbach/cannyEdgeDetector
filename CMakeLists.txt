cmake_minimum_required(VERSION 2.8)
project( cannyDetector )

find_package( OpenCV REQUIRED )

add_executable( cannyDetector main.cpp )
target_link_libraries( cannyDetector ${OpenCV_LIBS} )