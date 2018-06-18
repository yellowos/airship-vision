//
// Created by yellowos on 01/05/2018.
//

#ifndef CAR_DETECTION_2018_5_1_CAR_DETECTION_H
#define CAR_DETECTION_2018_5_1_CAR_DETECTION_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cmath>

#include <vector>
#include <deque>



using namespace cv;
using namespace std;
using namespace cv::ml;


int car_detection(Mat image, vector<RotatedRect> &rects);


#endif //CAR_DETECTION_2018_5_1_CAR_DETECTION_H
