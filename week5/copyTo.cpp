#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

using namespace cv;
using namespace std;

void mask_copyTo();
int main()
{
    mask_copyTo();
}

void mask_copyTo()
{
    Mat src = cv::imread(IMAGE_PATH("airplane.bmp"), IMREAD_COLOR);
    Mat mask = cv::imread(IMAGE_PATH("mask_plane.bmp"), IMREAD_GRAYSCALE);
    Mat dst = cv::imread(IMAGE_PATH("field.bmp"), IMREAD_COLOR);

    if (mask.empty() || src.empty() || dst.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    src.copyTo(dst, mask);

    imshow("dst", dst);

    waitKey(0);
    destroyAllWindows();
}