//
// Created by yellowos on 01/05/2018.
//

#include "../lib/car_detection.h"
#include "../lib/ctrl_flag.h"

int image_pos_cnt = 0;
int image_neg_cnt = 0;

inline void image_save(char *addr, const cv::Mat &img);

int car_detection(Mat image, vector<RotatedRect> &rects){
    Mat src = image.clone();
    Mat gray;
    Mat canny_img;

//    GaussianBlur(image, image, Size(5, 5), 1, 1);
    cvtColor(image, gray, CV_RGB2GRAY);
    imshow("gray", gray);
    waitKey(1);

    Canny(gray, canny_img, 50, 100, 3, true);
    //medianBlur(canny_img, canny_img, 3);
    imshow("gray", gray);
    waitKey(1);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(canny_img, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_NONE);
    //drawContours(image, contours, -1, Scalar(255, 255, 255));
    vector<RotatedRect> rects_temp;

    Ptr<SVM>svm = SVM::load("/Users/yellowos/CLionProjects/HOG_SVM_train/svm.xml");
    HOGDescriptor hog(Size(64, 64), Size(16, 16), Size(8, 8), Size(8, 8), 3);

    for(auto point_list_itr = contours.begin(); point_list_itr != contours.end(); point_list_itr++){
        RotatedRect rect;
        rect = minAreaRect(*point_list_itr);
        rect.size.height *= 1.1;
        rect.size.width *= 1.1;
        double w_h = rect.size.width*1.0/rect.size.height;
        double area_whole = (image.cols * image.rows) / (rect.size.width * rect.size.height);

        if(w_h < 2.5 && w_h >0.4 && area_whole > 10 && area_whole < 250) {
            Mat feed_img = Mat::zeros(Size(64, 64), CV_8UC3);
            Point2f img_points[4];
            Point2f warp_points[4];

            warp_points[0] = cv::Point(0, 0);
            warp_points[1] = cv::Point(0, feed_img.rows);
            warp_points[2] = cv::Point(feed_img.cols, 0);
            warp_points[3] = cv::Point(feed_img.cols, feed_img.rows);

            Point2f vec[4];
            rect.points(vec);

            img_points[0] = vec[2];
            img_points[1] = vec[3];
            img_points[3] = vec[0];
            img_points[2] = vec[1];

            Mat transMat = getPerspectiveTransform(img_points, warp_points);

            warpPerspective(src, feed_img, transMat, feed_img.size());
            vector<float> descriptors;

            if(feed_img.size() == Size(64, 64)) {
//                imshow("feed_image", feed_img);
//                waitKey(10);
                hog.compute(feed_img, descriptors);
                int predict_value;
                predict_value = svm->predict(descriptors);
                if(1 == predict_value) {
                    rects_temp.push_back(rect);
                    char addr[255] = {0};
                    sprintf(addr, "/Users/yellowos/CLionProjects/car_detection_2018_5_1/image_save/pos/img%d.png", image_pos_cnt);
                    image_pos_cnt++;
                    image_save(addr, feed_img);
                    for (int i = 0; i < 4; i++) {
                        line(image, vec[i], vec[(i + 1) % 4], Scalar(255, 255, 255));
                    }
                }
                else if(-1 == predict_value){
                    char addr[255] = {0};
                    sprintf(addr, "/Users/yellowos/CLionProjects/car_detection_2018_5_1/image_save/neg/img%d.png", image_neg_cnt);
                    image_neg_cnt++;
                    image_save(addr, feed_img);
                    for (int i = 0; i < 4; i++) {
                        line(image, vec[i], vec[(i + 1) % 4], Scalar(0, 0, 255));
                    }
                }
            }
            else{
                cout<<"error feed_img size"<<endl;
            }
        }
    }

    imshow("finish", image);
    waitKey(1);

    return 0;
}

inline void image_save(char *addr, const cv::Mat &img){
#ifdef IMAGE_SAVE
    imwrite(addr, img);
#endif

#ifdef IMAGE_SHOW
    cv::imshow("piece", img);
#endif
}
