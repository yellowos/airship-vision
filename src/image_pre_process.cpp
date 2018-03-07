//
// Created by yellowos on 02/02/2018.
//
#include "../lib/paramters.h"
#include "../lib/inc.h"

using namespace cv;
using namespace std;
int image_pre_process(Mat *input, Mat *output){
    Size ksize;
    ksize.width = 9;
    ksize.height = 9;

#ifdef DEBUG_MODE
    Mat output_bright;
    Mat output_dark;

    GaussianBlur(*input, *output, ksize, 9, 9);
    erode(*output, *output, getStructuringElement(MORPH_ELLIPSE, ksize));
    erode(*output, *output, getStructuringElement(MORPH_ELLIPSE, ksize));
//    dilate(*output, output_bright, getStructuringElement(MORPH_ELLIPSE, ksize));
//    morphologyEx(*output, *output, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, ksize));
//
//    imshow("bright", output_bright);
//    imshow("dark", output_dark);
//    waitKey(10);
    cvtColor(*output, *output, COLOR_RGB2GRAY);
    imshow("gray", *output);
    waitKey(1);
//    Mat mask(IMAGE_HIGH, IMAGE_WIDTH, CV_8UC1);
    int channels = 0;
    MatND hist;
    int histsize = 256;
    float midrange[] = {-10, 256};
    const float *range[] = {midrange};
    calcHist(output, 1, &channels, Mat(), hist, 1, &histsize, range, true, false);
    Mat drawimage = Mat::zeros(256, 256, CV_8UC3);
    normalize(hist, hist, 0, drawimage.rows, NORM_MINMAX, -1, Mat());
    for (int i = 0; i < 256; i++)
    {
        line(drawimage, Point(i, drawimage.rows - 1), Point(i, drawimage.rows - 1 - cvRound(hist.at<float>(i))), Scalar(0, 0, 255));
    }
    imshow("hist", drawimage);
    waitKey(1);

#endif

    return 0;
}

int dft_analys(Mat *src, Mat *dst){
    int M = getOptimalDFTSize((*src).rows);
    int N = getOptimalDFTSize((*src).cols);

    Mat padded;
    copyMakeBorder(*src, padded, 0, M - (*src).rows, 0, N - (*src).cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexImg;
    merge(planes, 2, complexImg);
    dft(complexImg, complexImg);
    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat mag = planes[0];
    mag += Scalar::all(1);
    log(mag, mag);

    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
    Mat _magI = mag.clone();
    normalize(_magI, _magI, 0, 1, CV_MINMAX);
    imshow("before rearrange ",_magI);

    int cx = mag.cols/2;
    int cy = mag.rows/2;

    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(mag, mag, 0, 1, CV_MINMAX);

    imshow("spectrum magnitude", mag);
    waitKey(1);
    return 0;

}

int dft_process(Mat *src, Mat *dst){
    int M = getOptimalDFTSize((*src).rows);
    int N = getOptimalDFTSize((*src).cols);

    Mat padded;
    copyMakeBorder(*src, padded, 0, M - (*src).rows, 0, N - (*src).cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexImg;
    merge(planes, 2, complexImg);
    dft(complexImg, complexImg);
    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat mag = planes[0];
    mag += Scalar::all(1);
    log(mag, mag);

    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
    Mat _magI = mag.clone();
    normalize(_magI, _magI, 0, 1, CV_MINMAX);
    imshow("before rearrange ",_magI);

    int cx = mag.cols/2;
    int cy = mag.rows/2;

    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(mag, mag, 0, 1, CV_MINMAX);

    imshow("spectrum magnitude", mag);
    waitKey(1);



    return 0;

}