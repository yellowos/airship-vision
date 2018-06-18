#include <iostream>
#include <unp.h>
#include "get_image.h"
#include <opencv2/opencv.hpp>
#include "parameters.h"


using namespace cv;
int main() {
    int listenfd, connfd;
    struct sockaddr_in cliaddr, servaddr;
    socklen_t clilen;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);
    clilen = sizeof(cliaddr);
    //ctrlfd = accept(listenfd, (SA *) &cliaddr, &clilen);
    printf("ok\n");
    connfd = accept(listenfd, (SA *) &cliaddr, &clilen);
    printf("connect!\n");
    char buf[IMAGE_HIGH * IMAGE_WIDTH] = {0};
    while (true) {

        Mat frame(IMAGE_HIGH, IMAGE_WIDTH, CV_16UC1);
        get_image(connfd, (char *)&frame.at<int>(0, 0), IMAGE_WIDTH * IMAGE_HIGH*2);
        Mat output_frame(IMAGE_HIGH, IMAGE_WIDTH, CV_8UC1);
        for(int y = 0; y < IMAGE_HIGH; y++){
            for(int x = 0; x < IMAGE_WIDTH; x++){
                output_frame.at<char>(y, x) = frame.at<int>(y, x/2);
            }
        }

        //memcpy(&frame.at<char>(0, 0), buf, IMAGE_WIDTH * IMAGE_HIGH * 2);
        imshow("output", output_frame);
        waitKey(1);
        //close(connfd);
        //printf("finish get image\n");
        write(connfd, "1", 2);


        /*if (fork() == 0) {
            printf("wait connect\n");
            connfd = accept(listenfd, (SA *) &cliaddr, &clilen);
            get_image(connfd);
            close(connfd);
            printf("finish connect\n\n");
            exit(0);
        } else {
            wait(nullptr);
            write(ctrlfd, "1", 2);
        }*/
    }
    return 0;
}

