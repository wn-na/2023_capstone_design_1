#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat src = cv::imread(IMAGE_PATH("rose.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    float data[] = {-1, -1, 0, -1, 0, 1, 0, 1, 1};

    Mat emboss(3, 3, CV_32FC1, data);
    Mat dst;
    filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}