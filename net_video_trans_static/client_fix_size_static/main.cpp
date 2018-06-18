#include <cerrno>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <unp.h>
#include "push_image.h"
#include "parameters.h"

using namespace cv;

struct buffer {
    void *start;
    size_t length;
};

int main() {
    //network init******************************************************
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char address[20] = "192.168.1.191";
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, address, &servaddr.sin_addr);
    //network init finish***********************************************

    //video device init
    int camerafd;
    fd_set readfd;
    int ret;
    struct timeval timeout;
    camerafd = open("/dev/video3", O_RDWR);

    printf("hello world\n");
    struct v4l2_capability cap_info;
    memset(&cap_info, 0, sizeof(cap_info));
    ioctl(camerafd, VIDIOC_QUERYCAP, &cap_info);
    if(!(cap_info.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
        perror("device not support video capture");
    }
    if(!(cap_info.capabilities & V4L2_CAP_STREAMING)){
        perror("device not support video stream");
    }

/*    struct v4l2_streamparm* setfps;
    setfps=(struct v4l2_streamparm *) calloc(1, sizeof(struct v4l2_streamparm));
    memset(setfps, 0, sizeof(struct v4l2_streamparm));
    setfps->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    setfps->parm.capture.timeperframe.numerator=1;
    setfps->parm.capture.timeperframe.denominator=60;
    if(-1== ioctl(camerafd, VIDIOC_S_PARM, setfps))
    {
        std::cout<<"fail"<<std::endl;
        return 0;
    };
*/

    struct v4l2_cropcap cap_set;
    memset(&cap_set, 0, sizeof(cap_set));
    cap_set.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(camerafd, VIDIOC_CROPCAP, &cap_set);
    cap_set.bounds.left = 0;
    cap_set.bounds.top = 0;
    cap_set.bounds.width = 1920;
    cap_set.bounds.height = 1080;
    cap_set.defrect.left = 0;
    cap_set.defrect.top = 0;
    cap_set.defrect.width = 1920;
    cap_set.defrect.height = 1080;
    cap_set.pixelaspect.numerator = 9;
    cap_set.pixelaspect.denominator = 16;

    ioctl(camerafd, VIDIOC_S_CROP, &cap_set);

    int support_grbg10 = 0;

    struct v4l2_fmtdesc fmtdesc = {0};
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    char fourcc[5] = {0};
    char c, e;
    printf("  FMT : CE Desc\n--------------------\n");
    while (0 == ioctl(camerafd, VIDIOC_ENUM_FMT, &fmtdesc))
    {
        strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
        if (fmtdesc.pixelformat == V4L2_PIX_FMT_SGRBG10)
            support_grbg10 = 1;
        c = fmtdesc.flags & 1? 'C' : ' ';
        e = fmtdesc.flags & 2? 'E' : ' ';
        printf("  %s: %c%c %s\n", fourcc, c, e, fmtdesc.description);
        fmtdesc.index++;
    }


    struct v4l2_format cap_fmt;
    memset(&cap_fmt, 0, sizeof(cap_fmt));
    ioctl(camerafd, VIDIOC_G_FMT, &cap_fmt);
    strncpy(fourcc, (char *)&cap_fmt.fmt.pix.pixelformat, 4);
    printf( "Selected Camera Mode:\n"
                    "  Width: %d\n"
                    "  Height: %d\n"
                    "  PixFmt: %s\n"
                    "  Field: %d\n",
            cap_fmt.fmt.pix.width,
            cap_fmt.fmt.pix.height,
            fourcc,
            cap_fmt.fmt.pix.field);


    cap_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    cap_fmt.fmt.pix.width = IMAGE_WIDTH;
    cap_fmt.fmt.pix.height = IMAGE_HIGH;
    cap_fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    cap_fmt.fmt.pix.field = V4L2_FIELD_ANY;
    ioctl(camerafd, VIDIOC_S_FMT, &cap_fmt);
	sleep(1);
    ioctl(camerafd, VIDIOC_G_FMT, &cap_fmt);

    strncpy(fourcc, (char *)&cap_fmt.fmt.pix.pixelformat, 4);
    printf( "Selected Camera Mode:\n"
                    "  Width: %d\n"
                    "  Height: %d\n"
                    "  PixFmt: %s\n"
                    "  Field: %d\n",
            cap_fmt.fmt.pix.width,
            cap_fmt.fmt.pix.height,
            fourcc,
            cap_fmt.fmt.pix.field);



    struct v4l2_requestbuffers req;
    struct v4l2_buffer buf;
    memset(&req, 0, sizeof(req));
    req.count = 2;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    ioctl(camerafd, VIDIOC_REQBUFS, &req);

    struct buffer *buffers;
    buffers = (buffer *)calloc(req.count, sizeof(*buffers));
    for(unsigned int n_buffers = 0; n_buffers < req.count; n_buffers++){
        memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;

        ioctl(camerafd, VIDIOC_QUERYBUF, &buf);

        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start = mmap(nullptr, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, camerafd, buf.m.offset);
        if(buffers[n_buffers].start == MAP_FAILED){
            perror("mmap");
            exit(EXIT_FAILURE);
        }
    }

    for(unsigned int i = 0; i < req.count; i++){
        memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        ioctl(camerafd, VIDIOC_QBUF, &buf);

    }

    fd_set fds;
    struct timeval tv;
    int r;
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(camerafd, VIDIOC_STREAMON, &type);
    //video init finish************************************************************************************************
    //Mat frame(IMAGE_HIGH, IMAGE_WIDTH, CV_16UC1);
    char image_buf[IMAGE_HIGH*IMAGE_WIDTH*2];
    printf("try to connect\n");
    connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
    printf("success connect\n");
    for(int x = 0; x < 1000; x++){
        do{ printf("wait\n");
            FD_ZERO(&fds);
            FD_SET(camerafd, &fds);
            tv.tv_sec = 2;
            tv.tv_usec = 0;

            r = select(camerafd+1, &fds, NULL, NULL, &tv);
        }while(r == -1 && (errno = EINTR));
        if(r == -1){
            perror("select");
            return errno;
        }

        memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
	printf("try to get buf\n");
        ioctl(camerafd, VIDIOC_DQBUF, &buf);
	printf("get buf success\n");
        if(buf.bytesused == IMAGE_HIGH*IMAGE_WIDTH*2){
            printf("data check pass\n");
        }
        else{
            printf("error data size\n");
        }
        memcpy(image_buf, buffers[buf.index].start, buf.bytesused);
//        memcpy(&frame.at<char>(0, 0), buffers[buf.index].start, buf.bytesused);
//        Mat frame_output(IMAGE_HIGH, IMAGE_WIDTH, CV_8UC1);
//        for(int y = 0; y < IMAGE_HIGH; y++) {
//            for (int x = 0; x < IMAGE_WIDTH; x++) {
//                frame_output.at<char>(y, x) = frame.at<int>(y, x/2);
//            }
//        }
//        imshow("output", frame_output);
//        waitKey(1);
        push_image(sockfd, image_buf, buf.bytesused);
        char echo[2] = {0};
        while (echo[0] != '1') {
            read(sockfd, echo, 2);
            usleep(10);
            //printf("###: %s\n", echo);
        }
        printf("%d\n", x);
        ioctl(camerafd, VIDIOC_QBUF, &buf);

    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(camerafd, VIDIOC_STREAMOFF, &type);
    for(unsigned int i = 0; i < req.count; i++){
        munmap(buffers[i].start, buffers[i].length);
    }
    close(camerafd);
    printf("finish!!!");



    return 0;
}
