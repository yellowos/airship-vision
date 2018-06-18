cmake_minimum_required(VERSION 3.9)
project(moving_catch)

set(CMAKE_CXX_STANDARD 11)

set(OpenCV_DIR /usr/local/Cellar/opencv/3.*)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV3_INCLUDE_DIRS})

add_executable(moving_catch main.cpp lib/paramters.h src/image_pre_process.cpp src/objects_detect.cpp src/mark_objects.cpp src/moving_detect.cpp lib/function.h lib/inc.h)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_video opencv_videoio opencv_videostab)
target_link_libraries(moving_catch ${OpenCV_LIBS})

