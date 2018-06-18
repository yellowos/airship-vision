cmake_minimum_required(VERSION 3.8)
project(service)

set(CMAKE_CXX_STANDARD 11)

set(OpenCV_DIR /usr/local/Cellar/opencv/3.*)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV3_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp get_image.cpp get_image.h parameters.h)
add_executable(service ${SOURCE_FILES})

set(UNP_LIBS unp)
target_link_libraries(service ${UNP_LIBS})

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_video opencv_videoio opencv_videostab)
target_link_libraries(service ${OpenCV_LIBS})