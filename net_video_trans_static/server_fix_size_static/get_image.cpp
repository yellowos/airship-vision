//
// Created by yellowos on 14/11/2017.
//

#include "get_image.h"
#include "parameters.h"
#include <unistd.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int get_image(int connfd, char *buf, size_t n){
    //char buf[IMAGE_WIDTH*IMAGE_HIGH];
    ssize_t nread;
    size_t nleft = n;
    char *ptr = buf;

    while (nleft > 0) {
        if ((nread = read(connfd, ptr, nleft)) < 0) {
            if (nleft == n) {
                return -1;
            } else {
                break;
            }
        } else if (nread == 0) {
            break;
        }

        nleft -= nread;
        ptr += nread;
    }

    //Mat dis_mat(IMAGE_HIGH, IMAGE_WIDTH, CV_8UC1);

    //memcpy(&dis_mat.at<char>(0, 0), buf, IMAGE_HIGH*IMAGE_WIDTH);
    //too slow buf useful
    /*int offset = 0;
    for (int y = 0; y < dis_mat.rows; y++) {
        for (int x = 0; x < dis_mat.cols; x++) {
            dis_mat.at<char>(y, x) = buf[offset];
            offset++;
        }
    }*/
    //imshow("output", dis_mat);
    //waitKey(1);
//    destroyWindow("output");
//    printf("finish display\n");
//    write(connfd, "1", 2);


    return 0;
}