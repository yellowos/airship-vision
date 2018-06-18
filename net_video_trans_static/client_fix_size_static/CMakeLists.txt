cmake_minimum_required(VERSION 3.6)
project(v4l2)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)


set(SOURCE_FILES main.cpp push_image.cpp push_image.h parameters.h)
add_executable(v4l2 ${SOURCE_FILES})

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_video opencv_videoio opencv_videostab)
target_link_libraries(v4l2 ${OpenCV_LIBS})