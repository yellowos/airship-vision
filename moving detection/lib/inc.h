//
// Created by yellowos on 02/02/2018.
//

#ifndef MOVING_CATCH_INC_H
#define MOVING_CATCH_INC_H

#include <cstdio>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <csignal>
#include <cerrno>

#define MIN_AREA_SIZE 5

using namespace cv;
using namespace std;

struct image{
    Mat image_src;
    Mat image_flag;
    unsigned short current_area;
    Point current_point;
    vector<Point> waiting_points;
    vector<int> area_size;
    int processed;
};

struct area{
    int area_flag;
    int area_num;
    size_t area_size;
    vector<Point> area_point;
    Point area_location;
    Point area_LT;
    Point area_RD;
    vector<Point> area_edge;
    Mat area_Mat;
    Mat area_Mat_std;
    int area_R_ch;
    int area_G_ch;
    int area_B_ch;
    int area_paired_flag;
};

struct area_pair{
    int area_before;
    int area_after;
    double shape_similarity;
    double color_similarity;
    Point moving_vector;
};

struct area_lists{
    vector<struct area> area_before;
    vector<struct area> area_after;
    vector<struct area_pair> area_pairs;
};



#endif //MOVING_CATCH_INC_H
