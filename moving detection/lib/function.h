//
// Created by yellowos on 02/02/2018.
//


#ifndef MOVING_CATCH_FUNCTION_H
#define MOVING_CATCH_FUNCTION_H

#include <opencv2/opencv.hpp>
#include "inc.h"
using namespace cv;

int image_pre_process(cv::Mat *input, cv::Mat *output);
int dft_analys(Mat *src, Mat *dst);
int point_compare(Point point_1, Point point_2, Mat& src);
int area_grow(Mat& image_src, Mat& image_dst);
int area_proc(Mat& image_src, Mat& image_flag, vector<struct area>& area_list);
int display_the_area_list(vector<struct area> &area_list);

#endif //MOVING_CATCH_FUNCTION_H
