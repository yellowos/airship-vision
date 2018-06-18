cmake_minimum_required(VERSION 3.10)
project(car_detection_2018_5_1)

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


add_executable(car_detection_2018_5_1 main.cpp src/car_detection.cpp lib/car_detection.h src/road_detection.cpp lib/road_detection.h lib/ctrl_flag.h)

target_link_libraries(car_detection_2018_5_1 ${OpenCV_LIBS})
