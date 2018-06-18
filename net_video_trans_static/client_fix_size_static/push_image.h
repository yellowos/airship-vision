//
// Created by yellowos on 11/20/17.
//
#include <unistd.h>

#ifndef V4L2_PUSH_IMAGE_H
#define V4L2_PUSH_IMAGE_H
int push_image(int sockfd, char *buf, size_t n);
#endif //V4L2_PUSH_IMAGE_H
