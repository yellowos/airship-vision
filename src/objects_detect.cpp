//
// Created by yellowos on 02/02/2018.
//
/*
                  ___    ___
                 /\_ \  /\_ \
    __  __     __\//\ \ \//\ \     ___   __  __  __    ___     ____
   /\ \/\ \  /'__`\\ \ \  \ \ \   / __`\/\ \/\ \/\ \  / __`\  /',__\
   \ \ \_\ \/\  __/ \_\ \_ \_\ \_/\ \L\ \ \ \_/ \_/ \/\ \L\ \/\__, `\
    \/`____ \ \____\/\____\/\____\ \____/\ \___x___/'\ \____/\/\____/
     `/___/> \/____/\/____/\/____/\/___/  \/__//__/   \/___/  \/___/
        /\___/
        \/__/

*/

#include "../lib/inc.h"
#include "../lib/function.h"
using namespace cv;
using namespace std;




int area_grow(Mat& image_src, Mat& image_dst){
// initialize
    struct image image_in;

    image_in.image_src = image_src;
    imshow("frame", image_in.image_src);
    image_in.image_flag = Mat(image_src.rows, image_src.cols, CV_16UC1);
    for(int v = 0; v < image_in.image_src.cols*image_in.image_src.rows; v++){
        image_in.image_flag.at<unsigned short>(v) = 0;
    }

    printf("image_size:%d*%d\n",image_src.cols, image_src.rows);
    image_in.current_area = 0;
    image_in.waiting_points.clear();
    image_in.area_size.clear();
    image_in.processed = 0;

//find unprocessed point

//        printf("start find unprocessed point\n");

        image_in.processed = 1;
        for(int cols = 1; cols < image_in.image_src.cols-1; cols++) {

            for (int rows = 1; rows < image_in.image_src.rows - 1; rows++) {
                if (image_in.image_flag.at<unsigned short>(rows, cols) == 0) {
                    image_in.waiting_points.push_back(Point(cols, rows));
                    image_in.current_area++;
//                    if (image_in.current_area == 0) {
//                        image_in.current_area += 1;
//                    }
                    image_in.area_size.emplace_back(1);
                    image_in.processed = 0;
                    image_in.image_flag.at<unsigned short>(rows, cols) = image_in.current_area;
//                    if(image_in.current_area == 255) {
//                        printf("point:(%d, %d)  current area: %d\n", cols, rows, image_in.current_area);
//                    }
//                    printf("try area grow\n");
                    while (!image_in.waiting_points.empty()) {
                        image_in.current_point = image_in.waiting_points.back();
//                printf("current point:(%d, %d)\n", image_in.current_point.x, image_in.current_point.y);
                        image_in.waiting_points.pop_back();
                        Point point_left = Point(image_in.current_point.x - 1, image_in.current_point.y);
                        Point point_right = Point(image_in.current_point.x + 1, image_in.current_point.y);
                        Point point_up = Point(image_in.current_point.x, image_in.current_point.y - 1);
                        Point point_down = Point(image_in.current_point.x, image_in.current_point.y + 1);

                        if (point_compare(image_in.current_point, point_left, image_in.image_src) &&
                            (!image_in.image_flag.at<unsigned short>(point_left))) {
                            image_in.image_flag.at<unsigned short>(point_left) = image_in.current_area;
                            if (point_left.x > 0) {
                                image_in.waiting_points.push_back(point_left);
                            }
                            image_in.area_size.back()++;
//                    printf("point:(%d, %d) in area %d\n", point_left.x, point_left.y, image_in.current_area);
                        }
                            if (point_compare(image_in.current_point, point_right, image_in.image_src) &&
                                (!image_in.image_flag.at<unsigned short>(point_right))) {
                                image_in.image_flag.at<unsigned short>(point_right) = image_in.current_area;
                                if (point_right.x < image_in.image_src.cols - 1) {
                                    image_in.waiting_points.push_back(point_right);
                                }
                                image_in.area_size.back()++;
//                    printf("point:(%d, %d) in area %d\n", point_right.x, point_right.y, image_in.current_area);
                            }
                            if (point_compare(image_in.current_point, point_up, image_in.image_src) &&
                                (!image_in.image_flag.at<unsigned short>(point_up))) {
                                image_in.image_flag.at<unsigned short>(point_up) = image_in.current_area;
                                if (point_up.y > 0) {
                                    image_in.waiting_points.push_back(point_up);
                                }
                                image_in.area_size.back()++;
//                    printf("point:(%d, %d) in area %d\n", point_up.x, point_up.y, image_in.current_area);
                            }
                            if (point_compare(image_in.current_point, point_down, image_in.image_src) &&
                                (!image_in.image_flag.at<unsigned short>(point_down))) {
                                image_in.image_flag.at<unsigned short>(point_down) = image_in.current_area;
                                if (point_down.y < image_in.image_src.rows - 1) {
                                    image_in.waiting_points.push_back(point_down);
                                }
                                image_in.area_size.back()++;
//                    printf("point:(%d, %d) in area %d\n", point_down.x, point_down.y, image_in.current_area);
                            }
                        }
//                        if (image_in.area_size.back() < 20) {
//
//                            printf("little size %d\n", image_in.area_size.back());
//                        }
                    }
//                if(image_in.processed == 0){
//                    break;
//                }
                }
//            if(image_in.processed == 0){
//                break;
//            }

        }

//        if(image_in.processed == 1){
//            printf("finish\n");
//            image_dst = image_in.image_flag;
//
//        }
//        else{
////area grow
//
//        }


    image_dst = image_in.image_flag.clone();
    imshow("grow", image_in.image_flag);


//    image_in.image_flag = Mat(image_src.rows, image_src.cols, CV_8UC1);
//    printf("divide into %d areas\n", image_in.current_area);
    return image_in.current_area;
}

