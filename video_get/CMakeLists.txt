cmake_minimum_required(VERSION 3.10)
project(video_get)

set(CMAKE_CXX_STANDARD 11)
set(OpenCV_DIR /usr/local/Cellar/opencv/3.*)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV3_INCLUDE_DIRS})

set(OpenCV_LIBS
        opencv_core
        opencv_imgproc
        opencv_highgui
        opencv_imgcodecs
        opencv_video
        opencv_videoio
        opencv_videostab
        opencv_ml
        opencv_objdetect
        )

add_executable(video_get main.cpp)
target_link_libraries(video_get ${OpenCV_LIBS})