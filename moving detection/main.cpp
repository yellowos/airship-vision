#include <iostream>
#include <opencv2/opencv.hpp>

#include "lib/function.h"
#include "lib/paramters.h"
//#define AREA_GROW 1

using namespace std;
using namespace cv;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Mat frame_disp;
    Mat frame;
    Mat frame_pre;
    Mat frame_gray;
    Mat frame_pre_gray;
    vector<Rect> pre_Rect;
    int area_num;


    Mat frame_area_grow;




    VideoCapture cap("/Users/yellowos/Desktop/MOV_0088.mp4");
//    VideoCapture cap("/Users/yellowos/Desktop/intel杯/detection/TB.mp4");
//    VideoCapture cap(0);
//    cap.set(CV_CAP_PROP_EXPOSURE, -3);
    if(cap.isOpened()){
        cout << "video capture is opened" << endl;
        cap >> frame_pre;
        pyrDown(frame_pre, frame_pre, Size(), BORDER_DEFAULT);
        cvtColor(frame_pre, frame_pre_gray, CV_BGR2GRAY);
        equalizeHist(frame_pre_gray, frame_pre_gray);
        medianBlur(frame_pre_gray, frame_pre_gray,3);
        GaussianBlur(frame_pre_gray, frame_pre_gray, Size(5, 5), 5, 5, BORDER_DEFAULT);
//        frame_disp = frame.clone();
    }
    while(cap.isOpened()){

//        frame_pre = frame_disp.clone();
//        cap >> frame_pre;
        cap >> frame;

#ifndef AREA_GROW
        pyrDown(frame, frame, Size(), BORDER_DEFAULT);
        frame_disp = frame.clone();


        Size ksize;
        ksize.width = 7;
        ksize.height = 7;

        cvtColor(frame, frame_gray, CV_BGR2GRAY);
//        cvtColor(frame_pre, frame_pre_gray, CV_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);
//        equalizeHist(frame_pre_gray, frame_pre_gray);
        medianBlur(frame_gray, frame_gray,3);
//        medianBlur(frame_pre_gray, frame_pre_gray,3);
        GaussianBlur(frame_gray, frame_gray, Size(5, 5), 5, 5, BORDER_DEFAULT);
//        GaussianBlur(frame_pre_gray, frame_pre_gray, Size(5, 5), 5, 5, BORDER_DEFAULT);
//        Canny(frame_gray, frame_gray, 30, 50, 3, false);
//        Canny(frame_pre_gray, frame_pre_gray, 30, 50, 3, false);
//        pyrDown(frame_gray, frame_gray, Size(), BORDER_DEFAULT);
//        pyrDown(frame_pre_gray, frame_pre_gray, Size(), BORDER_DEFAULT);
//        pyrDown(frame_gray, frame_gray, Size(), BORDER_DEFAULT);
//        pyrDown(frame_pre_gray, frame_pre_gray, Size(), BORDER_DEFAULT);
//        pyrUp(frame_gray, frame_gray, Size(), BORDER_DEFAULT);
//        pyrUp(frame_pre_gray, frame_pre_gray, Size(), BORDER_DEFAULT);
//        pyrUp(frame_gray, frame_gray, Size(), BORDER_DEFAULT);
//        pyrUp(frame_pre_gray, frame_pre_gray, Size(), BORDER_DEFAULT);
//        pyrDown(frame_gray, frame_gray, Size(), BORDER_DEFAULT);
//        pyrDown(frame_pre_gray, frame_pre_gray, Size(), BORDER_DEFAULT);
//        threshold(frame_gray, frame_gray, 128, 256, THRESH_OTSU);
//        threshold(frame_pre_gray, frame_pre_gray, 128, 256, THRESH_OTSU);
//        Canny(frame_gray, frame_gray, 30, 50, 3, false);
//        Canny(frame_pre_gray, frame_pre_gray, 30, 50, 3, false);
//        dilate(frame_gray, frame_gray, getStructuringElement(MORPH_RECT, Size(3, 3)));
//        dilate(frame_pre_gray, frame_pre_gray, getStructuringElement(MORPH_RECT, Size(3, 3)));
//        medianBlur(frame_gray,frame_gray, 3);
//        medianBlur(frame_pre_gray,frame_pre_gray, 3);

//        imshow("canny", frame_pre_gray);
//        boxFilter(frame_gray, frame_gray, frame_gray.depth(), ksize);
//        boxFilter(frame_pre_gray, frame_pre_gray, frame_pre_gray.depth(), ksize);

        Mat processed_frame = frame_gray.clone();
//        Mat frame_add = frame_gray.clone();
        absdiff(frame_pre_gray, frame_gray, processed_frame);
/*//        add(frame_pre_gray, frame_gray, processed_frame_2);
        for(int m = 0; m < IMAGE_WIDTH * IMAGE_HIGH; m++){
            frame_add.at<unsigned char>(m)  = frame_gray.at<unsigned char>(m) > frame_pre_gray.at<unsigned char>(m) ? frame_pre_gray.at<unsigned char>(m):frame_gray.at<unsigned char>(m);
//            processed_frame_2.at<unsigned char>(m)  = abs(frame_gray.at<unsigned char>(m) - frame_pre_gray.at<unsigned char>(m));
        }
        imshow("frame", frame_add);*/
//        medianBlur(processed_frame, processed_frame,3);
        //threshold(processed_frame, processed_frame, 40, 256, THRESH_BINARY);
//        vector<Vec4i> lines;
//        HoughLinesP(processed_frame, lines, 1, CV_PI/180, 20, 20, 5);
//        processed_frame = processed_frame * 0;
//        for( size_t i = 0; i < lines.size(); i++ )
//        {
//            line(processed_frame , Point(lines[i][0], lines[i][1]),
//                  Point(lines[i][2], lines[i][3]), 250, 1, LINE_4);
//        }
//
//        int flag = 0;
//        do{
//            flag = 0;
//            for (int m = 0; m < IMAGE_WIDTH; m++) {
//                for (int n = 0; n < IMAGE_HIGH; n++) {
//
//                    if (processed_frame.at<unsigned char>(n, m) > 250){
//                        if((m < IMAGE_WIDTH - 1) && (processed_frame.at<unsigned char>(n, m+1) < 250)){
//                            if(abs(frame_add.at<unsigned char>(n, m+1)-frame_add.at<unsigned char>(n, m)) < 5){
////                                printf("x: %d, y: %d\n", n, m);
//                                processed_frame.at<unsigned char>(n, m+1) = 255;
//                                flag = 1;
//                            }
//                        }
//                        if((m > 0) && (processed_frame.at<unsigned char>(n, m-1) < 250)){
//                            if(abs(frame_add.at<unsigned char>(n, m-1)-frame_add.at<unsigned char>(n, m)) < 5){
////                                printf("x: %d, y: %d\n", n, m);
//                                processed_frame.at<unsigned char>(n, m-1) = 255;
//                                flag = 1;
//                            }
//                        }
//                        if((n < IMAGE_HIGH - 1) && (processed_frame.at<unsigned char>(n+1, m) < 255)){
//                            if(abs(frame_add.at<unsigned char>(n+1, m)-frame_add.at<unsigned char>(n, m)) < 5){
////                                printf("x: %d, y: %d\n", n, m);
//                                processed_frame.at<unsigned char>(n+1, m) = 255;
//                                flag = 1;
//                            }
//                        }
//                        if((n > 0) && (processed_frame.at<unsigned char>(n-1, m) < 250)){
//                            if(abs(frame_add.at<unsigned char>(n-1, m)-frame_add.at<unsigned char>(n, m)) < 5){
//                                //printf("x: %d, y: %d\n", n, m);
//                                processed_frame.at<unsigned char>(n-1, m) = 255;
//                                flag = 1;
//                            }
//                        }
//                    }
//
//
//                }
//            }
//            printf("%d single finish\n ", flag);
//        }while(flag == 1);
//        printf("frame finish\n");


//        dilate(processed_frame, processed_frame, getStructuringElement(MORPH_RECT, Size(3, 3)));
        medianBlur(processed_frame, processed_frame, 3);
        dilate(processed_frame, processed_frame, getStructuringElement(MORPH_RECT, Size(20, 20)));
//        dilate(processed_frame, processed_frame, getStructuringElement(MORPH_RECT, Size(30, 30)));
//        dilate(processed_frame, processed_frame, getStructuringElement(MORPH_RECT, Size(10, 10)));
//        Canny(processed_frame, processed_frame, 100, 200, 3, false);
        threshold(processed_frame, processed_frame, 10, 256, THRESH_BINARY);

        vector<vector<Point>> contours;
        findContours(processed_frame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//        drawContours(frame_disp, contours, -1, Scalar(0, 0, 255), 2);//在result上绘制轮廓
        vector<Rect> boundRect(contours.size());
        for (int i = 0; i < contours.size(); i++)
        {
            boundRect[i] = boundingRect(contours[i]);
            if(boundRect[i].height*boundRect[i].width > 500) {
                int flag = 1;
                for(auto it = pre_Rect.begin(); it != pre_Rect.end(); it++){
                    if((boundRect[i] & (*it)).area() > 0){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0) {
                    rectangle(frame_disp, boundRect[i], Scalar(0, 255, 0), 2);//在result上绘制正外接矩形
                }
            }
        }
        pre_Rect.clear();
        pre_Rect.assign(boundRect.begin(), boundRect.end());




        imshow("disp", frame_disp);
//        dft_analys(&processed_frame, &frame_gray);
//        imshow("back ground",  processed_frame);
//        imshow("disp", frame_disp);
        waitKey(100);
        frame_pre = frame.clone();
        frame_pre_gray = frame_gray.clone();

//        image_pre_process(&frame, &processed_frame);
#else

        pyrDown(frame, frame, Size(), BORDER_DEFAULT);
//        pyrDown(frame, frame, Size(), BORDER_DEFAULT);
        medianBlur(frame, frame,3);
        medianBlur(frame, frame,3);
//        medianBlur(frame_pre, frame_pre,5);
//        GaussianBlur(frame, frame, Size(9, 9), 10, 10, BORDER_DEFAULT);
        area_lists area_lists_;
        area_num = area_grow(frame, frame_area_grow);
        printf("divide into %d area\n", area_num);
        area area_init;
        area_init.area_flag = 0;
        area_init.area_num = 0;
        area_init.area_size = 0;
        area_init.area_R_ch = 0;
        area_init.area_G_ch = 0;
        area_init.area_B_ch = 0;
        area_init.area_paired_flag = 0;
        for(int i = 0; i < area_num; i++){
            area_lists_.area_after.push_back(area_init);
            area_init.area_flag++;
        }
        area_proc(frame, frame_area_grow, area_lists_.area_after);
        display_the_area_list(area_lists_.area_after);
        waitKey(10);
        frame_pre = frame.clone();
#endif
    }
    return 0;
}

