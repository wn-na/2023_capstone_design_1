#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat img1 = cv::imread(IMAGE_PATH("dog.bmp"));

    Mat img2 = img1;
    Mat img3;
    img3 = img1;

    Mat img4 = img1.clone();
    Mat img5;
    img1.copyTo(img5);

    img1.setTo(Scalar(255, 25, 255));
    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);
    imshow("img4", img4);
    imshow("img5", img5);

    waitKey();
    destroyAllWindows();
}