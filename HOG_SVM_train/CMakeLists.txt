cmake_minimum_required(VERSION 3.10)
project(HOG_SVM_train)

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

add_executable(HOG_SVM_train main.cpp)

target_link_libraries(HOG_SVM_train ${OpenCV_LIBS})