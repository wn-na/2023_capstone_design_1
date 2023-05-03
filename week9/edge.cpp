#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat src = cv::imread(IMAGE_PATH("lenna.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    float data[] = {-1, 0, 1};

    Mat x(1, 3, CV_32FC1, data);
    Mat y(3, 1, CV_32FC1, data);

    Mat dstx, dsty;
    filter2D(src, dstx, -1, x, Point(-1, -1), 128);
    filter2D(src, dsty, -1, y, Point(-1, -1), 128);

    imshow("src", src);
    imshow("dstx", dstx);
    imshow("dsty", dsty);

    waitKey();
    destroyAllWindows();
}