#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#define POS_NUM 1100
#define NEG_NUM 2270

using namespace std;
using namespace cv;
using namespace cv::ml;

int main() {
    char adpos[255], adneg[255];
    HOGDescriptor hog(Size(64, 64), Size(16, 16), Size(8, 8), Size(8, 8), 3);
    int Descriptordim;
    Mat sam_label_mat, sam_feature_mat;
    for(int i = 0; i < POS_NUM; i++){
        sprintf(adpos, "/Users/yellowos/CLionProjects/HOG_SVM_train/pos_img/img%d.png", i);
        Mat src = imread(adpos);
        resize(src, src, Size(64, 64));
        vector<float> descriptors;
        hog.compute(src, descriptors);
        if(i == 0){
            Descriptordim = (int)descriptors.size();
            sam_feature_mat = Mat::zeros(POS_NUM+NEG_NUM, Descriptordim, CV_32FC1);
            sam_label_mat = Mat::zeros(POS_NUM+NEG_NUM, 1, CV_32SC1);
        }

        for(int j = 0; j < Descriptordim; j++) {
            sam_feature_mat.at<float>(i, j) = descriptors[j];
            sam_label_mat.at<int>(i, 0) = 1;
        }
    }

    for (int k = 0; k < NEG_NUM; k++)
    {
        sprintf(adneg, "/Users/yellowos/CLionProjects/HOG_SVM_train/neg_img/image%d.png", k);
        Mat src = imread(adneg);//读取图片
        resize(src,src,Size(64,64));
        vector<float> descriptors;//HOG描述子向量
        hog.compute(src,descriptors);
        for(int l=0; l<Descriptordim; l++)
        {
            sam_feature_mat.at<float>(k+POS_NUM,l) = descriptors[l];
            sam_label_mat.at<int>(k+POS_NUM,0) = -1;
        }
    }

    cout<<"特征个数："<<sam_feature_mat.rows<<endl;
    cout<<"特征维度："<<sam_feature_mat.cols<<endl;

    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);

    Ptr<TrainData> td = TrainData::create(sam_feature_mat, ROW_SAMPLE, sam_label_mat);
    svm->train(td);
    svm->save("/Users/yellowos/CLionProjects/HOG_SVM_train/svm.xml");


    cout<<"finish"<<endl;

    return 0;
}