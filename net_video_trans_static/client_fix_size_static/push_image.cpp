//
// Created by yellowos on 11/20/17.
//

#include "push_image.h"
#include <unistd.h>
#include "parameters.h"

int push_image(int sockfd, char *buf, size_t n){
    ssize_t nwritten;
    //size_t nleft = IMAGE_WIDTH*IMAGE_HIGH;
    size_t nleft = n;
    char *ptr = buf;
    while(nleft > 0){

        if((nwritten = write(sockfd, ptr, nleft)) < 0){
            if(nleft == n){
                return -1;
            }
            else{
                break;
            }
        }
        else if(nwritten == 0){
            break;
        }

        nleft -= nwritten;
        ptr += nwritten;

    }
    return 0;
}