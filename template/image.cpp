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

    imshow("img1", img1);

    waitKey();
    destroyAllWindows();
}