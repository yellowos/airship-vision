// copyright 2018 Yellow One Study
#include <iostream>
#include <opencv2/opencv.hpp>

#include "./lib/car_detection.h"
#include "./lib/road_detection.h"

int main() {
    cv::VideoCapture video(0);
    while (true) {
        cv::Mat image;
        video >> image;

        vector<cv::RotatedRect> rects;
        road_detection(image, 3, &image, 0.97);
        car_detection(image, rects);
    }

    return 0;
}
