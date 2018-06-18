#include <iostream>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <cerrno>
#include <string>
#include <vector>

#define DEBUG_IMAGE_SHOW


int main() {
    std::cout<<"process start"<<std::endl;
    //sleep(15);
    std::cout<<"start cap video"<<std::endl;
    cv::VideoCapture cap(0);
    cv::Mat frame;
    for (int i = 0; i < 1000; i++) {
        char video_path[255];
        snprintf(video_path, sizeof(video_path), "../video_%d.mp4", i);
        int rate = cap.get(CV_CAP_PROP_FPS);
        const cv::Size write_size(1920, 1080);
        cv::VideoWriter video_writer(video_path, -1, rate, write_size);
        for (int k = 0; k < 120; k++) {
            if(cap.isOpened()) {
                cap >> frame;
                cv::resize(frame, frame, write_size);
                video_writer << frame;
#ifdef DEBUG_IMAGE_SHOW
                cv::imshow("frame", frame);
                cv::waitKey(1);
#endif
            } else {
                perror("error the camera is notn opened\n");
            }
        }
        video_writer.release();
    }
    return 0;
}