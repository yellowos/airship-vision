// copyright 2018 Yellow One Study
// Created by yellowos on 2018/5/5.
//

#ifndef CAR_DETECTION_2018_5_1_ROAD_DETECTION_H

#include <stdlib.h>
#include <unistd.h>
#include <cerrno>
#include <vector>
#include <cmath>
#include <algorithm>

#include <opencv2/opencv.hpp>

#define CELL_SIZE 11
#define ROAD 0
#define NOT_ROAD -1

#define H_STDDEV_MAX 4
#define S_STDDEV_MAX 4
#define V_STDDEV_MAX 4

#define S_AVG_MIN 50
#define V_AVG_MAX 200
#define V_AVG_MIN 0

struct road_part{
    cv::RotatedRect rect_road;
    std::vector<double> phi_similaritys;
    double phi_similarity_sum;
};

int road_detection(cv::Mat input_source, int move_step, cv::Mat* output_source, const double &accuracy_phi);

#define CAR_DETECTION_2018_5_1_ROAD_DETECTION_H



#endif   // CAR_DETECTION_2018_5_1_ROAD_DETECTION_H