inline int point_compare(Point point_1, Point point_2, Mat &src) {
    int R_2;
    int G_2;
    int B_2;
    Mat_<Vec3b> image = src;

    R_2 = image(point_1.y, point_1.x)[0] - image(point_2.y, point_2.x)[0];
    G_2 = image(point_1.y, point_1.x)[1] - image(point_2.y, point_2.x)[1];
    B_2 = image(point_1.y, point_1.x)[2] - image(point_2.y, point_2.x)[2];
    R_2 *= R_2;
    G_2 *= G_2;
    B_2 *= B_2;

    if((R_2+G_2+B_2) < 7*7*3){
        return 1;
    }
    else{
        return 0;
    }

}

int area_proc(Mat& image_src, Mat& image_flag, vector<struct area>& area_list){
    Mat_<Vec3b> image = image_src;
    for(int x = 0; x < image_flag.cols; x++){
        for(int y = 0; y < image_flag.rows; y++){
            int area_flag = image_flag.at<unsigned short>(Point(x, y));
            area_list[area_flag].area_size++;
            area_list[area_flag].area_point.emplace_back(Point(x, y));
            area_list[area_flag].area_location.x += x;
            area_list[area_flag].area_R_ch += image(y, x)[0];
            area_list[area_flag].area_G_ch += image(y, x)[1];
            area_list[area_flag].area_B_ch += image(y, x)[2];
            area_list[area_flag].area_RD.x = (x > area_list[area_flag].area_RD.x ? x : area_list[area_flag].area_RD.x);
            area_list[area_flag].area_LT.x = (x < area_list[area_flag].area_LT.x ? x : area_list[area_flag].area_LT.x);
            area_list[area_flag].area_RD.y = (y < area_list[area_flag].area_RD.y ? y : area_list[area_flag].area_RD.y);
            area_list[area_flag].area_LT.y = (y > area_list[area_flag].area_LT.y ? y : area_list[area_flag].area_LT.y);

            area_list[area_flag].area_paired_flag = 0;
        }
    }
    for(auto area_it = area_list.begin(); area_it != area_list.end(); area_it++){
        if(area_it->area_size < MIN_AREA_SIZE){

        }
        else{
            auto width = area_it->area_RD.x - area_it->area_LT.x;
            auto high = area_it->area_LT.y - area_it->area_RD.y ;
            Rect rect(area_it->area_LT.x, area_it->area_LT.y, width, high);
//            area_it->area_Mat = image(rect);
//            pyrDown(area_it->area_Mat, area_it->area_Mat_std, Size(30, 30), BORDER_DEFAULT);

            area_it->area_location.x /= area_it->area_size;
            area_it->area_location.y /= area_it->area_size;
            area_it->area_R_ch /= area_it->area_size;
            area_it->area_G_ch /= area_it->area_size;
            area_it->area_B_ch /= area_it->area_size;

        }
        /*struct area &area_ = *area_it;
        auto width = area_.area_RD.x - area_.area_LT.x;
        auto high = area_.area_RD.y - area_.area_LT.y;
        Rect rect(area_.area_LT.x, area_.area_LT.y, width, high);
        area_.area_Mat = image(rect);
        pyrDown(area_.area_Mat, area_.area_Mat_std, Size(30, 30), BORDER_DEFAULT);

        area_.area_location.x /= area_.area_size;
        area_.area_location.y /= area_.area_size;
        area_.area_R_ch /= area_.area_size;
        area_.area_G_ch /= area_.area_size;
        area_.area_B_ch /= area_.area_size;*/

    }

    return 0;
}



int display_the_area_list(vector<struct area> &area_list){
    /*for(auto area_it : area_list){
        printf("#-------------------------\n");
        printf("area_flag:%d\n", area_it.area_flag);
        printf("area_num:%d\n", area_it.area_num);
        printf("area_size:%d\n", (int)(area_it.area_size));
        printf("area_R_ch:%d\n", area_it.area_R_ch);
        printf("area_G_ch:%d\n", area_it.area_G_ch);
        printf("area_B_ch:%d\n", area_it.area_B_ch);
        printf("area_LT:(%d, %d)\n", area_it.area_LT.x, area_it.area_LT.y);
        printf("area_RD:(%d, %d)\n", area_it.area_RD.x, area_it.area_RD.y);
        printf("area_location:(%d, %d)\n", area_it.area_location.x, area_it.area_location.y);
        printf("#-------------------------\n\n\n");
    }*/
    return 0;
}


